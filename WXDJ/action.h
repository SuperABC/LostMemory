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

    virtual std::string GetText() { return "无"; }
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
    new SingleAction("基础掌法", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new SingleAction("基础拳法", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new SingleAction("基础腿法", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),

    new SingleAction("进阶掌法", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new SingleAction("进阶拳法", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new SingleAction("进阶腿法", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
    new SingleAction("突破掌法", ATTRIBUTE_NONE, 34, 22, Realm::MYSTIC_MID),
    new SingleAction("突破拳法", ATTRIBUTE_NONE, 40, 26, Realm::MYSTIC_MID),
    new SingleAction("突破腿法", ATTRIBUTE_NONE, 45, 30, Realm::MYSTIC_MID),
    new SingleAction("自由掌法", ATTRIBUTE_NONE, 40, 25, Realm::MYSTIC_LATE),
    new SingleAction("自由拳法", ATTRIBUTE_NONE, 48, 30, Realm::MYSTIC_LATE),
    new SingleAction("自由腿法", ATTRIBUTE_NONE, 55, 35, Realm::MYSTIC_LATE),

    new SingleAction("千腿第一式", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第二式", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第三式", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第四式", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第五式", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第六式", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第七式", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第八式", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第九式", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十式", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十一式", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十二式", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十三式", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十四式", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十五式", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十六式", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十七式", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十八式", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第十九式", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("千腿第二十式", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new PenetrateEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("开天辟地爪第一式", ATTRIBUTE_NONE, 72, 40, Realm::EARTH_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第二式", ATTRIBUTE_NONE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第三式", ATTRIBUTE_NONE, 88, 47, Realm::EARTH_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第四式", ATTRIBUTE_NONE, 92, 50, Realm::EARTH_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第五式", ATTRIBUTE_NONE, 104, 55, Realm::EARTH_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第六式", ATTRIBUTE_NONE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第七式", ATTRIBUTE_NONE, 122, 64, Realm::HEAVEN_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第八式", ATTRIBUTE_NONE, 135, 70, Realm::HEAVEN_INIT, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第九式", ATTRIBUTE_NONE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十式", ATTRIBUTE_NONE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十一式", ATTRIBUTE_NONE, 192, 95, Realm::HEAVEN_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十二式", ATTRIBUTE_NONE, 216, 106, Realm::HEAVEN_MID, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十三式", ATTRIBUTE_NONE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十四式", ATTRIBUTE_NONE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十五式", ATTRIBUTE_NONE, 310, 145, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十六式", ATTRIBUTE_NONE, 346, 160, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十七式", ATTRIBUTE_NONE, 388, 176, Realm::HEAVEN_LATE, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十八式", ATTRIBUTE_NONE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第十九式", ATTRIBUTE_NONE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),
    new SingleAction("开天辟地爪第二十式", ATTRIBUTE_NONE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new PhysicalEffect()
        }),

    new SingleAction("伏羲九针第一式", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new SingleAction("伏羲九针第二式", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("伏羲九针第三式", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new SingleAction("伏羲九针第四式", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("伏羲九针第五式", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new SingleAction("伏羲九针第六式", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("伏羲九针第七式", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("伏羲九针第八式", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("伏羲九针第九式", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("伏羲九针第十式", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("伏羲九针第十一式", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("伏羲九针第十二式", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("伏羲九针第十三式", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("伏羲九针第十四式", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("伏羲九针第十五式", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("伏羲九针第十六式", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("伏羲九针第十七式", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("伏羲九针第十八式", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("伏羲九针第十九式", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("伏羲九针第二十式", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("千刃斩第一式", ATTRIBUTE_METAL, 72, 40, Realm::EARTH_INIT),
    new SingleAction("千刃斩第二式", ATTRIBUTE_METAL, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("千刃斩第三式", ATTRIBUTE_METAL, 88, 47, Realm::EARTH_MID),
    new SingleAction("千刃斩第四式", ATTRIBUTE_METAL, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("千刃斩第五式", ATTRIBUTE_METAL, 104, 55, Realm::EARTH_LATE),
    new SingleAction("千刃斩第六式", ATTRIBUTE_METAL, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("千刃斩第七式", ATTRIBUTE_METAL, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("千刃斩第八式", ATTRIBUTE_METAL, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("千刃斩第九式", ATTRIBUTE_METAL, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("千刃斩第十式", ATTRIBUTE_METAL, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("千刃斩第十一式", ATTRIBUTE_METAL, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("千刃斩第十二式", ATTRIBUTE_METAL, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("千刃斩第十三式", ATTRIBUTE_METAL, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("千刃斩第十四式", ATTRIBUTE_METAL, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("千刃斩第十五式", ATTRIBUTE_METAL, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("千刃斩第十六式", ATTRIBUTE_METAL, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("千刃斩第十七式", ATTRIBUTE_METAL, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("千刃斩第十八式", ATTRIBUTE_METAL, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("千刃斩第十九式", ATTRIBUTE_METAL, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("千刃斩第二十式", ATTRIBUTE_METAL, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("砍柴功第一式", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new SingleAction("砍柴功第二式", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("砍柴功第三式", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new SingleAction("砍柴功第四式", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("砍柴功第五式", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new SingleAction("砍柴功第六式", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("砍柴功第七式", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("砍柴功第八式", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("砍柴功第九式", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("砍柴功第十式", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("砍柴功第十一式", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("砍柴功第十二式", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("砍柴功第十三式", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("砍柴功第十四式", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("砍柴功第十五式", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("砍柴功第十六式", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("砍柴功第十七式", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("砍柴功第十八式", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("砍柴功第十九式", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("砍柴功第二十式", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("木森林变换第一式", ATTRIBUTE_WOOD, 72, 40, Realm::EARTH_INIT),
    new SingleAction("木森林变换第二式", ATTRIBUTE_WOOD, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("木森林变换第三式", ATTRIBUTE_WOOD, 88, 47, Realm::EARTH_MID),
    new SingleAction("木森林变换第四式", ATTRIBUTE_WOOD, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("木森林变换第五式", ATTRIBUTE_WOOD, 104, 55, Realm::EARTH_LATE),
    new SingleAction("木森林变换第六式", ATTRIBUTE_WOOD, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("木森林变换第七式", ATTRIBUTE_WOOD, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("木森林变换第八式", ATTRIBUTE_WOOD, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("木森林变换第九式", ATTRIBUTE_WOOD, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("木森林变换第十式", ATTRIBUTE_WOOD, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("木森林变换第十一式", ATTRIBUTE_WOOD, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("木森林变换第十二式", ATTRIBUTE_WOOD, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("木森林变换第十三式", ATTRIBUTE_WOOD, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("木森林变换第十四式", ATTRIBUTE_WOOD, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("木森林变换第十五式", ATTRIBUTE_WOOD, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("木森林变换第十六式", ATTRIBUTE_WOOD, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("木森林变换第十七式", ATTRIBUTE_WOOD, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("木森林变换第十八式", ATTRIBUTE_WOOD, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("木森林变换第十九式", ATTRIBUTE_WOOD, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("木森林变换第二十式", ATTRIBUTE_WOOD, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("海龙金身第一式", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new SingleAction("海龙金身第二式", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("海龙金身第三式", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new SingleAction("海龙金身第四式", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("海龙金身第五式", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new SingleAction("海龙金身第六式", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("海龙金身第七式", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("海龙金身第八式", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("海龙金身第九式", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("海龙金身第十式", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("海龙金身第十一式", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("海龙金身第十二式", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("海龙金身第十三式", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("海龙金身第十四式", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("海龙金身第十五式", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("海龙金身第十六式", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("海龙金身第十七式", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("海龙金身第十八式", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("海龙金身第十九式", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("海龙金身第二十式", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("天降春雨第一式", ATTRIBUTE_WATER, 72, 40, Realm::EARTH_INIT),
    new SingleAction("天降春雨第二式", ATTRIBUTE_WATER, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("天降春雨第三式", ATTRIBUTE_WATER, 88, 47, Realm::EARTH_MID),
    new SingleAction("天降春雨第四式", ATTRIBUTE_WATER, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("天降春雨第五式", ATTRIBUTE_WATER, 104, 55, Realm::EARTH_LATE),
    new SingleAction("天降春雨第六式", ATTRIBUTE_WATER, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("天降春雨第七式", ATTRIBUTE_WATER, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("天降春雨第八式", ATTRIBUTE_WATER, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("天降春雨第九式", ATTRIBUTE_WATER, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("天降春雨第十式", ATTRIBUTE_WATER, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("天降春雨第十一式", ATTRIBUTE_WATER, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("天降春雨第十二式", ATTRIBUTE_WATER, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("天降春雨第十三式", ATTRIBUTE_WATER, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("天降春雨第十四式", ATTRIBUTE_WATER, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("天降春雨第十五式", ATTRIBUTE_WATER, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("天降春雨第十六式", ATTRIBUTE_WATER, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("天降春雨第十七式", ATTRIBUTE_WATER, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("天降春雨第十八式", ATTRIBUTE_WATER, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("天降春雨第十九式", ATTRIBUTE_WATER, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("天降春雨第二十式", ATTRIBUTE_WATER, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("焚天第一式", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第二式", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第三式", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第四式", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第五式", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第六式", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第七式", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第八式", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第九式", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十式", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十一式", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十二式", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十三式", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十四式", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十五式", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十六式", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十七式", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十八式", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第十九式", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("焚天第二十式", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new ReboundEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("狂火拳第一式", ATTRIBUTE_FIRE, 72, 40, Realm::EARTH_INIT),
    new SingleAction("狂火拳第二式", ATTRIBUTE_FIRE, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("狂火拳第三式", ATTRIBUTE_FIRE, 88, 47, Realm::EARTH_MID),
    new SingleAction("狂火拳第四式", ATTRIBUTE_FIRE, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("狂火拳第五式", ATTRIBUTE_FIRE, 104, 55, Realm::EARTH_LATE),
    new SingleAction("狂火拳第六式", ATTRIBUTE_FIRE, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("狂火拳第七式", ATTRIBUTE_FIRE, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("狂火拳第八式", ATTRIBUTE_FIRE, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("狂火拳第九式", ATTRIBUTE_FIRE, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("狂火拳第十式", ATTRIBUTE_FIRE, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("狂火拳第十一式", ATTRIBUTE_FIRE, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("狂火拳第十二式", ATTRIBUTE_FIRE, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("狂火拳第十三式", ATTRIBUTE_FIRE, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("狂火拳第十四式", ATTRIBUTE_FIRE, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("狂火拳第十五式", ATTRIBUTE_FIRE, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("狂火拳第十六式", ATTRIBUTE_FIRE, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("狂火拳第十七式", ATTRIBUTE_FIRE, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("狂火拳第十八式", ATTRIBUTE_FIRE, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("狂火拳第十九式", ATTRIBUTE_FIRE, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("狂火拳第二十式", ATTRIBUTE_FIRE, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("荒星第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new SingleAction("荒星第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("荒星第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new SingleAction("荒星第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("荒星第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new SingleAction("荒星第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("荒星第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("荒星第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("荒星第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("荒星第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("荒星第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("荒星第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("荒星第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("荒星第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("荒星第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("荒星第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("荒星第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("荒星第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("荒星第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("荒星第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

    new SingleAction("地狱阴魔拳第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),
    new SingleAction("地狱阴魔拳第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK, {
            new AbsorbEffect(0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f)
        }),

    new SingleAction("五行八卦掌第一式", ATTRIBUTE_EARTH, 72, 40, Realm::EARTH_INIT),
    new SingleAction("五行八卦掌第二式", ATTRIBUTE_EARTH, 80, 43, Realm::EARTH_INIT_PEAK),
    new SingleAction("五行八卦掌第三式", ATTRIBUTE_EARTH, 88, 47, Realm::EARTH_MID),
    new SingleAction("五行八卦掌第四式", ATTRIBUTE_EARTH, 92, 50, Realm::EARTH_MID_PEAK),
    new SingleAction("五行八卦掌第五式", ATTRIBUTE_EARTH, 104, 55, Realm::EARTH_LATE),
    new SingleAction("五行八卦掌第六式", ATTRIBUTE_EARTH, 112, 59, Realm::EARTH_LATE_PEAK),
    new SingleAction("五行八卦掌第七式", ATTRIBUTE_EARTH, 122, 64, Realm::HEAVEN_INIT),
    new SingleAction("五行八卦掌第八式", ATTRIBUTE_EARTH, 135, 70, Realm::HEAVEN_INIT),
    new SingleAction("五行八卦掌第九式", ATTRIBUTE_EARTH, 150, 77, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("五行八卦掌第十式", ATTRIBUTE_EARTH, 168, 85, Realm::HEAVEN_INIT_PEAK),
    new SingleAction("五行八卦掌第十一式", ATTRIBUTE_EARTH, 192, 95, Realm::HEAVEN_MID),
    new SingleAction("五行八卦掌第十二式", ATTRIBUTE_EARTH, 216, 106, Realm::HEAVEN_MID),
    new SingleAction("五行八卦掌第十三式", ATTRIBUTE_EARTH, 244, 118, Realm::HEAVEN_MID_PEAK),
    new SingleAction("五行八卦掌第十四式", ATTRIBUTE_EARTH, 280, 132, Realm::HEAVEN_MID_PEAK),
    new SingleAction("五行八卦掌第十五式", ATTRIBUTE_EARTH, 310, 145, Realm::HEAVEN_LATE),
    new SingleAction("五行八卦掌第十六式", ATTRIBUTE_EARTH, 346, 160, Realm::HEAVEN_LATE),
    new SingleAction("五行八卦掌第十七式", ATTRIBUTE_EARTH, 388, 176, Realm::HEAVEN_LATE),
    new SingleAction("五行八卦掌第十八式", ATTRIBUTE_EARTH, 436, 194, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("五行八卦掌第十九式", ATTRIBUTE_EARTH, 488, 214, Realm::HEAVEN_LATE_PEAK),
    new SingleAction("五行八卦掌第二十式", ATTRIBUTE_EARTH, 560, 240, Realm::HEAVEN_LATE_PEAK),

};
