

#include "LeaderBoard.h"

LeaderBoard::LeaderBoard() {
    len1 = 0;
    len2 = 0;
    ReadFile_();
}

void LeaderBoard::BubbleSort(players players_[],int len)
{
    for (int i = len; i > 1; i--)
    {
        bool swapped = false;

        for (int j = 0; j + 1 < i; j++)
        {
            if (players_[j].score < players_[j + 1].score)
            {
                players temp = players_[j];
                players_[j] = players_[j + 1];
                players_[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;

    }
}
