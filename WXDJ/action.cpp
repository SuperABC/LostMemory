#include "action.h"


Effect::Effect(EFFECT_TYPE t) : type(t) {

}

EFFECT_TYPE Effect::GetType() {

}

PenetrateEffect::PenetrateEffect() : Effect(EFFECT_PENETRATE) {

}

DotEffect::DotEffect() : Effect(EFFECT_DOT) {

}

RecoverEffect::RecoverEffect() : Effect(EFFECT_RECOVER) {

}

LockEffect::LockEffect() : Effect(EFFECT_LOCK) {

}

ReduceEffect::ReduceEffect() : Effect(EFFECT_REDUCE) {

}

ReboundEffect::ReboundEffect() : Effect(EFFECT_REBOUND) {

}

AbsorbEffect::AbsorbEffect() : Effect(EFFECT_ABSORB) {

}

RebateEffect::RebateEffect() : Effect(EFFECT_REBATE) {

}

Action::Action(ACTION_TYPE type, ATTRIBUTE_TYPE attribute, int point, int power)
    : type(type), attribute(attribute), point(point), power(power) {
}

ACTION_TYPE Action::GetType() const {
    return type;
}
ATTRIBUTE_TYPE Action::GetAttribute() const {
    return attribute;
}
int Action::GetPoint() const {
    return point;
}
int Action::GetPower() const {
    return power;
}

bool Action::Validate(int power) const {
    return this->power >= power;
}

SkipAction::SkipAction() : Action(ACTION_SKIP, ATTRIBUTE_NONE, 0, 0) {

}

SingleAction::SingleAction(const std::string& name, ATTRIBUTE_TYPE attribute, int point, int power, Realm realm,
    std::vector<Effect*>effects)
    : name(name), realm(realm), effects(effects), Action(ACTION_SINGLE, attribute, point, power) {
}

std::string SingleAction::GetName() const {
    return name;
}
Realm SingleAction::GetRealm() const {
    return realm;
}
std::vector<Effect*>& SingleAction::GetEffects() {
    return effects;
}

DualAction::DualAction(SingleAction* action1, SingleAction* action2)
    : action1(action1), action2(action2),
    Action(ACTION_DUAL, DUAL_ATTRIBUTE_PRIMARY.at({ action1->GetAttribute(), action2->GetAttribute() }),
        static_cast<int>(0.75 * (action1->GetPoint() + action2->GetPoint())),
        static_cast<int>(1.2 * (action1->GetPower() + action2->GetPower()))
    ) {

}

SingleAction* DualAction::GetAction1() {
    return action1;
}
SingleAction* DualAction::GetAction2() {
    return action2;
}

