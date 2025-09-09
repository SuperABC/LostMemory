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
    std::vector<SingleAction*> actions;
    std::vector<std::string> skills;
    int recover;

public:
    Player(const std::string& name, int hp, int atk, int mp, int agi, int recover = 10);

    std::string GetName() const;
    int GetCurrentHP() const;
    int GetCurrentATK() const;
    int GetCurrentMP() const;
    int GetAGI() const;
    int GetCurrentRealm() const;

    void AddAction(SingleAction* action);
    const std::vector<SingleAction*>& GetActions() const;
    Action* GetAction(int idx);
    Action* GetAction(std::string name);
    Action* GetAction(int idx1, int idx2);
    Action* GetAction(std::string name1, std::string name2);

    void AddSkill(const std::string& skill);

    bool IsAlive() const;
    bool ValidateAction(const Action* action) const;
    void ConsumePower(int power);
    void TakeDamage(int damage, bool physical = false);
    void UpdateRealm();
    void RecoverHP(int treat);
    void RecoverMP();
};