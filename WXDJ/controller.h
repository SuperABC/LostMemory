#pragma once

#include "def.h"
#include "action.h"
#include "player.h"

enum LOG_TYPE {
    LOG_MOVE,
    LOG_DODGE,
    LOG_EFFECT
};

class Log {
public:
    Log(int subject, int object, ATTRIBUTE_TYPE attribute, int pointAtk, int pointHp) : type(LOG_MOVE), 
        subject(subject), object(object), attribute(attribute), pointAtk(pointAtk), pointHp(pointHp) {}
    Log(int subject, int object) : type(LOG_DODGE), subject(subject), object(object) {}
    Log(int subject, int object, ATTRIBUTE_TYPE attribute, int pointAtk, int pointHp, EFFECT_TYPE effect) : type(LOG_EFFECT),
        subject(subject), object(object), attribute(attribute), pointAtk(pointAtk), pointHp(pointHp), effect(effect) {}

    LOG_TYPE type;

    int subject, object;
    ATTRIBUTE_TYPE attribute;
    int pointAtk, pointHp;

    EFFECT_TYPE effect = EFFECT_NONE;
};

class Controller {
private:
    std::vector<Player *> players;
    std::vector<Effect * >effects;

    int mark = 0;
    std::vector<Log> logs;

    std::mt19937 rng;

    bool CheckCounter(ATTRIBUTE_TYPE a1, ATTRIBUTE_TYPE a2);
    double DodgeChance(int attackerAGI, int defenderAGI);

public:
    Controller(std::vector<Player*> players);

    void StartTurn();
    void ActionTurn(std::vector<std::pair<Action*, int>> actions);
    void CheckTurn(std::vector<std::pair<Action*, int>> actions);
    void EndTurn();

    std::vector<Log> GetNews();
};