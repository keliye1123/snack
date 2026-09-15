//
// Created by 25738 on 2026/9/13.
//

#include "InputMethod.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <iostream>
#include <windows.h>
#include <conio.h>

//wstring转string
std::string WStringToString(const std::wstring& wstr)
{
    if (wstr.empty()) return "";
    int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

//输入法词库
void InputMethod::LoadDefaultDictionary_() {
    AddWord_(L"ni", L"你", 100);
    AddWord_(L"ni", L"尼", 20);
    AddWord_(L"ni", L"泥", 10);
    AddWord_(L"hao", L"好", 100);
    AddWord_(L"hao", L"号", 50);
    AddWord_(L"nihao", L"你好", 150);
    AddWord_(L"wo", L"我", 100);
    AddWord_(L"wo", L"沃", 10);
    AddWord_(L"men", L"们", 100);
    AddWord_(L"men", L"门", 50);
    AddWord_(L"de", L"的", 200);
    AddWord_(L"de", L"地", 80);
    AddWord_(L"de", L"得", 60);
    AddWord_(L"shi", L"是", 150);
    AddWord_(L"shi", L"时", 50);
    AddWord_(L"shi", L"事", 40);
    AddWord_(L"zai", L"在", 100);
    AddWord_(L"zai", L"再", 60);
    AddWord_(L"le", L"了", 150);
    AddWord_(L"le", L"乐", 30);
    AddWord_(L"you", L"有", 120);
    AddWord_(L"you", L"又", 50);
    AddWord_(L"you", L"游", 30);
    AddWord_(L"ta", L"他", 100);
    AddWord_(L"ta", L"她", 90);
    AddWord_(L"ta", L"它", 40);
    AddWord_(L"yi", L"一", 150);
    AddWord_(L"yi", L"已", 40);
    AddWord_(L"yi", L"以", 30);
    AddWord_(L"bu", L"不", 150);
    AddWord_(L"bu", L"布", 20);
    AddWord_(L"lai", L"来", 100);
    AddWord_(L"lai", L"莱", 10);
    AddWord_(L"qu", L"去", 100);
    AddWord_(L"qu", L"区", 30);
    AddWord_(L"kan", L"看", 80);
    AddWord_(L"kan", L"刊", 20);
    AddWord_(L"shuo", L"说", 80);
    AddWord_(L"shuo", L"硕", 10);
    AddWord_(L"zhe", L"这", 120);
    AddWord_(L"zhe", L"着", 60);
    AddWord_(L"na", L"那", 100);
    AddWord_(L"na", L"哪", 50);
    AddWord_(L"na", L"拿", 40);
    AddWord_(L"hen", L"很", 80);
    AddWord_(L"hen", L"狠", 20);
    AddWord_(L"dou", L"都", 90);
    AddWord_(L"dou", L"斗", 20);
    AddWord_(L"da", L"大", 100);
    AddWord_(L"da", L"打", 80);
    AddWord_(L"da", L"答", 40);
    AddWord_(L"xiao", L"小", 90);
    AddWord_(L"xiao", L"笑", 60);
    AddWord_(L"xiao", L"校", 40);
    AddWord_(L"shang", L"上", 100);
    AddWord_(L"shang", L"商", 40);
    AddWord_(L"xia", L"下", 100);
    AddWord_(L"xia", L"夏", 30);
    AddWord_(L"zhong", L"中", 100);
    AddWord_(L"zhong", L"重", 50);
    AddWord_(L"zhong", L"终", 30);
    AddWord_(L"guo", L"国", 100);
    AddWord_(L"guo", L"过", 80);
    AddWord_(L"guo", L"果", 40);
    AddWord_(L"ren", L"人", 150);
    AddWord_(L"ren", L"任", 40);
    AddWord_(L"ren", L"认", 30);
    AddWord_(L"ming", L"名", 80);
    AddWord_(L"ming", L"明", 60);
    AddWord_(L"zi", L"字", 70);
    AddWord_(L"zi", L"自", 60);
    AddWord_(L"zi", L"子", 50);
    AddWord_(L"jia", L"家", 90);
    AddWord_(L"jia", L"加", 60);
    AddWord_(L"jia", L"假", 40);
    AddWord_(L"she", L"社", 60);
    AddWord_(L"she", L"设", 50);
    AddWord_(L"she", L"舍", 30);
    AddWord_(L"hui", L"会", 100);
    AddWord_(L"hui", L"回", 80);
    AddWord_(L"hui", L"汇", 30);
}


//初始化（初始当前选择的下标和加载词库）
InputMethod::InputMethod() : selectedIndex_(0),IsRun_(false) {
    std::cout << "词库初始化成功" << std::endl;
    LoadDefaultDictionary_();
}


//添加词
void InputMethod::AddWord_(const std::wstring& pinyin, const std::wstring& word, int frequency) {
    dictionary_[pinyin].emplace_back(word, frequency);
}

void InputMethod::InputPinyin_(char c) {
    if (c >= 'a' && c <= 'z') {
        currentPinyin_ += c;
        candidates_ = GetCandidates_();
        selectedIndex_ = 0;
    }
}

std::vector<Word> InputMethod::GetCandidates_() const {
    std::vector<Word> result;

    if (currentPinyin_.empty()) {
        return result;
    }

    auto it = dictionary_.find(currentPinyin_);
    if (it != dictionary_.end()) {
        result = it->second;
        std::sort(result.begin(), result.end(),
            [](const Word& a, const Word& b) {
                return a.frequency > b.frequency;
            });
    }

    return result;
}

void InputMethod::SetStatus_(bool s) {
    IsRun_ = s;
}

bool InputMethod::GetStatus_() const {
    return IsRun_;
}

void InputMethod::DeletePinyin_() {
    if (!currentPinyin_.empty()) {
        currentPinyin_.pop_back();
        candidates_ = GetCandidates_();
        selectedIndex_ = 0;
    }
}

void InputMethod::ClearPinyin_() {
    currentPinyin_.clear();
    candidates_.clear();
    selectedIndex_ = 0;
}

std::wstring InputMethod::SelectCandidate_() {
    if (selectedIndex_ >= 0 && selectedIndex_ < static_cast<int>(candidates_.size())) {
        std::wstring selectedWord = candidates_[selectedIndex_].text;

        dictionary_[currentPinyin_][selectedIndex_].frequency++;

        ClearPinyin_();
        return selectedWord;
    }
    return L"";
}

std::wstring InputMethod::GetCurrentPinyin_() const {
    return currentPinyin_;
}

int InputMethod::GetSelectedIndex_() const {
    return selectedIndex_;
}

void InputMethod::SetSelectedIndex_(int index) {
    if (index >= 0 && index < static_cast<int>(candidates_.size())) {
        selectedIndex_ = index;
    }
}

void InputMethod::SortCandidates_() {
    std::sort(candidates_.begin(), candidates_.end(),
        [](const Word& a, const Word& b) {
            return a.frequency > b.frequency;
        });
}

bool InputMethod::GetCaps_() const {
    return GetAsyncKeyState(VK_CAPITAL) & 1;
}

std::vector<Word> InputMethod::RunInputMethod_(std::wstring& name) {
    //未锁定大写模式
   if (!GetCaps_()) {
       if (GetAsyncKeyState('A') & 0x8000) { inputMethod.InputPinyin_('a');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('B') & 0x8000) { inputMethod.InputPinyin_('b');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('C') & 0x8000) { inputMethod.InputPinyin_('c');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('D') & 0x8000) { inputMethod.InputPinyin_('d');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('E') & 0x8000) { inputMethod.InputPinyin_('e');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('F') & 0x8000) { inputMethod.InputPinyin_('f');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('G') & 0x8000) { inputMethod.InputPinyin_('g');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('H') & 0x8000) { inputMethod.InputPinyin_('h');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('I') & 0x8000) { inputMethod.InputPinyin_('i');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('J') & 0x8000) { inputMethod.InputPinyin_('j');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('K') & 0x8000) { inputMethod.InputPinyin_('k');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('L') & 0x8000) { inputMethod.InputPinyin_('l');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('M') & 0x8000) { inputMethod.InputPinyin_('m');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('N') & 0x8000) { inputMethod.InputPinyin_('n');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('O') & 0x8000) { inputMethod.InputPinyin_('o');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('P') & 0x8000) { inputMethod.InputPinyin_('p');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('Q') & 0x8000) { inputMethod.InputPinyin_('q');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('R') & 0x8000) { inputMethod.InputPinyin_('r');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('S') & 0x8000) { inputMethod.InputPinyin_('s');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('T') & 0x8000) { inputMethod.InputPinyin_('t');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('U') & 0x8000) { inputMethod.InputPinyin_('u');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('V') & 0x8000) { inputMethod.InputPinyin_('v');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('W') & 0x8000) { inputMethod.InputPinyin_('w');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('X') & 0x8000) { inputMethod.InputPinyin_('x');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('Y') & 0x8000) { inputMethod.InputPinyin_('y');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState('Z') & 0x8000) { inputMethod.InputPinyin_('z');inputMethod.SetStatus_(true); }
       else if (GetAsyncKeyState(VK_LEFT) & 0x8000){ SetSelectedIndex_(selectedIndex_ - 1); }
       else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { SetSelectedIndex_(selectedIndex_ + 1); }
       else if (GetAsyncKeyState(VK_BACK) & 0x8000) {inputMethod.DeletePinyin_();}
       else if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && !currentPinyin_.empty()){name += SelectCandidate_();inputMethod.SetStatus_(false);}
   }else {//锁定大写模式

    }


    std::cout << "当拼音为："<<WStringToString(inputMethod.GetCurrentPinyin_()) << std::endl;
    std::cout << "当前下标为为："<<inputMethod.GetSelectedIndex_()<<std::endl;
    std::cout << "当前队列为：";
    for (const auto& i : candidates_) {
        std::cout << WStringToString(i.text.c_str()) <<" ";
    }
    std::cout << std::endl;
    return inputMethod.GetCandidates_();

}

// void InputMethod::SaveDictionary_(const std::string& filename) const {
//     std::wofstream file(filename);
//     file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
//
//     for (const auto& entry : dictionary_) {
//         for (const auto& word : entry.second) {
//             file << std::string(entry.first.begin(), entry.first.end())
//                  << " " << word.text << " " << word.frequency << "\n";
//         }
//     }
// }
//
// void InputMethod::LoadDictionary_(const std::string& filename) {
//     std::wifstream file(filename);
//     file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
//
//     std::string line;
//     while (std::getline(file, line)) {
//         std::stringstream ss(line);
//         std::string pinyinW, wordW;
//         int freq;
//
//         ss >> pinyinW >> wordW >> freq;
//
//         std::string pinyin(pinyinW.begin(), pinyinW.end());
//         AddWord_(pinyin, wordW, freq);
//     }
// }

InputMethod inputMethod;

// int main() {
//     std::string name;
//     std::vector<Word> words;
//     while (true) {
//
//             words = inputMethod.RunInputMethod_(name);
//             std::cout << "当拼音为："<<inputMethod.GetCurrentPinyin_() << std::endl;
//             std::cout << "已输入为："<<name<<std::endl;
//             std::cout << "当前下标为为："<<inputMethod.GetSelectedIndex_()<<std::endl;
//             std::cout << "当前队列为：";
//             for (auto i : words) {
//                 std::cout << i.text <<" ";
//             }
//             std::cout << std::endl;
//
//         Sleep(500);
//     }
// }