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

    std::vector<Action *> actions;
    std::vector<std::string> skills;

    int recover;

public:
    Player(const std::string& name, int hp, int atk, int mp, int agi)
        : name(name), maxHP(hp), currentHP(hp), maxATK(atk), currentATK(atk),
        maxMP(mp), currentMP(mp), AGI(agi), currentRealm(YELLOW_INIT), recover(10) {}

    std::string GetName() const { return name; }
    int GetCurrentHP() const { return currentHP; }
    int GetCurrentATK() const { return currentATK; }
    int GetCurrentMP() const { return currentMP; }
    int GetAGI() const { return AGI; }
    int GetCurrentRealm() const { return currentRealm; }
    const std::vector<Action *>& GetActions() const { return actions; }

    void AddAction(Action* action) {
        actions.push_back(action);
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
            if (damage >= currentATK * 0.3) {
                currentHP = std::max(0, currentHP - damage);
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