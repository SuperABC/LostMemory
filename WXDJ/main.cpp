#include "player.h"
#include "controller.h"

#include <iostream>
#include <algorithm>


using namespace std;

std::vector<Action *> actions = {
    new MoveAction("�����Ʒ�", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new MoveAction("����ȭ��", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new MoveAction("�����ȷ�", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),

    new MoveAction("�����Ʒ�", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new MoveAction("����ȭ��", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new MoveAction("�����ȷ�", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
    new MoveAction("ͻ���Ʒ�", ATTRIBUTE_NONE, 34, 22, Realm::MYSTIC_MID),
    new MoveAction("ͻ��ȭ��", ATTRIBUTE_NONE, 40, 26, Realm::MYSTIC_MID),
    new MoveAction("ͻ���ȷ�", ATTRIBUTE_NONE, 45, 30, Realm::MYSTIC_MID),
    new MoveAction("�����Ʒ�", ATTRIBUTE_NONE, 40, 25, Realm::MYSTIC_LATE),
    new MoveAction("����ȭ��", ATTRIBUTE_NONE, 48, 30, Realm::MYSTIC_LATE),
    new MoveAction("�����ȷ�", ATTRIBUTE_NONE, 55, 35, Realm::MYSTIC_LATE),

    new MoveAction("ǧ�ȵ�һʽ", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("ǧ�ȵڶ�ʽ", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID),
    new MoveAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("ǧ�ȵڰ�ʽ", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("ǧ�ȵھ�ʽ", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ǧ�ȵ�ʮʽ", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ǧ�ȵ�ʮһʽ", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ǧ�ȵڶ�ʮʽ", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("����ٵ�צ��һʽ", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("����ٵ�צ�ڶ�ʽ", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID),
    new MoveAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("����ٵ�צ�ڰ�ʽ", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("����ٵ�צ�ھ�ʽ", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("����ٵ�צ��ʮʽ", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("����ٵ�צ��ʮһʽ", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("����ٵ�צ�ڶ�ʮʽ", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���˾����һʽ", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new MoveAction("���˾���ڶ�ʽ", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("���˾������ʽ", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new MoveAction("���˾������ʽ", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("���˾������ʽ", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new MoveAction("���˾������ʽ", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("���˾������ʽ", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("���˾���ڰ�ʽ", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("���˾���ھ�ʽ", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���˾����ʮʽ", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���˾����ʮһʽ", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���˾���ڶ�ʮʽ", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("ǧ��ն��һʽ", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new MoveAction("ǧ��ն�ڶ�ʽ", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new MoveAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new MoveAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("ǧ��ն�ڰ�ʽ", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("ǧ��ն�ھ�ʽ", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ǧ��ն��ʮʽ", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ǧ��ն��ʮһʽ", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ǧ��ն�ڶ�ʮʽ", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���񹦵�һʽ", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new MoveAction("���񹦵ڶ�ʽ", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new MoveAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new MoveAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("���񹦵ڰ�ʽ", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("���񹦵ھ�ʽ", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���񹦵�ʮʽ", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���񹦵�ʮһʽ", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���񹦵ڶ�ʮʽ", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("ľɭ�ֱ任��һʽ", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new MoveAction("ľɭ�ֱ任�ڶ�ʽ", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new MoveAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new MoveAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("ľɭ�ֱ任�ڰ�ʽ", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("ľɭ�ֱ任�ھ�ʽ", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ľɭ�ֱ任��ʮʽ", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("ľɭ�ֱ任��ʮһʽ", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("ľɭ�ֱ任�ڶ�ʮʽ", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���������һʽ", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new MoveAction("��������ڶ�ʽ", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("�����������ʽ", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new MoveAction("�����������ʽ", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("�����������ʽ", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new MoveAction("�����������ʽ", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("�����������ʽ", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("��������ڰ�ʽ", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("��������ھ�ʽ", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���������ʮʽ", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���������ʮһʽ", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("��������ڶ�ʮʽ", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("�콵�����һʽ", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new MoveAction("�콵����ڶ�ʽ", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("�콵�������ʽ", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new MoveAction("�콵�������ʽ", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("�콵�������ʽ", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new MoveAction("�콵�������ʽ", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("�콵�������ʽ", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("�콵����ڰ�ʽ", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("�콵����ھ�ʽ", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("�콵�����ʮʽ", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("�콵�����ʮһʽ", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("�콵����ڶ�ʮʽ", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("�����һʽ", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("����ڶ�ʽ", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("�������ʽ", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new MoveAction("�������ʽ", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("�������ʽ", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("�������ʽ", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("�������ʽ", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("����ڰ�ʽ", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("����ھ�ʽ", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("�����ʮʽ", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("�����ʮһʽ", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("����ڶ�ʮʽ", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���ȭ��һʽ", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new MoveAction("���ȭ�ڶ�ʽ", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new MoveAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new MoveAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("���ȭ�ڰ�ʽ", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("���ȭ�ھ�ʽ", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���ȭ��ʮʽ", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���ȭ��ʮһʽ", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���ȭ�ڶ�ʮʽ", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���ǵ�һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("���ǵڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("���ǵڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("���ǵھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���ǵ�ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���ǵ�ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���ǵڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("������ħȭ��һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("������ħȭ�ڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("������ħȭ�ڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("������ħȭ�ھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("������ħȭ��ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("������ħȭ��ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("������ħȭ�ڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new MoveAction("���а����Ƶ�һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new MoveAction("���а����Ƶڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new MoveAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new MoveAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new MoveAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new MoveAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new MoveAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new MoveAction("���а����Ƶڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new MoveAction("���а����Ƶھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���а����Ƶ�ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new MoveAction("���а����Ƶ�ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new MoveAction("���а����Ƶڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

};
int GetRandom(int range) {
    if (range <= 0)return 0;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, range - 1);
    int ret = dist(rng);

    return ret;
}

int main() {
    Player player1("����", 1000, 1200, 720, 20, 40);
    Player player2("����", 1000, 1080, 800, 22, 40);
    player1.AddAction(new SkipAction());
    player2.AddAction(new SkipAction());
    for (auto action : actions) {
        player1.AddAction(action);
        player2.AddAction(action);
    }

    Controller game(&player1, &player2);

    cout << "�����ж�����ս����ʼ��" << endl;
    cout << player1.GetName() << " VS " << player2.GetName() <<  std::endl;

    int turnCount = 0;
    while (player1.IsAlive() && player2.IsAlive()) {
        cout << "\n--- �� " << ++turnCount << " �غ� ---" << endl;
        cout << player1.GetName() << ": HP=" << player1.GetCurrentHP()
            << ", ATK=" << player1.GetCurrentATK()
            << ", MP=" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << ": HP=" << player2.GetCurrentHP()
            << ", ATK=" << player2.GetCurrentATK()
            << ", MP=" << player2.GetCurrentMP() << endl;

        game.StartTurn();
        cout << player1.GetName() << "�������ظ���" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << "�������ظ���" << player2.GetCurrentMP() << endl;

        Action *action1 = player1.GetActions()[GetRandom(actions.size() + 1)];
        Action* action2 = player2.GetActions()[GetRandom(actions.size() + 1)];
        game.ActionTurn(action1, action2);
        if (action1->GetType() == ACTION_SKIP) {
            cout << player1.GetName() << "�����غ�" << endl;
        }
        else {
            cout << player1.GetName() << "���У�" << ((MoveAction *)action1)->GetName() <<
                "������" << action1->GetPower() << "������������" << action1->GetPoint() << endl;
        }
        if (action2->GetType() == ACTION_SKIP) {
            cout << player2.GetName() << "�����غ�" << endl;
        }
        else {
            cout << player2.GetName() << "���У�" << ((MoveAction*)action2)->GetName() <<
                "������" << action2->GetPower() << "������������" << action2->GetPoint() << endl;
        }

        auto check = game.CheckTurn(action1, action2);
        if (check.first == 0) {
            cout << player1.GetName() << "δ���˺�" << endl;
        }
        else {
            cout << player1.GetName() << "�ܵ�" << check.first << "�˺�" << endl;
        }
        if (check.second == 0) {
            cout << player2.GetName() << "δ���˺�" << endl;
        }
        else {
            cout << player2.GetName() << "�ܵ�" << check.second << "�˺�" << endl;
        }

        game.EndTurn();
        cout << "�غϽ���" << endl;
    }

    if (!player1.IsAlive() && !player2.IsAlive()) {
        cout << "\nս��������ͬ���ھ�!" << endl;
    }
    else {
        cout << "\nս��������ʤ����: " << (player1.IsAlive() ? player1 : player2).GetName() << "!" << endl;
    }
}