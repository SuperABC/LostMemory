#pragma once

#include "def.h"


enum ACTION_TYPE {
    ACTION_SKIP,
    ACTION_MOVE,
    ACTION_DUAL
};

class Action {
protected:
    ACTION_TYPE type;

    Attribute attribute;
    int point;
    int power;

public:
    Action(ACTION_TYPE type, Attribute attribute, int point, int power) :
        type(type), attribute(attribute), point(point), power(power) {}

    ACTION_TYPE GetType() const { return type; }
    Attribute GetAttribute() const { return attribute; }
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

class MoveAction : public Action {
private:
    std::string name;
    Realm realm;

public:
    MoveAction(const std::string& name, Attribute element, int point, int power, Realm realm)
        : name(name), realm(realm), Action(ACTION_MOVE, attribute, point, power) {}

    std::string GetName() const { return name; }
    Realm GetRealm() const { return realm; }
};

class DualAction : public Action {
private:
    MoveAction action1, action2;

public:
    DualAction(MoveAction& action1, MoveAction& action2)
        : action1(action1), action2(action2),
        Action(ACTION_DUAL, DUAL_ATTRIBUTE_PRIMARY.at({ action1.GetAttribute(), action1.GetAttribute() }),
            0.75 * (action1.GetPoint() + action1.GetPoint()),
            1.2 * (action1.GetPower() + action1.GetPower())
        ) {}
};
