#pragma once

#include "def.h"
#include "action.h"


class Player {
private:
    std::string name;
    int maxHP;
    int currentHP;
    int maxATK;
    int currentATK;
    int maxMP;
    int currentMP;
    int AGI;
    Realm currentRealm;

    std::vector<SingleAction *> actions;
    std::vector<std::string> skills;

    int recover;

public:
    Player(const std::string& name, int hp, int atk, int mp, int agi, int recover = 10)
        : name(name), maxHP(hp), currentHP(hp), maxATK(atk), currentATK(atk),
        maxMP(mp), currentMP(mp), AGI(agi), currentRealm(YELLOW_INIT), recover(recover) {}

    std::string GetName() const { return name; }
    int GetCurrentHP() const { return currentHP; }
    int GetCurrentATK() const { return currentATK; }
    int GetCurrentMP() const { return currentMP; }
    int GetAGI() const { return AGI; }
    int GetCurrentRealm() const { return currentRealm; }

    void AddAction(SingleAction* action) {
        actions.push_back(action);
    }
    const std::vector<SingleAction*>& GetActions() const { return actions; }
    Action* GetAction(int idx) {
        if (idx < 0 || idx >= actions.size())return new SkipAction();

        return actions[idx];
    }
    Action* GetAction(std::string name) {
        for (auto action : actions) {
            if (action->GetName() == name) {
                return action;
            }
        }
        return new SkipAction();
    }
    Action* GetAction(int idx1, int idx2) {
        if (idx1 < 0 || idx1 >= actions.size())return new SkipAction();
        if (idx2 < 0 || idx2 >= actions.size())return new SkipAction();

        return new DualAction(actions[idx1], actions[idx2]);
    }
    Action* GetAction(std::string name1, std::string name2) {
        SingleAction *action1 = nullptr, *action2 = nullptr;
        for (auto action : actions) {
            if (action->GetName() == name1) {
                action1 = action;
                break;
            }
        }
        for (auto action : actions) {
            if (action->GetName() == name2) {
                action2 = action;
                break;
            }
        }
        if (action1 && action2) {
            return new DualAction(action1, action2);
        }

        return new SkipAction();
    }

    void AddSkill(const std::string& skill) {
        skills.push_back(skill);
    }

    bool IsAlive() const { return currentHP > 0 && currentATK > 0; }
    bool ValidateAction(const Action* action) const {
        return action->Validate(currentMP);
    }

    void ConsumePower(int power) {
        if (currentMP >= power) {
            currentMP -= power;
        }
        else {
            int deficit = power - currentMP;
            currentMP = 0;
            currentATK = std::max(0, currentATK - deficit * 2);
        }
    }

    void TakeDamage(int damage, bool physical = false) {
        if (physical) {
            currentHP = std::max(0, currentHP - damage);
        }
        else {
            if (damage >= currentATK * 0.6) {
                currentHP = std::max(0, currentHP - damage);
            }
            else if (damage >= currentATK * 0.3) {
                currentHP = std::max(0, (int)(currentHP - damage * 0.5f));
            }
            currentATK -= damage;
        }
    }

    void UpdateRealm() {
        for (const auto& requirement : REALM_ATK_REQUIREMENTS) {
            if (currentATK >= requirement.second) {
                currentRealm = requirement.first;
            }
            else {
                break;
            }
        }
    }

    void RecoverHP(int treat) {
        currentHP = std::min(maxHP, currentHP + treat);
    }

    void RecoverMP() {
        currentMP += recover;
        if (currentMP > maxMP * 2) {
            currentHP = 0;
        }
        else if (currentMP > maxMP) {
            currentMP = maxMP;
        }
    }
};