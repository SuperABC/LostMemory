#pragma once
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4150)

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <algorithm>


// ��������ö��
enum Attribute {
    ATTRIBUTE_NONE, // ������
    ATTRIBUTE_METAL, // ��
    ATTRIBUTE_WOOD, // ľ
    ATTRIBUTE_WATER, // ˮ
    ATTRIBUTE_FIRE, // ��
    ATTRIBUTE_EARTH, // ��
    ATTRIBUTE_ALL // ����
};

// ��λö��
enum Realm {
    YELLOW_INIT, //�ƽ׳���
    YELLOW_INIT_PEAK, //�ƽ׳����۷�
    YELLOW_MID, //�ƽ�����
    YELLOW_MID_PEAK, //�ƽ������۷�
    YELLOW_LATE, //�ƽ׺���
    YELLOW_LATE_PEAK, //�ƽ׺����۷�
    MYSTIC_INIT, //���׳���
    MYSTIC_INIT_PEAK, //���׳����۷�
    MYSTIC_MID, //��������
    MYSTIC_MID_PEAK, //���������۷�
    MYSTIC_LATE, //���׺���
    MYSTIC_LATE_PEAK, //���׺����۷�
    EARTH_INIT, //�ؽ׳���
    EARTH_INIT_PEAK, //�ؽ׳����۷�
    EARTH_MID, //�ؽ�����
    EARTH_MID_PEAK, //�ؽ������۷�
    EARTH_LATE, //�ؽӺ���
    EARTH_LATE_PEAK, //�ؽ׺����۷�
    HEAVEN_INIT, //��׳���
    HEAVEN_INIT_PEAK, //��׳����۷�
    HEAVEN_MID, //�������
    HEAVEN_MID_PEAK, //��������۷�
    HEAVEN_LATE, //��׺���
    HEAVEN_LATE_PEAK //��׺����۷�
};

// ���Կ��ƹ�ϵ
const std::map<std::pair<Attribute, Attribute>, bool> ATTRIBUTE_COUNTERS = {
    {{ATTRIBUTE_WATER, ATTRIBUTE_FIRE}, true}, //ˮ�˻�
    {{ATTRIBUTE_FIRE, ATTRIBUTE_WOOD}, true}, //���ľ
    {{ATTRIBUTE_WOOD, ATTRIBUTE_WATER}, true}, //ľ��ˮ
    {{ATTRIBUTE_EARTH, ATTRIBUTE_METAL}, true}, //���˽�
    {{ATTRIBUTE_METAL, ATTRIBUTE_WOOD}, true}, //���ľ
    {{ATTRIBUTE_WOOD, ATTRIBUTE_EARTH}, true}, //ľ����
    {{ATTRIBUTE_ALL, ATTRIBUTE_METAL}, true}, //���п˽�
    {{ATTRIBUTE_ALL, ATTRIBUTE_WOOD}, true}, //���п�ľ
    {{ATTRIBUTE_ALL, ATTRIBUTE_WATER}, true}, //���п�ˮ
    {{ATTRIBUTE_ALL, ATTRIBUTE_FIRE}, true}, //���п˻�
    {{ATTRIBUTE_ALL, ATTRIBUTE_EARTH}, true}, //���п���
};

// ˫�������������ӳ��
const std::map<std::pair<Attribute, Attribute>, Attribute> DUAL_ATTRIBUTE_PRIMARY = {
    {{ATTRIBUTE_WOOD, ATTRIBUTE_FIRE}, ATTRIBUTE_FIRE},
    {{ATTRIBUTE_FIRE, ATTRIBUTE_EARTH}, ATTRIBUTE_EARTH},
    {{ATTRIBUTE_EARTH, ATTRIBUTE_METAL}, ATTRIBUTE_EARTH},
    {{ATTRIBUTE_METAL, ATTRIBUTE_WATER}, ATTRIBUTE_WATER},
    {{ATTRIBUTE_WATER, ATTRIBUTE_WOOD}, ATTRIBUTE_WOOD},
    {{ATTRIBUTE_FIRE, ATTRIBUTE_METAL}, ATTRIBUTE_METAL},
    {{ATTRIBUTE_METAL, ATTRIBUTE_WOOD}, ATTRIBUTE_METAL},
    {{ATTRIBUTE_WOOD, ATTRIBUTE_EARTH}, ATTRIBUTE_WOOD},
    {{ATTRIBUTE_EARTH, ATTRIBUTE_WATER}, ATTRIBUTE_EARTH},
    {{ATTRIBUTE_WATER, ATTRIBUTE_FIRE}, ATTRIBUTE_WATER},
    {{ATTRIBUTE_ALL, ATTRIBUTE_METAL}, ATTRIBUTE_METAL},
    {{ATTRIBUTE_ALL, ATTRIBUTE_WOOD}, ATTRIBUTE_WOOD},
    {{ATTRIBUTE_ALL, ATTRIBUTE_WATER}, ATTRIBUTE_WATER},
    {{ATTRIBUTE_ALL, ATTRIBUTE_FIRE}, ATTRIBUTE_FIRE},
    {{ATTRIBUTE_ALL, ATTRIBUTE_EARTH}, ATTRIBUTE_EARTH}
};

// ��λҪ�����СATKֵ
const std::map<Realm, int> REALM_ATK_REQUIREMENTS = {
    // �ƽ�
    {Realm::YELLOW_INIT, 20},
    {Realm::YELLOW_INIT_PEAK, 30},
    {Realm::YELLOW_MID, 40},
    {Realm::YELLOW_MID_PEAK, 50},
    {Realm::YELLOW_LATE, 60},
    {Realm::YELLOW_LATE_PEAK, 80},

    // ����
    {Realm::MYSTIC_INIT, 100},
    {Realm::MYSTIC_INIT_PEAK, 120},
    {Realm::MYSTIC_MID, 140},
    {Realm::MYSTIC_MID_PEAK, 160},
    {Realm::MYSTIC_LATE, 180},
    {Realm::MYSTIC_LATE_PEAK, 200},

    // �ؽ�
    {Realm::EARTH_INIT, 250},
    {Realm::EARTH_INIT_PEAK, 300},
    {Realm::EARTH_MID, 350},
    {Realm::EARTH_MID_PEAK, 400},
    {Realm::EARTH_LATE, 450},
    {Realm::EARTH_LATE_PEAK, 500},

    // ���
    {Realm::HEAVEN_INIT, 600},
    {Realm::HEAVEN_INIT_PEAK, 700},
    {Realm::HEAVEN_MID, 800},
    {Realm::HEAVEN_MID_PEAK, 900},
    {Realm::HEAVEN_LATE, 1000},
    {Realm::HEAVEN_LATE_PEAK, 1200}
};