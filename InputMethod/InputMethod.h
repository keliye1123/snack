# pragma once
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <windows.h>

struct Word {
    std::wstring text;
    int frequency;

    Word(std::wstring  t = L"", int f = 0) : text(std::move(t)), frequency(f) {}
};

class InputMethod {
    //属性
private:
    std::unordered_map<std::wstring, std::vector<Word>> dictionary_;     //词库
    std::wstring currentPinyin_;                                         //当前的拼音
    std::vector<Word> candidates_;                                      //当前拼音对用的汉字数组
    int selectedIndex_;                                                 //当前选择的数组下标
    bool IsRun_;                                                        //是否处于运行状态
    bool IsChinese;                                                     //是否处于中文输入法

    //方法
private:
    void LoadDefaultDictionary_();
    void SortCandidates_();

public:
    InputMethod();

    void Draw_();       //渲染输入法窗口

    static std::string WStringToString(const std::wstring& wstr);//wstring转string

    static std::wstring StringToWstring(const std::string& str);//string转wstring

    void AddWord_(const std::wstring& pinyin, const std::wstring& word, int frequency = 1);

    void SetStatus_(bool s);

    [[nodiscard]] bool GetStatus_() const;

    void InputPinyin_(char c);//输入拼音
    void DeletePinyin_();//删除拼音
    void ClearPinyin_();//清空拼音

    [[nodiscard]] std::vector<Word> GetCandidates_() const;//获得队列
    std::wstring SelectCandidate_();//获得选中的汉字

    [[nodiscard]] std::wstring GetCurrentPinyin_() const;
    [[nodiscard]] int GetSelectedIndex_() const;
    void SetSelectedIndex_(int index);

    static bool GetCaps_() ;

    std::vector<Word> RunInputMethod_(std::string& name_);//运行

    // void SaveDictionary_(const std::string& filename) const;
    // void LoadDictionary_(const std::string& filename);
};

extern InputMethod inputMethod;

