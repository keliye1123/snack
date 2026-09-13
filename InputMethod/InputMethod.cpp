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

//输入法词库
void InputMethod::LoadDefaultDictionary_() {
    AddWord_("ni", "你", 100);
    AddWord_("ni", "尼", 20);
    AddWord_("ni", "泥", 10);
    AddWord_("hao", "好", 100);
    AddWord_("hao", "号", 50);
    AddWord_("nihao", "你好", 150);
    AddWord_("wo", "我", 100);
    AddWord_("wo", "沃", 10);
    AddWord_("men", "们", 100);
    AddWord_("men", "门", 50);
    AddWord_("de", "的", 200);
    AddWord_("de", "地", 80);
    AddWord_("de", "得", 60);
    AddWord_("shi", "是", 150);
    AddWord_("shi", "时", 50);
    AddWord_("shi", "事", 40);
    AddWord_("zai", "在", 100);
    AddWord_("zai", "再", 60);
    AddWord_("le", "了", 150);
    AddWord_("le", "乐", 30);
    AddWord_("you", "有", 120);
    AddWord_("you", "又", 50);
    AddWord_("you", "游", 30);
    AddWord_("ta", "他", 100);
    AddWord_("ta", "她", 90);
    AddWord_("ta", "它", 40);
    AddWord_("yi", "一", 150);
    AddWord_("yi", "已", 40);
    AddWord_("yi", "以", 30);
    AddWord_("bu", "不", 150);
    AddWord_("bu", "布", 20);
    AddWord_("lai", "来", 100);
    AddWord_("lai", "莱", 10);
    AddWord_("qu", "去", 100);
    AddWord_("qu", "区", 30);
    AddWord_("kan", "看", 80);
    AddWord_("kan", "刊", 20);
    AddWord_("shuo", "说", 80);
    AddWord_("shuo", "硕", 10);
    AddWord_("zhe", "这", 120);
    AddWord_("zhe", "着", 60);
    AddWord_("na", "那", 100);
    AddWord_("na", "哪", 50);
    AddWord_("na", "拿", 40);
    AddWord_("hen", "很", 80);
    AddWord_("hen", "狠", 20);
    AddWord_("dou", "都", 90);
    AddWord_("dou", "斗", 20);
    AddWord_("da", "大", 100);
    AddWord_("da", "打", 80);
    AddWord_("da", "答", 40);
    AddWord_("xiao", "小", 90);
    AddWord_("xiao", "笑", 60);
    AddWord_("xiao", "校", 40);
    AddWord_("shang", "上", 100);
    AddWord_("shang", "商", 40);
    AddWord_("xia", "下", 100);
    AddWord_("xia", "夏", 30);
    AddWord_("zhong", "中", 100);
    AddWord_("zhong", "重", 50);
    AddWord_("zhong", "终", 30);
    AddWord_("guo", "国", 100);
    AddWord_("guo", "过", 80);
    AddWord_("guo", "果", 40);
    AddWord_("ren", "人", 150);
    AddWord_("ren", "任", 40);
    AddWord_("ren", "认", 30);
    AddWord_("ming", "名", 80);
    AddWord_("ming", "明", 60);
    AddWord_("zi", "字", 70);
    AddWord_("zi", "自", 60);
    AddWord_("zi", "子", 50);
    AddWord_("jia", "家", 90);
    AddWord_("jia", "加", 60);
    AddWord_("jia", "假", 40);
    AddWord_("she", "社", 60);
    AddWord_("she", "设", 50);
    AddWord_("she", "舍", 30);
    AddWord_("hui", "会", 100);
    AddWord_("hui", "回", 80);
    AddWord_("hui", "汇", 30);
}

//初始化（初始当前选择的下标和加载词库）
InputMethod::InputMethod() : selectedIndex_(0) {
    std::cout << "词库初始化成功" << std::endl;
    LoadDefaultDictionary_();
}


//添加词
void InputMethod::AddWord_(const std::string& pinyin, const std::string& word, int frequency) {
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

std::string InputMethod::SelectCandidate_(int index) {
    if (index >= 0 && index < static_cast<int>(candidates_.size())) {
        std::string selectedWord = candidates_[index].text;

        dictionary_[currentPinyin_][index].frequency++;

        ClearPinyin_();
        return selectedWord;
    }
    return "";
}

std::string InputMethod::GetCurrentPinyin_() const {
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

bool GetCaps_() {
    return GetAsyncKeyState(VK_CAPITAL) & 1;
}

void InputMethod::RunInputMethod_(int& len ) {
   if (!GetCaps_()) {
       if (GetAsyncKeyState('A') & 0x8000) { inputMethod.InputPinyin_('a'); }
       else if (GetAsyncKeyState('B') & 0x8000) { inputMethod.InputPinyin_('b'); }
       else if (GetAsyncKeyState('C') & 0x8000) { inputMethod.InputPinyin_('c'); }
       else if (GetAsyncKeyState('D') & 0x8000) { inputMethod.InputPinyin_('d'); }
       else if (GetAsyncKeyState('E') & 0x8000) { inputMethod.InputPinyin_('e'); }
       else if (GetAsyncKeyState('F') & 0x8000) { inputMethod.InputPinyin_('f'); }
       else if (GetAsyncKeyState('G') & 0x8000) { inputMethod.InputPinyin_('g'); }
       else if (GetAsyncKeyState('H') & 0x8000) { inputMethod.InputPinyin_('h'); }
       else if (GetAsyncKeyState('I') & 0x8000) { inputMethod.InputPinyin_('i'); }
       else if (GetAsyncKeyState('J') & 0x8000) { inputMethod.InputPinyin_('j'); }
       else if (GetAsyncKeyState('K') & 0x8000) { inputMethod.InputPinyin_('k'); }
       else if (GetAsyncKeyState('L') & 0x8000) { inputMethod.InputPinyin_('l'); }
       else if (GetAsyncKeyState('M') & 0x8000) { inputMethod.InputPinyin_('m'); }
       else if (GetAsyncKeyState('N') & 0x8000) { inputMethod.InputPinyin_('n'); }
       else if (GetAsyncKeyState('O') & 0x8000) { inputMethod.InputPinyin_('o'); }
       else if (GetAsyncKeyState('P') & 0x8000) { inputMethod.InputPinyin_('p'); }
       else if (GetAsyncKeyState('Q') & 0x8000) { inputMethod.InputPinyin_('q'); }
       else if (GetAsyncKeyState('R') & 0x8000) { inputMethod.InputPinyin_('r'); }
       else if (GetAsyncKeyState('S') & 0x8000) { inputMethod.InputPinyin_('s'); }
       else if (GetAsyncKeyState('T') & 0x8000) { inputMethod.InputPinyin_('t'); }
       else if (GetAsyncKeyState('U') & 0x8000) { inputMethod.InputPinyin_('u'); }
       else if (GetAsyncKeyState('V') & 0x8000) { inputMethod.InputPinyin_('v'); }
       else if (GetAsyncKeyState('W') & 0x8000) { inputMethod.InputPinyin_('w'); }
       else if (GetAsyncKeyState('X') & 0x8000) { inputMethod.InputPinyin_('x'); }
       else if (GetAsyncKeyState('Y') & 0x8000) { inputMethod.InputPinyin_('y'); }
       else if (GetAsyncKeyState('Z') & 0x8000) { inputMethod.InputPinyin_('z'); }
       else if (GetAsyncKeyState(VK_LEFT) & 0x8000){ SetSelectedIndex_(selectedIndex_ - 1); }
       else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { SetSelectedIndex_(selectedIndex_ + 1); }
       if (GetAsyncKeyState(VK_BACK) & 0x8000) {inputMethod.DeletePinyin_();};
   }else {

    }

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

int main() {
    for (int i = 0;i < 10;i++) {
        std::cout << "当前拼音为：" << inputMethod.GetCurrentPinyin_() << std::endl;
        char temp;
        std::cin >> temp;
        if (temp == 127) {
            inputMethod.DeletePinyin_();
            continue;
        }
        inputMethod.InputPinyin_(temp);
        std::vector<Word> res = inputMethod.GetCandidates_();
        std::cout << "队列为："<< res.size() << std::endl;
        for (const auto& c : res) {
            std::cout << c.text << std::endl;
        }

    }
}