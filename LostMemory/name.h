#pragma once

#include "util.h"

#include <vector>
#include <string>
#include <random>
#include <ctime>

class ChineseNameGenerator {
private:
    std::vector<std::string> surnames;
    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;
    std::vector<std::string> neutralNames;

public:
    ChineseNameGenerator();

    // 初始化姓氏列表
    void InitializeSurnames();

    // 初始化名字列表
    void InitializeNames();

    // 生成随机姓名
    std::string GenerateName(bool male = true, bool female = true, bool neutral = true);
};