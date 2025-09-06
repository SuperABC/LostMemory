#pragma once

#include "def.h"
#include "action.h"
#include "player.h"

class Controller {
private:
    Player* player1;
    Player* player2;

    std::mt19937 rng;

    bool CheckCounter(Attribute a1, Attribute a2) {
        return ATTRIBUTE_COUNTERS.find({ a1, a2 }) != ATTRIBUTE_COUNTERS.end();
    }

    double DodgeChance(int attackerAGI, int defenderAGI) {
        return static_cast<double>(
            defenderAGI * defenderAGI) / (attackerAGI * attackerAGI + defenderAGI * defenderAGI);
    }

public:
    Controller(Player* p1, Player* p2)
        : player1(p1), player2(p2) {
        rng.seed(std::random_device()());
    }

    void StartTurn() {
        player1->RecoverMP();
        player2->RecoverMP();
    }

    void ActionTurn(Action* action1, Action* action2) {
        if (action1->GetType() == ACTION_SKIP && action2->GetType() == ACTION_SKIP)return;

        else if (action1->GetType() == ACTION_SKIP) {
            player2->ConsumePower(action2->GetPower());
        }

        else if (action2->GetType() == ACTION_SKIP) {
            player1->ConsumePower(action1->GetPower());
        }

        else {
            player1->ConsumePower(action1->GetPower());
            player2->ConsumePower(action2->GetPower());
        }
    }

    std::pair<int, int> CheckTurn(Action* action1, Action* action2) {
        if (action1->GetType() == ACTION_SKIP && action2->GetType() == ACTION_SKIP)return { 0, 0 };

        else if (action1->GetType() == ACTION_SKIP) {
            int point = action2->GetPoint();
            Attribute attribute = action2->GetAttribute();

            std::uniform_real_distribution<double> dist(0.0, 1.0);
            double dodgeChance = DodgeChance(player2->GetAGI(), player1->GetAGI());
            if (dist(rng) < dodgeChance)return { 0, 0 };

            player1->TakeDamage(point);
            return  { point, 0 };
        }

        else if (action2->GetType() == ACTION_SKIP) {
            int point = action1->GetPoint();
            Attribute attribute = action1->GetAttribute();

            std::uniform_real_distribution<double> dist(0.0, 1.0);
            double dodgeChance = DodgeChance(player1->GetAGI(), player2->GetAGI());
            if (dist(rng) < dodgeChance)return { 0, 0 };

            player2->TakeDamage(point);
            return  { 0, point };
        }

        else {
            int point1 = action1->GetPoint();
            int point2 = action2->GetPoint();
            Attribute attribute1 = action1->GetAttribute();
            Attribute attribute2 = action2->GetAttribute();

            if (CheckCounter(attribute1, attribute2)) {
                point2 /= 2;
            }
            if (CheckCounter(attribute2, attribute1)) {
                point1 /= 2;
            }

            if (point1 > point2) {
                player2->TakeDamage(point1 - point2);
                return  { 0, point1 - point2 };
            }
            else if (point2 > point1) {
                player1->TakeDamage(point2 - point1);
                return  { point2 - point1, 0 };
            }
        }

        return { 0, 0 };
    }

    void EndTurn() {

    }
};