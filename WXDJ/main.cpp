#include "player.h"
#include "controller.h"

#include <iostream>
#include <algorithm>


using namespace std;

std::vector<Action *> actions = {
    new MoveAction("基础掌法", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new MoveAction("基础拳法", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new MoveAction("基础腿法", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),

    new MoveAction("进阶掌法", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new MoveAction("进阶拳法", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new MoveAction("进阶腿法", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
    new MoveAction("突破掌法", ATTRIBUTE_NONE, 34, 22, Realm::MYSTIC_MID),
    new MoveAction("突破拳法", ATTRIBUTE_NONE, 40, 26, Realm::MYSTIC_MID),
    new MoveAction("突破腿法", ATTRIBUTE_NONE, 45, 30, Realm::MYSTIC_MID),
    new MoveAction("自由掌法", ATTRIBUTE_NONE, 40, 25, Realm::MYSTIC_LATE),
    new MoveAction("自由拳法", ATTRIBUTE_NONE, 48, 30, Realm::MYSTIC_LATE),
    new MoveAction("自由腿法", ATTRIBUTE_NONE, 55, 35, Realm::MYSTIC_LATE),

    new MoveAction("千腿第一式", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("千腿第二式", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("千腿第三式", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID),
    new MoveAction("千腿第四式", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("千腿第五式", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("千腿第六式", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("千腿第七式", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("千腿第八式", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("千腿第九式", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("千腿第十式", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("千腿第十一式", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("千腿第十二式", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("千腿第十三式", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("千腿第十四式", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("千腿第十五式", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("千腿第十六式", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("千腿第十七式", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("千腿第十八式", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("千腿第十九式", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("千腿第二十式", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("开天辟地爪第一式", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("开天辟地爪第二式", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("开天辟地爪第三式", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID),
    new MoveAction("开天辟地爪第四式", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("开天辟地爪第五式", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("开天辟地爪第六式", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("开天辟地爪第七式", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("开天辟地爪第八式", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("开天辟地爪第九式", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("开天辟地爪第十式", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("开天辟地爪第十一式", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("开天辟地爪第十二式", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("开天辟地爪第十三式", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("开天辟地爪第十四式", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("开天辟地爪第十五式", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("开天辟地爪第十六式", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("开天辟地爪第十七式", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("开天辟地爪第十八式", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("开天辟地爪第十九式", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("开天辟地爪第二十式", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("伏羲九针第一式", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new MoveAction("伏羲九针第二式", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("伏羲九针第三式", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new MoveAction("伏羲九针第四式", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("伏羲九针第五式", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new MoveAction("伏羲九针第六式", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("伏羲九针第七式", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("伏羲九针第八式", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("伏羲九针第九式", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("伏羲九针第十式", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("伏羲九针第十一式", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("伏羲九针第十二式", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("伏羲九针第十三式", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("伏羲九针第十四式", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("伏羲九针第十五式", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("伏羲九针第十六式", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("伏羲九针第十七式", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("伏羲九针第十八式", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("伏羲九针第十九式", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("伏羲九针第二十式", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("千刃斩第一式", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new MoveAction("千刃斩第二式", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("千刃斩第三式", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new MoveAction("千刃斩第四式", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("千刃斩第五式", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new MoveAction("千刃斩第六式", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("千刃斩第七式", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("千刃斩第八式", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("千刃斩第九式", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("千刃斩第十式", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("千刃斩第十一式", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("千刃斩第十二式", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("千刃斩第十三式", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("千刃斩第十四式", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("千刃斩第十五式", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("千刃斩第十六式", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("千刃斩第十七式", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("千刃斩第十八式", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("千刃斩第十九式", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("千刃斩第二十式", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("砍柴功第一式", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new MoveAction("砍柴功第二式", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("砍柴功第三式", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new MoveAction("砍柴功第四式", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("砍柴功第五式", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new MoveAction("砍柴功第六式", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("砍柴功第七式", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("砍柴功第八式", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("砍柴功第九式", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("砍柴功第十式", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("砍柴功第十一式", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("砍柴功第十二式", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("砍柴功第十三式", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("砍柴功第十四式", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("砍柴功第十五式", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("砍柴功第十六式", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("砍柴功第十七式", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("砍柴功第十八式", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("砍柴功第十九式", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("砍柴功第二十式", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("木森林变换第一式", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new MoveAction("木森林变换第二式", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("木森林变换第三式", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new MoveAction("木森林变换第四式", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("木森林变换第五式", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new MoveAction("木森林变换第六式", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("木森林变换第七式", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("木森林变换第八式", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("木森林变换第九式", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("木森林变换第十式", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("木森林变换第十一式", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("木森林变换第十二式", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("木森林变换第十三式", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("木森林变换第十四式", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("木森林变换第十五式", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("木森林变换第十六式", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("木森林变换第十七式", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("木森林变换第十八式", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("木森林变换第十九式", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("木森林变换第二十式", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("海龙金身第一式", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new MoveAction("海龙金身第二式", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("海龙金身第三式", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new MoveAction("海龙金身第四式", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("海龙金身第五式", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new MoveAction("海龙金身第六式", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("海龙金身第七式", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("海龙金身第八式", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("海龙金身第九式", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("海龙金身第十式", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("海龙金身第十一式", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("海龙金身第十二式", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("海龙金身第十三式", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("海龙金身第十四式", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("海龙金身第十五式", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("海龙金身第十六式", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("海龙金身第十七式", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("海龙金身第十八式", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("海龙金身第十九式", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("海龙金身第二十式", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("天降春雨第一式", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new MoveAction("天降春雨第二式", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("天降春雨第三式", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new MoveAction("天降春雨第四式", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("天降春雨第五式", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new MoveAction("天降春雨第六式", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("天降春雨第七式", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("天降春雨第八式", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("天降春雨第九式", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("天降春雨第十式", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("天降春雨第十一式", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("天降春雨第十二式", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("天降春雨第十三式", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("天降春雨第十四式", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("天降春雨第十五式", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("天降春雨第十六式", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("天降春雨第十七式", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("天降春雨第十八式", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("天降春雨第十九式", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("天降春雨第二十式", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("焚天第一式", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("焚天第二式", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("焚天第三式", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new MoveAction("焚天第四式", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("焚天第五式", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("焚天第六式", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("焚天第七式", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("焚天第八式", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("焚天第九式", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("焚天第十式", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("焚天第十一式", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("焚天第十二式", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("焚天第十三式", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("焚天第十四式", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("焚天第十五式", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("焚天第十六式", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("焚天第十七式", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("焚天第十八式", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("焚天第十九式", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("焚天第二十式", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("狂火拳第一式", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("狂火拳第二式", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("狂火拳第三式", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new MoveAction("狂火拳第四式", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("狂火拳第五式", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("狂火拳第六式", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("狂火拳第七式", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("狂火拳第八式", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("狂火拳第九式", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("狂火拳第十式", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("狂火拳第十一式", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("狂火拳第十二式", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("狂火拳第十三式", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("狂火拳第十四式", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("狂火拳第十五式", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("狂火拳第十六式", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("狂火拳第十七式", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("狂火拳第十八式", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("狂火拳第十九式", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("狂火拳第二十式", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("荒星第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("荒星第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("荒星第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("荒星第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("荒星第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("荒星第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("荒星第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("荒星第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("荒星第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("荒星第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("荒星第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("荒星第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("荒星第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("荒星第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("荒星第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("荒星第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("荒星第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("荒星第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("荒星第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("荒星第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("地狱阴魔拳第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("地狱阴魔拳第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("地狱阴魔拳第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("地狱阴魔拳第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("地狱阴魔拳第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("地狱阴魔拳第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("地狱阴魔拳第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("地狱阴魔拳第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("地狱阴魔拳第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("地狱阴魔拳第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("地狱阴魔拳第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("地狱阴魔拳第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("地狱阴魔拳第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("地狱阴魔拳第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("地狱阴魔拳第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("地狱阴魔拳第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("地狱阴魔拳第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("地狱阴魔拳第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("地狱阴魔拳第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("地狱阴魔拳第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("五行八卦掌第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("五行八卦掌第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("五行八卦掌第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("五行八卦掌第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("五行八卦掌第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("五行八卦掌第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("五行八卦掌第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("五行八卦掌第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("五行八卦掌第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("五行八卦掌第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("五行八卦掌第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("五行八卦掌第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("五行八卦掌第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("五行八卦掌第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("五行八卦掌第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("五行八卦掌第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("五行八卦掌第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("五行八卦掌第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("五行八卦掌第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("五行八卦掌第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

};
int GetRandom(int range) {
    if (range <= 0)return 0;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, range - 1);
    int ret = dist(rng);

    return ret;
}

int main() {
    Player player1("张三", 1000, 1200, 720, 20, 40);
    Player player2("李四", 1000, 1080, 800, 22, 40);
    player1.AddAction(new SkipAction());
    player2.AddAction(new SkipAction());
    for (auto action : actions) {
        player1.AddAction(action);
        player2.AddAction(action);
    }

    Controller game(&player1, &player2);

    cout << "《五行斗诀》战斗开始！" << endl;
    cout << player1.GetName() << " VS " << player2.GetName() <<  std::endl;

    int turnCount = 0;
    while (player1.IsAlive() && player2.IsAlive()) {
        cout << "\n--- 第 " << ++turnCount << " 回合 ---" << endl;
        cout << player1.GetName() << ": HP=" << player1.GetCurrentHP()
            << ", ATK=" << player1.GetCurrentATK()
            << ", MP=" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << ": HP=" << player2.GetCurrentHP()
            << ", ATK=" << player2.GetCurrentATK()
            << ", MP=" << player2.GetCurrentMP() << endl;

        game.StartTurn();
        cout << player1.GetName() << "真气量回复至" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << "真气量回复至" << player2.GetCurrentMP() << endl;

        Action *action1 = player1.GetActions()[GetRandom(actions.size() + 1)];
        Action* action2 = player2.GetActions()[GetRandom(actions.size() + 1)];
        game.ActionTurn(action1, action2);
        if (action1->GetType() == ACTION_SKIP) {
            cout << player1.GetName() << "跳过回合" << endl;
        }
        else {
            cout << player1.GetName() << "出招：" << ((MoveAction *)action1)->GetName() <<
                "，消耗" << action1->GetPower() << "真气量，点数" << action1->GetPoint() << endl;
        }
        if (action2->GetType() == ACTION_SKIP) {
            cout << player2.GetName() << "跳过回合" << endl;
        }
        else {
            cout << player2.GetName() << "出招：" << ((MoveAction*)action2)->GetName() <<
                "，消耗" << action2->GetPower() << "真气量，点数" << action2->GetPoint() << endl;
        }

        auto check = game.CheckTurn(action1, action2);
        if (check.first == 0) {
            cout << player1.GetName() << "未受伤害" << endl;
        }
        else {
            cout << player1.GetName() << "受到" << check.first << "伤害" << endl;
        }
        if (check.second == 0) {
            cout << player2.GetName() << "未受伤害" << endl;
        }
        else {
            cout << player2.GetName() << "受到" << check.second << "伤害" << endl;
        }

        game.EndTurn();
        cout << "回合结束" << endl;
    }

    if (!player1.IsAlive() && !player2.IsAlive()) {
        cout << "\n战斗结束！同归于尽!" << endl;
    }
    else {
        cout << "\n战斗结束！胜利者: " << (player1.IsAlive() ? player1 : player2).GetName() << "!" << endl;
    }
}