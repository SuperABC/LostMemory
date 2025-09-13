#pragma once

#include "def.h"


class Effect {
private:
    EFFECT_TYPE type;

public:
    Effect(EFFECT_TYPE t);

    EFFECT_TYPE GetType();
};

class PhysicalEffect : public Effect {
private:

public:
    PhysicalEffect();
};

class PenetrateEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    PenetrateEffect(float none, float metal, float wood, float water, float fire, float earth, float all);

    float GetRatio(ATTRIBUTE_TYPE attribute) {
        for (auto ratio : ratios) {
            if (ratio.first == attribute)return ratio.second;
        }

        return 0.0f;
    }
};

class ReboundEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    ReboundEffect(float none, float metal, float wood, float water, float fire, float earth, float all);

    float GetRatio(ATTRIBUTE_TYPE attribute) {
        for (auto ratio : ratios) {
            if (ratio.first == attribute)return ratio.second;
        }

        return 0.0f;
    }
};

class AbsorbEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    AbsorbEffect(float none, float metal, float wood, float water, float fire, float earth, float all);

    float GetRatio(ATTRIBUTE_TYPE attribute) {
        for (auto ratio : ratios) {
            if (ratio.first == attribute)return ratio.second;
        }

        return 0.0f;
    }
};

class LockEffect : public Effect {
private:
    bool lockBegin;
    bool lockMove;
    bool lockEnd;

public:
    LockEffect();
};

class RebateEffect : public Effect {
private:
    int instantRebate;
    int beginRebate;
    int endRebate;
    int rebateRounds;
    int rebateInterval;

public:
    RebateEffect();
};

class DotEffect : public Effect {
private:
    int instantDot;
    int beginDot;
    int endDot;
    int dotRounds;
    int dotInterval;

public:
    DotEffect();
};

class ReduceEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    ReduceEffect();
};

class RecoverEffect : public Effect {
private:
    int instantRecover;
    int beginRecover;
    int endRecover;
    int recoverRounds;
    int recoverInterval;

public:
    RecoverEffect();
};

class Action {
protected:
    ACTION_TYPE type;
    ATTRIBUTE_TYPE attribute;
    int point;
    int power;

    std::vector<Effect*> effects;

public:
    Action(ACTION_TYPE type, ATTRIBUTE_TYPE attribute, int point, int power, std::vector<Effect*> effects);
    ACTION_TYPE GetType() const;
    ATTRIBUTE_TYPE GetAttribute() const;
    int GetPoint() const;
    int GetPower() const;
    virtual bool Validate(int power) const;

    Effect* GetEffect(EFFECT_TYPE type);
    std::vector<Effect*> &GetEffects();

    virtual std::string GetText() = 0;
};

class SkipAction : public Action {
public:
    SkipAction();

    virtual std::string GetText() { return "��"; }
};

class SingleAction : public Action {
private:
    std::string name;
    Realm realm;

    friend class DualAction;

public:
    SingleAction(const std::string& name, ATTRIBUTE_TYPE attribute, int point, int power, Realm realm,
        std::vector<Effect*>effects = {});
    std::string GetName() const;
    Realm GetRealm() const;
    std::vector<Effect*>& GetEffects();

    virtual std::string GetText() { return name; }
};

class DualAction : public Action {
private:
    SingleAction* action1, * action2;

public:
    DualAction(SingleAction* action1, SingleAction* action2);
    SingleAction* GetAction1();
    SingleAction* GetAction2();

    virtual std::string GetText() { return std::string("(") + action1->GetName() + ", " + action2->GetName() + ")"; }
};

static std::vector<SingleAction*> actions = {
    new SingleAction("�����Ʒ�", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new SingleAction("����ȭ��", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new SingleAction("�����ȷ�", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),

    new SingleAction("�����Ʒ�", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new SingleAction("����ȭ��", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new SingleAction("�����ȷ�", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
    new SingleAction("ͻ���Ʒ�", ATTRIBUTE_NONE, 34, 22, Realm::MYSTIC_MID),
    new SingleAction("ͻ��ȭ��", ATTRIBUTE_NONE, 40, 26, Realm::MYSTIC_MID),
    new SingleAction("ͻ���ȷ�", ATTRIBUTE_NONE, 45, 30, Realm::MYSTIC_MID),
    new SingleAction("�����Ʒ�", ATTRIBUTE_NONE, 40, 25, Realm::MYSTIC_LATE),
    new SingleAction("����ȭ��", ATTRIBUTE_NONE, 48, 30, Realm::MYSTIC_LATE),
    new SingleAction("�����ȷ�", ATTRIBUTE_NONE, 55, 35, Realm::MYSTIC_LATE),

    new SingleAction("ǧ�ȵ�һʽ", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵڶ�ʽ", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ���ʽ", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵڰ�ʽ", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵھ�ʽ", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮʽ", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮһʽ", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵ�ʮ��ʽ", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("ǧ�ȵڶ�ʮʽ", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("����ٵ�צ��һʽ", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ�ڶ�ʽ", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ����ʽ", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ�ڰ�ʽ", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ�ھ�ʽ", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮʽ", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮһʽ", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ��ʮ��ʽ", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("����ٵ�צ�ڶ�ʮʽ", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),

    new SingleAction("���˾����һʽ", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new SingleAction("���˾���ڶ�ʽ", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("���˾������ʽ", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new SingleAction("���˾������ʽ", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("���˾������ʽ", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new SingleAction("���˾������ʽ", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("���˾������ʽ", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("���˾���ڰ�ʽ", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("���˾���ھ�ʽ", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���˾����ʮʽ", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���˾����ʮһʽ", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���˾����ʮ��ʽ", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���˾���ڶ�ʮʽ", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("ǧ��ն��һʽ", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new SingleAction("ǧ��ն�ڶ�ʽ", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new SingleAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new SingleAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("ǧ��ն����ʽ", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("ǧ��ն�ڰ�ʽ", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("ǧ��ն�ھ�ʽ", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("ǧ��ն��ʮʽ", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("ǧ��ն��ʮһʽ", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("ǧ��ն��ʮ��ʽ", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("ǧ��ն�ڶ�ʮʽ", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("���񹦵�һʽ", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new SingleAction("���񹦵ڶ�ʽ", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new SingleAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new SingleAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("���񹦵���ʽ", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("���񹦵ڰ�ʽ", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("���񹦵ھ�ʽ", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���񹦵�ʮʽ", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���񹦵�ʮһʽ", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���񹦵�ʮ��ʽ", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���񹦵ڶ�ʮʽ", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("ľɭ�ֱ任��һʽ", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new SingleAction("ľɭ�ֱ任�ڶ�ʽ", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new SingleAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new SingleAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("ľɭ�ֱ任����ʽ", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("ľɭ�ֱ任�ڰ�ʽ", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("ľɭ�ֱ任�ھ�ʽ", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("ľɭ�ֱ任��ʮʽ", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("ľɭ�ֱ任��ʮһʽ", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("ľɭ�ֱ任��ʮ��ʽ", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("ľɭ�ֱ任�ڶ�ʮʽ", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("���������һʽ", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new SingleAction("��������ڶ�ʽ", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("�����������ʽ", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new SingleAction("�����������ʽ", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("�����������ʽ", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new SingleAction("�����������ʽ", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("�����������ʽ", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("��������ڰ�ʽ", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("��������ھ�ʽ", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���������ʮʽ", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���������ʮһʽ", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���������ʮ��ʽ", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("��������ڶ�ʮʽ", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("�콵�����һʽ", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new SingleAction("�콵����ڶ�ʽ", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("�콵�������ʽ", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new SingleAction("�콵�������ʽ", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("�콵�������ʽ", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new SingleAction("�콵�������ʽ", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("�콵�������ʽ", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("�콵����ڰ�ʽ", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("�콵����ھ�ʽ", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("�콵�����ʮʽ", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("�콵�����ʮһʽ", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("�콵�����ʮ��ʽ", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("�콵����ڶ�ʮʽ", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("�����һʽ", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("����ڶ�ʽ", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�������ʽ", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�������ʽ", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�������ʽ", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�������ʽ", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�������ʽ", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("����ڰ�ʽ", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("����ھ�ʽ", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮʽ", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮһʽ", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("�����ʮ��ʽ", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("����ڶ�ʮʽ", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("���ȭ��һʽ", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new SingleAction("���ȭ�ڶ�ʽ", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new SingleAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new SingleAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("���ȭ����ʽ", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("���ȭ�ڰ�ʽ", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("���ȭ�ھ�ʽ", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���ȭ��ʮʽ", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���ȭ��ʮһʽ", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���ȭ��ʮ��ʽ", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���ȭ�ڶ�ʮʽ", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("���ǵ�һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new SingleAction("���ǵڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new SingleAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new SingleAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("���ǵ���ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("���ǵڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("���ǵھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���ǵ�ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���ǵ�ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���ǵ�ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���ǵڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("������ħȭ��һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ�ڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ����ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ�ڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ�ھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ��ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("������ħȭ�ڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("���а����Ƶ�һʽ", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new SingleAction("���а����Ƶڶ�ʽ", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new SingleAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new SingleAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("���а����Ƶ���ʽ", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("���а����Ƶڰ�ʽ", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("���а����Ƶھ�ʽ", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���а����Ƶ�ʮʽ", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("���а����Ƶ�ʮһʽ", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���а����Ƶ�ʮ��ʽ", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("���а����Ƶڶ�ʮʽ", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

};
