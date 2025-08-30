﻿#pragma once
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


// 五行属性枚举
enum Attribute {
    ATTRIBUTE_NONE, // 无属性
    ATTRIBUTE_METAL, // 金
    ATTRIBUTE_WOOD, // 木
    ATTRIBUTE_WATER, // 水
    ATTRIBUTE_FIRE, // 火
    ATTRIBUTE_EARTH, // 土
    ATTRIBUTE_ALL // 五行
};

// 阶位枚举
enum Realm {
    YELLOW_INIT, //黄阶初期
    YELLOW_INIT_PEAK, //黄阶初期巅峰
    YELLOW_MID, //黄阶中期
    YELLOW_MID_PEAK, //黄阶中期巅峰
    YELLOW_LATE, //黄阶后期
    YELLOW_LATE_PEAK, //黄阶后期巅峰
    MYSTIC_INIT, //玄阶初期
    MYSTIC_INIT_PEAK, //玄阶初期巅峰
    MYSTIC_MID, //玄阶中期
    MYSTIC_MID_PEAK, //玄阶中期巅峰
    MYSTIC_LATE, //玄阶后期
    MYSTIC_LATE_PEAK, //玄阶后期巅峰
    EARTH_INIT, //地阶初期
    EARTH_INIT_PEAK, //地阶初期巅峰
    EARTH_MID, //地阶中期
    EARTH_MID_PEAK, //地阶中期巅峰
    EARTH_LATE, //地接后期
    EARTH_LATE_PEAK, //地阶后期巅峰
    HEAVEN_INIT, //天阶初期
    HEAVEN_INIT_PEAK, //天阶初期巅峰
    HEAVEN_MID, //天阶中期
    HEAVEN_MID_PEAK, //天阶中期巅峰
    HEAVEN_LATE, //天阶后期
    HEAVEN_LATE_PEAK //天阶后期巅峰
};

// 属性克制关系
const std::map<std::pair<Attribute, Attribute>, bool> ATTRIBUTE_COUNTERS = {
    {{ATTRIBUTE_WATER, ATTRIBUTE_FIRE}, true}, //水克火
    {{ATTRIBUTE_FIRE, ATTRIBUTE_WOOD}, true}, //火克木
    {{ATTRIBUTE_WOOD, ATTRIBUTE_WATER}, true}, //木克水
    {{ATTRIBUTE_EARTH, ATTRIBUTE_METAL}, true}, //土克金
    {{ATTRIBUTE_METAL, ATTRIBUTE_WOOD}, true}, //金克木
    {{ATTRIBUTE_WOOD, ATTRIBUTE_EARTH}, true}, //木克土
    {{ATTRIBUTE_ALL, ATTRIBUTE_METAL}, true}, //五行克金
    {{ATTRIBUTE_ALL, ATTRIBUTE_WOOD}, true}, //五行克木
    {{ATTRIBUTE_ALL, ATTRIBUTE_WATER}, true}, //五行克水
    {{ATTRIBUTE_ALL, ATTRIBUTE_FIRE}, true}, //五行克火
    {{ATTRIBUTE_ALL, ATTRIBUTE_EARTH}, true}, //五行克土
};

// 双属性组合主属性映射
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

// 阶位要求的最小ATK值
const std::map<Realm, int> REALM_ATK_REQUIREMENTS = {
    // 黄阶
    {Realm::YELLOW_INIT, 20},
    {Realm::YELLOW_INIT_PEAK, 30},
    {Realm::YELLOW_MID, 40},
    {Realm::YELLOW_MID_PEAK, 50},
    {Realm::YELLOW_LATE, 60},
    {Realm::YELLOW_LATE_PEAK, 80},

    // 玄阶
    {Realm::MYSTIC_INIT, 100},
    {Realm::MYSTIC_INIT_PEAK, 120},
    {Realm::MYSTIC_MID, 140},
    {Realm::MYSTIC_MID_PEAK, 160},
    {Realm::MYSTIC_LATE, 180},
    {Realm::MYSTIC_LATE_PEAK, 200},

    // 地阶
    {Realm::EARTH_INIT, 250},
    {Realm::EARTH_INIT_PEAK, 300},
    {Realm::EARTH_MID, 350},
    {Realm::EARTH_MID_PEAK, 400},
    {Realm::EARTH_LATE, 450},
    {Realm::EARTH_LATE_PEAK, 500},

    // 天阶
    {Realm::HEAVEN_INIT, 600},
    {Realm::HEAVEN_INIT_PEAK, 700},
    {Realm::HEAVEN_MID, 800},
    {Realm::HEAVEN_MID_PEAK, 900},
    {Realm::HEAVEN_LATE, 1000},
    {Realm::HEAVEN_LATE_PEAK, 1200}
};