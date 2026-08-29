#include "serve.h"

#include <map>

#include "poll.h"
#include <unistd.h>
#include <netinet/tcp.h>
#include <random>

//声明随机数种子
std::random_device rd;
std::mt19937 gen(rd());

//获取随机数
int RandInt_(int lower,int upper) {
    if(lower > upper)
    {
        int temp = lower;
        lower = upper;
        upper = temp;
    }
    std::uniform_int_distribution<int> dis(lower, upper);
    return dis(gen);
}

//为房间对战提前创建线程
   ThreadPoll pool(MAXSIZE_ROOM*3);

class GameServer {
    //属性
private:
    TcpServe serve;          //tcp客户端类

    int room[MAXSIZE_ROOM][MAXSIZE_PEOPLE]{};            //用于存储玩家的socket
    int room_dir[MAXSIZE_ROOM][MAXSIZE_PEOPLE];          //用于存储玩家方向
    Food* room_food[MAXSIZE_ROOM];                       //每个房间独立生成的食物
    Node* room_snack[MAXSIZE_ROOM][MAXSIZE_PEOPLE];      //每个房间蛇的头节点
    int room_score[MAXSIZE_ROOM][MAXSIZE_PEOPLE];        //每个房间玩家分数
    bool map[MAXSIZE_ROOM][HEIGHT/SIZE][WIDTH/SIZE];     //每个房间的地图


    int empty_room_num = MAXSIZE_ROOM;    //空闲房间数量
    std::queue<int> waiting;              //等待匹配的队列，存客户端的socket
    std::queue<int> delete_room;          //等待销毁房间队列

    //方法
public:
    GameServer() {
        //初始化房间
        for (int i = 0; i < MAXSIZE_ROOM; i++) {
            for (int j = 0; j < MAXSIZE_PEOPLE; j++) {
                room[i][j] = -1;
                room_dir[i][j] = RIGHT;
            }
        }

    }

    //初始化食物
    void InitFood_(int keys) {
        room_food[keys] = new Food();
        do {
            room_food[keys] -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
            room_food[keys] -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
        }while ((map[keys][room_food[keys] ->y/SIZE][room_food[keys] -> x/SIZE] == false));

        room_food[keys] -> exists = true;
    };

    //初始化玩家1
    void InitSnack1_(int keys) {
        room_snack[keys][0] = new Node();

        Node* head = new Node();
        Node* mid  = new Node();
        Node* tail = new Node();

        head->next = mid;
        mid->next = tail;
        tail->next = nullptr;

        head -> x = PLAYER1_HEAD_X;
        head -> y = PLAYER1_HEAD_Y;

        room_dir[keys][0] = PLAYER1_DIRECTION;
        room_score[keys][0] = 0;

        switch (room_dir[keys][0]) {
            case LEFT: mid -> x = PLAYER1_HEAD_X + SIZE;
                mid -> y = PLAYER1_HEAD_Y;
                tail -> x = PLAYER1_HEAD_X + SIZE*2;
                tail -> y = PLAYER1_HEAD_Y;
                break;

            case UP:   mid -> x = PLAYER1_HEAD_X;
                mid -> y = PLAYER1_HEAD_Y + SIZE;
                tail -> x = PLAYER1_HEAD_X;
                tail -> y = PLAYER1_HEAD_Y + SIZE*2;
                break;


            case RIGHT:mid -> x = PLAYER1_HEAD_X - SIZE;
                mid -> y = PLAYER1_HEAD_Y;
                tail -> x = PLAYER1_HEAD_X - SIZE*2;
                tail -> y = PLAYER1_HEAD_Y;
                break;

            case DOWN: mid -> x = PLAYER1_HEAD_X;
                mid -> y = PLAYER1_HEAD_Y - SIZE;
                tail -> x = PLAYER1_HEAD_X;
                tail -> y = PLAYER1_HEAD_Y - SIZE*2;
                break;
        }
        room_snack[keys][0] -> next =  head;
    }

    //初始化玩家2
    inline void InitSnack2_(int keys) {
        room_snack[keys][1] = new Node();

        Node* head = new Node();
        Node* mid  = new Node();
        Node* tail = new Node();

        head->next = mid;
        mid->next = tail;
        tail->next = nullptr;

        head -> x = PLAYER2_HEAD_X;
        head -> y = PLAYER2_HEAD_Y;

        room_dir[keys][1] = PLAYER2_DIRECTION;
        room_score[keys][1] = 0;

        switch (room_dir[keys][1]) {
            case LEFT: mid -> x = PLAYER2_HEAD_X + SIZE;
                mid -> y = PLAYER2_HEAD_Y;
                tail -> x = PLAYER2_HEAD_X + SIZE*2;
                tail -> y = PLAYER2_HEAD_Y;
                break;

            case UP:   mid -> x = PLAYER2_HEAD_X;
                mid -> y = PLAYER2_HEAD_Y + SIZE;
                tail -> x = PLAYER2_HEAD_X;
                tail -> y = PLAYER2_HEAD_Y + SIZE*2;
                break;


            case RIGHT:mid -> x = PLAYER2_HEAD_X - SIZE;
                mid -> y = PLAYER2_HEAD_Y;
                tail -> x = PLAYER2_HEAD_X - SIZE*2;
                tail -> y = PLAYER2_HEAD_Y;
                break;

            case DOWN: mid -> x = PLAYER2_HEAD_X;
                mid -> y = PLAYER2_HEAD_Y - SIZE;
                tail -> x = PLAYER2_HEAD_X;
                tail -> y = PLAYER2_HEAD_Y - SIZE*2;
                break;
        }
        room_snack[keys][1] -> next =  head;
    }

    //初始化地图
    void InitMap_(int keys) {
        for (int i = 0;i <= HEIGHT/SIZE-1;i++ ) {
            for (int j = 0;j <= WIDTH/SIZE-1;j++ ) {
                map[keys][i][j] = true;
            }
        }

        room_score[keys][0] = 0;
        room_score[keys][1] = 0;
        InitSnack1_(keys);
        InitSnack2_(keys);
        InitFood_(keys);
    }

    //玩家1的移动逻辑
    void  UpdatePlay1_(int keys) {
    Node* new_head  = new Node;

    switch (room_dir[keys][0]) {
        case LEFT:new_head -> x = room_snack[keys][0] -> next -> x - SIZE;
            new_head -> y = room_snack[keys][0] -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = room_snack[keys][0] -> next -> y - SIZE;
            new_head -> x = room_snack[keys][0] -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = room_snack[keys][0] -> next -> x + SIZE;
            new_head -> y = room_snack[keys][0] -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = room_snack[keys][0] -> next -> y + SIZE;
            new_head -> x = room_snack[keys][0] -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
            break;
    }

    new_head -> next = room_snack[keys][0] -> next;
    room_snack[keys][0] -> next = new_head;

    Node* temp = room_snack[keys][0] -> next;
    while (temp -> next != nullptr) {
        map[keys][temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }


    //玩家1未吃到food尾巴减少
        if (!(room_snack[keys][0] -> next -> x == room_food[keys] -> x && room_snack[keys][0] -> next -> y == room_food[keys] -> y)) {
            Node* pre = room_snack[keys][0];
            Node* delete_tail = room_snack[keys][0] -> next;
            while (delete_tail -> next != nullptr) {
                delete_tail = delete_tail -> next;
                pre = pre -> next;
            }
            map[keys][delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
            delete delete_tail;
            pre -> next = nullptr;
        }

}

    //玩家2的移动逻辑
    void UpdatePlay2_(int keys) {
    Node* new_head  = new Node;

    switch (room_dir[keys][1]) {
        case LEFT:new_head -> x = room_snack[keys][1] -> next -> x - SIZE;
            new_head -> y = room_snack[keys][1] -> next -> y;
            if (new_head -> x < 0) {
                new_head -> x = WIDTH - SIZE;
            }
            break;

        case UP:new_head -> y = room_snack[keys][1] -> next -> y - SIZE;
            new_head -> x = room_snack[keys][1] -> next -> x;
            if (new_head -> y < 0) {
                new_head -> y = HEIGHT - SIZE;
            }
            break;

        case RIGHT:new_head -> x = room_snack[keys][1] -> next -> x + SIZE;
            new_head -> y = room_snack[keys][1] -> next -> y;
            if (new_head -> x > WIDTH - SIZE) {
                new_head -> x = 0;
            }
            break;

        case DOWN:new_head -> y = room_snack[keys][1] -> next -> y + SIZE;
            new_head -> x = room_snack[keys][1] -> next -> x;
            if (new_head -> y > HEIGHT - SIZE) {
                new_head -> y = 0;
            }
            break;
    }

    new_head -> next = room_snack[keys][1] -> next;
    room_snack[keys][1] -> next = new_head;

    Node* temp = room_snack[keys][1] -> next;
    while (temp -> next != nullptr) {
        map[keys][temp -> next ->y/SIZE][temp -> next -> x/SIZE] = false;
        temp = temp -> next;
    }


    //玩家2未吃到food尾巴减少
        if (!(room_snack[keys][1] -> next -> x == room_food[keys] -> x && room_snack[keys][1] -> next -> y == room_food[keys] -> y)) {
            Node* pre = room_snack[keys][1];
            Node* delete_tail = room_snack[keys][1] -> next;
            while (delete_tail -> next != nullptr) {
                delete_tail = delete_tail -> next;
                pre = pre -> next;
            }
            map[keys][delete_tail -> y/SIZE][delete_tail -> x/SIZE] = true;
            delete delete_tail;
            pre -> next = nullptr;
        }

}

    //食物更新
    void UpdateFood_(int keys) {
        //玩家1吃到食物
        if (room_snack[keys][0] -> next -> x == room_food[keys] -> x && room_snack[keys][0] -> next -> y == room_food[keys] -> y) {
            room_food[keys] -> exists = false;
            room_score[keys][0] += speed;
            return;
        }
        //玩家2吃到食物
        else if (room_snack[keys][1] -> next -> x == room_food[keys] -> x && room_snack[keys][1] -> next -> y == room_food[keys] -> y) {
            room_food[keys] -> exists = false;
            room_score[keys][1] += speed;
            return;
        }

        if (room_food[keys] -> exists ) return;

        do {
            room_food[keys] -> x = RandInt_(1,WIDTH/SIZE-2)*SIZE;
            room_food[keys] -> y = RandInt_(1,HEIGHT/SIZE-2)*SIZE;
        }while ((map[keys][room_food[keys] ->y/SIZE][room_food[keys] -> x/SIZE] == false) || (room_snack[keys][0] -> next -> x == room_food[keys] -> x && room_snack[keys][0] -> next -> y == room_food[keys] -> y) || (room_snack[keys][1] -> next -> x == room_food[keys] -> x && room_snack[keys][1] -> next -> y == room_food[keys] -> y));

        room_food[keys] -> exists = true;
    }

    //地图更新
    void UpdateMap_(int keys) {
        UpdatePlay1_(keys);
        UpdatePlay2_(keys);
        UpdateFood_(keys);

    }
    //游戏服务器监听
    void Listen_(const unsigned short& port) {
        serve.Listen_(port);
    }

    bool Player1IsDead_(int keys) {
        if (map[keys][room_snack[keys][0] -> next-> y/SIZE][room_snack[keys][0] -> next-> x/SIZE] == false) return true;
        return false;
    }

    bool Player2IsDead_(int keys) {
        if (map[keys][room_snack[keys][1] -> next-> y/SIZE][room_snack[keys][1] -> next-> x/SIZE] == false) return true;
        return false;
    }

    //游戏服务器接受报文
    void Accept_() {

        while (true) {
            // std::cout << "等待连接请求..." << std::endl;
            //受理客户端的连接，如果没收到连接则阻塞,连接到了就返回客户端句柄
            int temp_socket;//用于存储客户端句柄
            if ( serve.Accept_(temp_socket) == -1) {
                perror("accept error");
                break;
            }

            std::cout << "当前等待队列人数为："<<waiting.size()<<std::endl;
            // std::cout << "收到连接请求，连接成功"<< std::endl;
            if (waiting.size() == MAXSIZE_QUEUE) {//等待队列已满，拒绝连接
                std::cout << "等待队列已满，断开连接"<< std::endl;
                // serve.Send_(temp_socket,"1");//发送匹配队列已满，让其断开连接
                serve.CloseSocket_(temp_socket);
            }
            else {
                std::cout << "加入等待队列"<< std::endl;
                waiting.push(temp_socket);          //加入等待队列
                //开1个线程接受退出队列消息
                pool.enqueue([this,temp_socket] {
                    string ac;
                    int res1 = serve.Receive_(temp_socket,ac,MAXLEN); //接受玩家1改变后的状态
                    if (stoi(ac) == EXIT_QUEUE) {
                        std::cout << "收到EXIT_QUEUE退出等待队列消息" << std::endl;
                        queue<int> temp;
                        while (!waiting.empty()) {
                            if (waiting.front() == temp_socket) {
                                waiting.pop();
                                continue;
                            }
                            temp.push(waiting.front());
                        }
                       while (!temp.empty()) {
                           waiting.push(temp.front());
                           temp.pop();
                       }
                        std::cout << "退出队列成功发送EXIT_QUEUE"<< std::endl;
                        serve.Send_(temp_socket,to_string(EXIT_QUEUE)); //发送退出队列成功消息
                        serve.CloseSocket_(temp_socket);
                    }
                    else if (stoi(ac) == ENTER_SUCCESS) {

                    }

                });

            }

            // std::cout << "当前等待队列人数为："<<waiting.size()<< std::endl;
            //处理队列
            if (waiting.size() >= 2 && empty_room_num >= 1) {
                //取出客户端socket
                int player1_socket = waiting.front();
                waiting.pop();
                int player2_socket = waiting.front();
                waiting.pop();
                // std::cout << "发送匹配成功"<<to_string(ENTER_SUCCESS)<< std::endl;
                serve.Send_(player1_socket,to_string(ENTER_SUCCESS));
                serve.Send_(player2_socket,to_string(ENTER_SUCCESS));

                int keys = 0;   //房间号
                //寻找空的房间
                for (int i = 0; i < MAXSIZE_ROOM; i++) {
                    if (room[i][0] == -1 && room[i][1] == -1) {
                        keys = i;
                        break;
                    }
                }

                //玩家进入房间
                room[keys][0] = player1_socket;
                room[keys][1] = player2_socket;
                empty_room_num--;//空闲房间减少

                //初始化地图
                InitMap_(keys);

                serve.Send_(player1_socket,"1"); //给玩家1发送其编号
                serve.Send_(player2_socket,"2"); //给玩家2发送其编号
                usleep(200000);   // 休眠200毫秒等待玩家收到编号，防止粘包

                //开一个线程来处理当前房间的对战

                //接收玩家1和玩家2的消息，并发送消息
                pool.enqueue([this,keys] {
                    string ac1;
                    string ac2;
                    int res1;
                    int res2;
                   while (true) {
                        res1 = serve.Receive_(room[keys][0],ac1,MAXLEN); //接受玩家1改变后的状态
                        res2 = serve.Receive_(room[keys][1],ac2,MAXLEN);  //接受玩家2改变后的状态

                       if (res1 == -1) {//玩家1网络异常断开
                           serve.Send_(room[keys][1],to_string(ERRORS));//给玩家2发送对局异常结束
                           delete_room.push(keys);
                           //退出线程
                           break;
                       }
                       else if (res2 == -1) {//玩家2网络异常断开
                           serve.Send_(room[keys][0],to_string(ERRORS));//给玩家1发送对局异常结束
                           delete_room.push(keys);
                            //退出线程
                            break;
                       }

                       room_dir[keys][0] = stoi(ac1);//修改服务端玩家1状态
                       room_dir[keys][1] = stoi(ac2);//修改服务端玩家2状态

                       //逻辑更新
                      UpdateMap_(keys);

                       if (Player1IsDead_(keys)) {//玩家1死亡,玩家2胜利，对局结束
                           serve.Send_(room[keys][1],to_string(PLAY2WIN));//给玩家2发送玩家2胜利
                           serve.Send_(room[keys][0],to_string(PLAY2WIN));//给玩家1发送玩家2胜利
                           delete_room.push(keys);
                           //退出线程
                             break;
                       }
                       else if (Player2IsDead_(keys)) {//玩家2死亡，玩家1胜利对局结束
                           serve.Send_(room[keys][1],to_string(PLAY1WIN));//给玩家2发送玩家1胜利
                           serve.Send_(room[keys][0],to_string(PLAY1WIN));//给玩家1发送玩家1胜利
                           delete_room.push(keys);
                           //退出线程
                             break;
                       }

                       //发送状态
                       //发送食物位置
                       char f_x[1024];
                       char f_y[1024];
                       char p1_score[1024];
                       char p2_score[1024];
                       sprintf(f_x, "%03d", room_food[keys] -> x);
                       sprintf(f_y, "%03d", room_food[keys] -> y);
                       sprintf(p1_score, "%04d", room_score[keys][0]);
                       sprintf(p2_score, "%04d", room_score[keys][1]);
                       serve.Send_(room[keys][0],to_string(room_dir[keys][1]) + f_x + f_y + p1_score + p2_score);
                       serve.Send_(room[keys][1],to_string(room_dir[keys][0]) + f_x + f_y + p1_score + p2_score);

                       usleep(100000);   // 休眠100毫秒

                   }
               });

            }

            //销毁房间队列
            while (!delete_room.empty()) {
                int k = delete_room.front();
                delete_room.pop();
                //关闭玩家1的socket
                serve.CloseSocket_(room[k][0]);
                //关闭玩家2的socket
                serve.CloseSocket_(room[k][1]);
                //退出房间
                room[k][0] = -1;
                room[k][1] = -1;
                room_dir[k][0] = RIGHT;
                room_dir[k][1] = RIGHT;
                delete room_food[k];
                room_food[k] = nullptr;
                Node* p = room_snack[k][0];
                while (p) {
                    Node* temp = p;
                    p = p->next;
                    delete temp;
                }
                room_snack[k][0] = nullptr;
                p = room_snack[k][1];
                while (p) {
                    Node* temp = p;
                    p = p->next;
                    delete temp;
                }
                room_snack[k][1] = nullptr;
                room_score[k][0] = 0;
                room_score[k][1] = 0;
                empty_room_num += 1;
            }

            sleep(1);

        }
    }

};

int main() {

    GameServer server;
    server.Listen_(SPORT);

    while (true) {

        server.Accept_();

    }



}