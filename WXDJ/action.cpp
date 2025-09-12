#include "action.h"


using namespace std;

Effect::Effect(EFFECT_TYPE t) : type(t) {

}

EFFECT_TYPE Effect::GetType() {
    return type;
}

PhysicalEffect::PhysicalEffect() :
    Effect(EFFECT_PHYSICAL) {

}

PenetrateEffect::PenetrateEffect(float none, float metal, float wood, float water, float fire, float earth, float all) :
    Effect(EFFECT_PENETRATE) {
    if (none > 0)ratios.emplace_back(make_pair(ATTRIBUTE_NONE, none));
    if (metal > 0)ratios.emplace_back(make_pair(ATTRIBUTE_METAL, metal));
    if (wood > 0)ratios.emplace_back(make_pair(ATTRIBUTE_WOOD, wood));
    if (water > 0)ratios.emplace_back(make_pair(ATTRIBUTE_WATER, water));
    if (fire > 0)ratios.emplace_back(make_pair(ATTRIBUTE_FIRE, fire));
    if (earth > 0)ratios.emplace_back(make_pair(ATTRIBUTE_EARTH, earth));
    if (all > 0)ratios.emplace_back(make_pair(ATTRIBUTE_ALL, all));
}

ReboundEffect::ReboundEffect(float none, float metal, float wood, float water, float fire, float earth, float all) :
    Effect(EFFECT_REBOUND) {
    if (none > 0)ratios.emplace_back(make_pair(ATTRIBUTE_NONE, none));
    if (metal > 0)ratios.emplace_back(make_pair(ATTRIBUTE_METAL, metal));
    if (wood > 0)ratios.emplace_back(make_pair(ATTRIBUTE_WOOD, wood));
    if (water > 0)ratios.emplace_back(make_pair(ATTRIBUTE_WATER, water));
    if (fire > 0)ratios.emplace_back(make_pair(ATTRIBUTE_FIRE, fire));
    if (earth > 0)ratios.emplace_back(make_pair(ATTRIBUTE_EARTH, earth));
    if (all > 0)ratios.emplace_back(make_pair(ATTRIBUTE_ALL, all));
}

AbsorbEffect::AbsorbEffect() : Effect(EFFECT_ABSORB) {

}

RebateEffect::RebateEffect() : Effect(EFFECT_REBATE) {

}

LockEffect::LockEffect() : Effect(EFFECT_LOCK) {

}

DotEffect::DotEffect() : Effect(EFFECT_DOT) {

}

ReduceEffect::ReduceEffect() : Effect(EFFECT_REDUCE) {

}

RecoverEffect::RecoverEffect() : Effect(EFFECT_RECOVER) {

}

Action::Action(ACTION_TYPE type, ATTRIBUTE_TYPE attribute, int point, int power, std::vector<Effect*> effects = {})
    : type(type), attribute(attribute), point(point), power(power), effects(effects) {
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

Effect* Action::GetEffect(EFFECT_TYPE type) {
    for (auto effect : effects) {
        if (effect->GetType() == type)return effect;
    }

    return nullptr;
}

std::vector<Effect*>& Action::GetEffects() {
    return effects;
}

SkipAction::SkipAction() : Action(ACTION_SKIP, ATTRIBUTE_NONE, 0, 0) {

}

SingleAction::SingleAction(const string& name, ATTRIBUTE_TYPE attribute, int point, int power, Realm realm,
    vector<Effect*>effects)
    : name(name), realm(realm), Action(ACTION_SINGLE, attribute, point, power, effects) {
}

string SingleAction::GetName() const {
    return name;
}
Realm SingleAction::GetRealm() const {
    return realm;
}
vector<Effect*>& SingleAction::GetEffects() {
    return effects;
}

DualAction::DualAction(SingleAction* action1, SingleAction* action2)
    : action1(action1), action2(action2),
    Action(ACTION_DUAL, DUAL_ATTRIBUTE_PRIMARY.at({ action1->GetAttribute(), action2->GetAttribute() }),
        static_cast<int>(0.75 * (action1->GetPoint() + action2->GetPoint())),
        static_cast<int>(1.2 * (action1->GetPower() + action2->GetPower()))
    ) {
    effects = action1->effects;
    effects.insert(effects.end(), action2->effects.begin(), action2->effects.end());
}

SingleAction* DualAction::GetAction1() {
    return action1;
}
SingleAction* DualAction::GetAction2() {
    return action2;
}
