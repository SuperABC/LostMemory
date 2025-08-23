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

    // ��ʼ�������б�
    void InitializeSurnames();

    // ��ʼ�������б�
    void InitializeNames();

    // �����������
    std::string GenerateName(bool male = true, bool female = true, bool neutral = true);
};