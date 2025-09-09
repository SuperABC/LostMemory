#include "player.h"


Player::Player(const std::string& name, int hp, int atk, int mp, int agi, int recover)
    : name(name), maxHP(hp), currentHP(hp), maxATK(atk), currentATK(atk),
    maxMP(mp), currentMP(mp), AGI(agi), currentRealm(YELLOW_INIT), recover(recover) {

}

std::string Player::GetName() const {
    return name;
}
int Player::GetCurrentHP() const {
    return currentHP;
}
int Player::GetCurrentATK() const {
    return currentATK;
}
int Player::GetCurrentMP() const {
    return currentMP;
}
int Player::GetAGI() const {
    return AGI;
}
int Player::GetCurrentRealm() const {
    return currentRealm;
}

void Player::AddAction(SingleAction* action) {
    actions.push_back(action);
}

const std::vector<SingleAction*>& Player::GetActions() const {
    return actions;
}

Action* Player::GetAction(int idx) {
    if (idx < 0 || idx >= actions.size()) return new SkipAction();
    return actions[idx];
}

Action* Player::GetAction(std::string name) {
    for (auto action : actions) {
        if (action->GetName() == name) {
            return action;
        }
    }
    return new SkipAction();
}

Action* Player::GetAction(int idx1, int idx2) {
    if (idx1 < 0 || idx1 >= actions.size()) return new SkipAction();
    if (idx2 < 0 || idx2 >= actions.size()) return new SkipAction();
    return new DualAction(actions[idx1], actions[idx2]);
}

Action* Player::GetAction(std::string name1, std::string name2) {
    SingleAction* action1 = nullptr, * action2 = nullptr;
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

void Player::AddSkill(const std::string& skill) {
    skills.push_back(skill);
}

bool Player::IsAlive() const {
    return currentHP > 0 && currentATK > 0;
}

bool Player::ValidateAction(const Action* action) const {
    return action->Validate(currentMP);
}

void Player::ConsumePower(int power) {
    if (currentMP >= power) {
        currentMP -= power;
    }
    else {
        int deficit = power - currentMP;
        currentMP = 0;
        currentATK = std::max(0, currentATK - deficit * 2);
    }
}

void Player::TakeDamage(int damage, bool physical) {
    if (physical) {
        currentHP = std::max(0, currentHP - damage);
    }
    else {
        if (damage >= currentATK * 0.6) {
            currentHP = std::max(0, currentHP - damage);
        }
        else if (damage >= currentATK * 0.3) {
            currentHP = std::max(0, static_cast<int>(currentHP - damage * 0.5f));
        }
        currentATK -= damage;
    }
}

void Player::UpdateRealm() {
    for (const auto& requirement : REALM_ATK_REQUIREMENTS) {
        if (currentATK >= requirement.second) {
            currentRealm = requirement.first;
        }
        else {
            break;
        }
    }
}

void Player::RecoverHP(int treat) {
    currentHP = std::min(maxHP, currentHP + treat);
}

void Player::RecoverMP() {
    currentMP += recover;
    if (currentMP > maxMP * 2) {
        currentHP = 0;
    }
    else if (currentMP > maxMP) {
        currentMP = maxMP;
    }
}