#pragma once

#include "def.h"


class Effect {
private:
    EFFECT_TYPE type;

public:
    Effect(EFFECT_TYPE t) : type(t) {}
};

class DotEffect : public Effect {
private:
    int instantDot;
    int beginDot;
    int endDot;
    int dotRounds;
    int dotInterval;

public:
    DotEffect() : Effect(EFFECT_DOT) {}
};

class RecoverEffect : public Effect {
private:
    int instantRecover;
    int beginRecover;
    int endRecover;
    int recoverRounds;
    int recoverInterval;

public:
    RecoverEffect() : Effect(EFFECT_RECOVER) {}
};

class LockEffect : public Effect {
private:
    bool lockBegin;
    bool lockMove;
    bool lockEnd;

public:
    LockEffect() : Effect(EFFECT_LOCK) {}
};

class ImmuneEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;

public:
    ImmuneEffect() : Effect(EFFECT_IMMUNE) {}
};

class ReboundEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;
    std::vector<std::pair<ATTRIBUTE_TYPE, int>> limit;

public:
    ReboundEffect() : Effect(EFFECT_REBOUND) {}
};

class AbsorbEffect : public Effect {
private:
    std::vector<std::pair<ATTRIBUTE_TYPE, float>> ratios;
    std::vector<std::pair<ATTRIBUTE_TYPE, int>> limit;

public:
    AbsorbEffect() : Effect(EFFECT_ABSORB) {}
};

class RebateEffect : public Effect {
private:
    int instantRebate;
    int beginRebate;
    int endRebate;
    int rebateRounds;
    int rebateInterval;

public:
    RebateEffect() : Effect(EFFECT_REBATE) {}
};

class Action {
protected:
    ACTION_TYPE type;

    ATTRIBUTE_TYPE attribute;
    int point;
    int power;

public:
    Action(ACTION_TYPE type, ATTRIBUTE_TYPE attribute, int point, int power) :
        type(type), attribute(attribute), point(point), power(power) {}

    ACTION_TYPE GetType() const { return type; }
    ATTRIBUTE_TYPE GetAttribute() const { return attribute; }
    int GetPoint() const { return point; }
    int GetPower() const { return power; }

    virtual bool Validate(int power) const {
        return this->power >= power;
    }
};

class SkipAction : public Action {
public:
    SkipAction() : Action(ACTION_SKIP, ATTRIBUTE_NONE, 0, 0) {}
};

class SingleAction : public Action {
private:
    std::string name;
    Realm realm;

    std::vector<Effect*> effects;

public:
    SingleAction(const std::string& name, ATTRIBUTE_TYPE attribute, int point, int power, Realm realm,
        std::vector<Effect*>effects = {})
        : name(name), realm(realm), effects(effects), Action(ACTION_SINGLE, attribute, point, power) {}

    std::string GetName() const { return name; }
    Realm GetRealm() const { return realm; }
};

class DualAction : public Action {
private:
    SingleAction *action1, *action2;

public:
    DualAction(SingleAction* action1, SingleAction* action2)
        : action1(action1), action2(action2),
        Action(ACTION_DUAL, DUAL_ATTRIBUTE_PRIMARY.at({ action1->GetAttribute(), action1->GetAttribute() }),
            0.75 * (action1->GetPoint() + action1->GetPoint()),
            1.2 * (action1->GetPower() + action1->GetPower())
        ) {}

    SingleAction* GetAction1() { return action1; }
    SingleAction* GetAction2() { return action2; }
};
