#pragma once

#include "def.h"


class Effect {
private:
    EFFECT_TYPE type;

public:
    Effect(EFFECT_TYPE t);

    EFFECT_TYPE GetType();
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

class ReduceEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    ReduceEffect();
};

class ReboundEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;
    std::vector<std::pair<ATTRIBUTE_TYPE, int>> limit;

public:
    ReboundEffect();
};

class AbsorbEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;
    std::vector<std::pair<ATTRIBUTE_TYPE, int>> limit;

public:
    AbsorbEffect();
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

class LockEffect : public Effect {
private:
    bool lockBegin;
    bool lockMove;
    bool lockEnd;

public:
    LockEffect();
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
};

class SkipAction : public Action {
public:
    SkipAction();
};

class SingleAction : public Action {
private:
    std::string name;
    Realm realm;
    std::vector<Effect*> effects;

    friend class DualAction;
public:
    SingleAction(const std::string& name, ATTRIBUTE_TYPE attribute, int point, int power, Realm realm,
        std::vector<Effect*>effects = {});
    std::string GetName() const;
    Realm GetRealm() const;
    std::vector<Effect*>& GetEffects();
};

class DualAction : public Action {
private:
    SingleAction* action1, * action2;

public:
    DualAction(SingleAction* action1, SingleAction* action2);
    SingleAction* GetAction1();
    SingleAction* GetAction2();
};