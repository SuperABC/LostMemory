#pragma once

#include "def.h"
#include "action.h"
#include "player.h"


class Controller {
private:
    Player* player1;
    Player* player2;
    std::mt19937 rng;

    std::vector<Effect*>effects1;
    std::vector<Effect*>effects2;

    bool CheckCounter(ATTRIBUTE_TYPE a1, ATTRIBUTE_TYPE a2);
    double DodgeChance(int attackerAGI, int defenderAGI);

public:
    Controller(Player* p1, Player* p2);

    void StartTurn();
    void ActionTurn(Action* action1, Action* action2);
    std::pair<int, int> CheckTurn(Action* action1, Action* action2);
    void EndTurn();
};