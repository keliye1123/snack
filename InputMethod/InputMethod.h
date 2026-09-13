# pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <windows.h>

struct Word {
    std::string text;
    int frequency;

    Word(const std::string& t = "", int f = 0) : text(t), frequency(f) {}
};

class InputMethod {
    //属性
private:
    std::unordered_map<std::string, std::vector<Word>> dictionary_;     //词库
    std::string currentPinyin_;                                         //当前的拼音
    std::vector<Word> candidates_;                                      //当前拼音对用的汉字数组
    int selectedIndex_;                                                 //当前选择的数组下标

    //方法
private:
    void LoadDefaultDictionary_();
    void SortCandidates_();

public:
    InputMethod();

    void AddWord_(const std::string& pinyin, const std::string& word, int frequency = 1);

    void InputPinyin_(char c);
    void DeletePinyin_();
    void ClearPinyin_();

    std::vector<Word> GetCandidates_() const;
    std::string SelectCandidate_(int index);

    std::string GetCurrentPinyin_() const;
    int GetSelectedIndex_() const;
    void SetSelectedIndex_(int index);

    bool GetCaps_() const;

    void RunInputMethod_(int& len);//运行

    // void SaveDictionary_(const std::string& filename) const;
    // void LoadDictionary_(const std::string& filename);
};

extern InputMethod inputMethod;

