#pragma once

#include "def.h"
#include "action.h"
#include "player.h"

enum LOG_TYPE {
    LOG_MP, // 回复真气
    LOG_ATK, // 回复武力值
    LOG_HP, // 回复健康值
    LOG_CONSUME, // 消耗武力值
    LOG_SKIP, // 跳过回合
    LOG_MOVE, // 出招
    LOG_DAMAGE, // 招式命中
    LOG_DODGE, // 闪避成功
    LOG_EFFECT, // 特殊效果
};

class Log {
public:
    //状态变化
    Log(LOG_TYPE type, int player, int amount) : type(type), subject(player), amount(amount) {}
    //跳过回合
    Log(int player) : type(LOG_SKIP), subject(player) {}
    //出招
    Log(int subject, int object, int amount, std::string name, int point) : type(LOG_MOVE),
        subject(subject), object(object), amount(amount), name(name), pointAtk(point) {}
    //造成伤害
    Log(int subject, int object, ATTRIBUTE_TYPE attribute, int pointAtk, int pointHp) : type(LOG_DAMAGE),
        subject(subject), object(object), attribute(attribute), pointAtk(pointAtk), pointHp(pointHp) {
    }
    //闪避成功
    Log(int subject, int object) : type(LOG_DODGE), subject(subject), object(object) {}
    //即时伤害效果
    Log(int subject, int object, ATTRIBUTE_TYPE attribute, int pointAtk, int pointHp, EFFECT_TYPE effect) : type(LOG_EFFECT),
        subject(subject), object(object), attribute(attribute), pointAtk(pointAtk), pointHp(pointHp), effect(effect) {
    }
    //即时动作效果
    Log(int subject, int object, int amount, EFFECT_TYPE effect) : type(LOG_EFFECT),
        subject(subject), object(object), amount(amount), effect(effect) {
    }

    LOG_TYPE type;

    int subject, object;
    ATTRIBUTE_TYPE attribute;
    int pointAtk, pointHp;
    int amount;
    std::string name;

    EFFECT_TYPE effect = EFFECT_NONE;
};

class Controller {
private:
    std::vector<Player *> players;
    std::vector<std::vector<Effect *>>effects;
    std::vector<int> status;

    int mark = 0;
    std::vector<Log> logs;

    std::mt19937 rng;

    bool CheckCounter(ATTRIBUTE_TYPE a1, ATTRIBUTE_TYPE a2);
    double DodgeChance(int attackerAGI, int defenderAGI);

public:
    Controller(std::vector<Player*> players);

    void ResetRound();
    void StartTurn();
    void ActionTurn(std::vector<std::pair<Action*, int>> actions);
    void CheckTurn(std::vector<std::pair<Action*, int>> actions);
    void EndTurn();

    void AddEffect(int player, Effect* effect);
    void ExecEffect(STAGE_TYPE stage);

    std::vector<Log> GetNews();

    void RecoverMP(int player, int amount, bool log = true);
    void ConsumeMP(int player, int amount, bool log = true);
    void MakeMove(int subject, int object, int amount, std::string name, int point, bool log = true);
    void SkipMove(int player, bool log = true);
    void RecoverATK(int player, int amount, bool log = true);
    void RecoverHP(int player, int amount, bool log = true);
    void HitSuccess(int subject, int object, Action *action, bool log = true);
    void TakeDamage(int subject, int object, std::vector<Effect *> offend, std::vector<Effect*> defend,
        ATTRIBUTE_TYPE attribute, int amount, bool log = true);
    void TakeDamage(int subject, int object, std::vector<Effect*> offend, std::vector<Effect*> defend,
        ATTRIBUTE_TYPE attribute, int atk, int hp, bool log = true);
    void DodgeSuccess(int subject, int object, bool log = true);
};