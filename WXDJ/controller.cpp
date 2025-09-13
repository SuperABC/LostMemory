#include "controller.h"

#include <stdexcept>


using namespace std;

bool Controller::CheckCounter(ATTRIBUTE_TYPE a1, ATTRIBUTE_TYPE a2) {
    return ATTRIBUTE_COUNTERS.find({ a1, a2 }) != ATTRIBUTE_COUNTERS.end();
}

double Controller::DodgeChance(int attackerAGI, int defenderAGI) {
    return static_cast<double>(
        defenderAGI * defenderAGI) / (attackerAGI * attackerAGI + defenderAGI * defenderAGI);
}

Controller::Controller(vector<Player*> players) : players(players) {
    effects.resize(players.size());
    status.resize(players.size());

    rng.seed(random_device()());
}

void Controller::ResetRound() {
    for (auto& s : status) {
        s = 0;
    }
}

void Controller::StartTurn() {
    ResetRound();

    ExecEffect(STAGE_START);

    for (int i = 0; i < players.size(); i++) {
        RecoverMP(i, -1);
    }
}

void Controller::ActionTurn(vector<pair<Action*, int>> actions) {
    if (actions.size() != players.size())
        throw runtime_error("Players and actions mismatch.");

    ExecEffect(STAGE_ACTION);

    for (int i = 0; i < players.size(); i++) {
        if (actions[i].first->GetType() != ACTION_SKIP && !(status[i] & 0x01)) {
            MakeMove(i, actions[i].second, actions[i].first->GetPower(), actions[i].first->GetText(), actions[i].first->GetPoint());

            auto rebate = actions[i].first->GetEffect(EFFECT_REBATE);
            if (rebate && !((RebateEffect*)rebate)->NeedHit()) {
                int amount = ((RebateEffect*)rebate)->RebateInstant();
                logs.push_back(Log(i, -1, amount, EFFECT_REBATE));
                RecoverMP(i, amount);
                AddEffect(i, new RebateEffect(*(RebateEffect*)rebate));
            }

            auto dot = actions[i].first->GetEffect(EFFECT_DOT);
            if (dot && !((DotEffect*)dot)->NeedHit()) {
                int amount = ((DotEffect*)dot)->DotInstant();
                int object = actions[i].second;
                logs.push_back(Log(i, object, amount, EFFECT_DOT));
                TakeDamage(i, object, actions[i].first->GetEffects(), actions[object].first->GetEffects(),
                    actions[i].first->GetAttribute(), amount);
                AddEffect(object, new DotEffect(*(DotEffect*)dot));
            }
        }
        else {
            SkipMove(i);
        }
    }
}

void Controller::CheckTurn(vector<pair<Action*, int>> actions) {
    if (actions.size() != players.size())
        throw runtime_error("Players and actions mismatch.");

    ExecEffect(STAGE_CHECK);

    for (int i = 0; i < players.size(); i++) {
        if (actions[i].first->GetType() == ACTION_SKIP || (status[i] & 0x01))continue;

        int j = actions[i].second;

        if (actions[j].first->GetType() == ACTION_SKIP || (status[j] & 0x01)) {
            uniform_real_distribution<double> dist(0.0, 1.0);
            double dodgeChance = DodgeChance(players[i]->GetAGI(), players[j]->GetAGI());
            if (!(status[j] & 0x01) && dist(rng) < dodgeChance) {
                DodgeSuccess(i, j);
                continue;
            }
            else {
                HitSuccess(i, j, actions[i].first, actions[j].first);
                TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                    actions[i].first->GetAttribute(), actions[i].first->GetPoint());
            }
        }
        else {
            if (actions[j].second == i) {
                if (j < i)continue;

                int point1 = actions[i].first->GetPoint();
                int point2 = actions[j].first->GetPoint();
                ATTRIBUTE_TYPE attribute1 = actions[i].first->GetAttribute();
                ATTRIBUTE_TYPE attribute2 = actions[j].first->GetAttribute();

                if (CheckCounter(attribute1, attribute2)) {
                    point2 /= 2;
                }
                if (CheckCounter(attribute2, attribute1)) {
                    point1 /= 2;
                }

                if (point1 > point2) {
                    HitSuccess(i, j, actions[i].first, actions[j].first);
                    HitSuccess(j, i, actions[j].first, actions[i].first);
                    TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                        actions[i].first->GetAttribute(), point1 - point2);
                    if (auto effect = actions[i].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point2 * ((PenetrateEffect*)effect)->GetRatio(actions[j].first->GetAttribute());
                        logs.push_back(Log(i, j, actions[i].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                            actions[i].first->GetAttribute(), penerate, false);
                    }
                    if (auto effect = actions[j].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point2 * ((PenetrateEffect*)effect)->GetRatio(actions[i].first->GetAttribute());
                        logs.push_back(Log(j, i, actions[j].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(j, i, actions[j].first->GetEffects(), actions[i].first->GetEffects(),
                            actions[j].first->GetAttribute(), penerate, false);
                    }
                }
                else if (point2 > point1) {
                    HitSuccess(i, j, actions[i].first, actions[j].first);
                    HitSuccess(j, i, actions[j].first, actions[i].first);
                    TakeDamage(j, i, actions[j].first->GetEffects(), actions[i].first->GetEffects(),
                        actions[j].first->GetAttribute(), point2 - point1);
                    if (auto effect = actions[i].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point1 * ((PenetrateEffect*)effect)->GetRatio(actions[j].first->GetAttribute());
                        logs.push_back(Log(i, j, actions[i].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                            actions[i].first->GetAttribute(), penerate, false);
                    }
                    if (auto effect = actions[j].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point1 * ((PenetrateEffect*)effect)->GetRatio(actions[i].first->GetAttribute());
                        logs.push_back(Log(j, i, actions[j].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(j, i, actions[j].first->GetEffects(), actions[i].first->GetEffects(),
                            actions[j].first->GetAttribute(), penerate, false);
                    }
                }
                else {
                    HitSuccess(i, j, actions[i].first, actions[j].first);
                    HitSuccess(j, i, actions[j].first, actions[i].first);
                    if (auto effect = actions[i].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point2 * ((PenetrateEffect*)effect)->GetRatio(actions[j].first->GetAttribute());
                        logs.push_back(Log(i, j, actions[i].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                            actions[i].first->GetAttribute(), penerate, false);
                    }
                    if (auto effect = actions[j].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point1 * ((PenetrateEffect*)effect)->GetRatio(actions[i].first->GetAttribute());
                        logs.push_back(Log(j, i, actions[j].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                        TakeDamage(j, i, actions[j].first->GetEffects(), actions[i].first->GetEffects(),
                            actions[j].first->GetAttribute(), penerate, false);
                    }
                }
            }
            else {
                HitSuccess(i, j, actions[i].first, actions[j].first);
                TakeDamage(i, j, actions[i].first->GetEffects(), actions[j].first->GetEffects(),
                    actions[i].first->GetAttribute(), actions[i].first->GetPoint());
            }
        }
    }
}

void Controller::EndTurn() {
    ExecEffect(STAGE_END);

    for (auto player : players) {
        player->UpdateRealm();
    }
}

void Controller::AddEffect(int player, Effect* effect) {
    effects[player].push_back(effect);
}

void Controller::ExecEffect(STAGE_TYPE stage) {
    for (int i = 0; i < effects.size(); i++) {
        for (int j = 0; j < effects[i].size(); j++) {
            switch (effects[i][j]->GetType()) {
            case EFFECT_LOCK:
                if (stage == STAGE_START) {
                    status[i] |= 0x01;
                    for (int k = j + 1; k < effects[i].size(); k++) {
                        effects[i][k - 1] = effects[i][k];
                    }
                    effects[i].pop_back();
                    j--;
                }
                break;
            case EFFECT_REBATE:
                if (stage == STAGE_START) {
                    int amount = ((RebateEffect*)effects[i][j])->RebateOnce();
                    if (amount == 0)break;
                    logs.push_back(Log(i, -1, amount, EFFECT_REBATE));
                    RecoverMP(i, amount, false);
                    if (((RebateEffect*)effects[i][j])->UseUp()) {
                        for (int k = j + 1; k < effects[i].size(); k++) {
                            effects[i][k - 1] = effects[i][k];
                        }
                        effects[i].pop_back();
                        j--;
                    }
                }
                break;
            case EFFECT_DOT:
                if (stage == STAGE_START) {
                    int amount = ((DotEffect*)effects[i][j])->DotOnce();
                    if (amount == 0)break;
                    logs.push_back(Log(-1, i, amount, EFFECT_DOT));
                    TakeDamage(-1, i, {}, {}, ATTRIBUTE_NONE, amount, false);
                    if (((DotEffect*)effects[i][j])->UseUp()) {
                        for (int k = j + 1; k < effects[i].size(); k++) {
                            effects[i][k - 1] = effects[i][k];
                        }
                        effects[i].pop_back();
                        j--;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}

vector<Log> Controller::GetNews() {
    vector<Log> news;
    for (int i = mark; i < logs.size(); i++) {
        news.push_back(logs[i]);
    }
    mark = logs.size();

    return news;
}

void Controller::RecoverMP(int player, int amount, bool log) {
    if (log)
        logs.push_back(Log(LOG_MP, player, amount));
    players[player]->RecoverMP(amount);
}

void Controller::ConsumeMP(int player, int amount, bool log) {
    if (log)
        logs.push_back(Log(LOG_CONSUME, player, amount));
    players[player]->ConsumeMP(amount);
}

void Controller::MakeMove(int subject, int object, int amount, std::string name, int point, bool log) {
    if (log)
        logs.push_back(Log(subject, object, amount, name, point));
    players[subject]->ConsumeMP(amount);
}

void Controller::SkipMove(int player, bool log) {
    if (log)
        logs.push_back(Log(player));
}

void Controller::RecoverATK(int player, int amount, bool log) {
    if (log)
        logs.push_back(Log(LOG_ATK, player, amount));
    players[player]->RecoverATK(amount);
}

void Controller::RecoverHP(int player, int amount, bool log) {
    if (log)
        logs.push_back(Log(LOG_HP, player, amount));
    players[player]->RecoverHP(amount);
}

void Controller::HitSuccess(int subject, int object, Action* offend, Action* defend, bool log) {
    auto lock = offend->GetEffect(EFFECT_LOCK);
    if (lock) {
        float prob = ((LockEffect*)lock)->GetProb();
        uniform_real_distribution<double> dist(0.0, 1.0);
        if (dist(rng) < prob) {
            if (log)
                logs.push_back(Log(subject, object, 0, EFFECT_LOCK));
            AddEffect(object, lock);
        }
    }

    auto rebate = offend->GetEffect(EFFECT_REBATE);
    if (rebate && ((RebateEffect*)rebate)->NeedHit()) {
        int amount = ((RebateEffect*)rebate)->RebateInstant();
        if (log)
            logs.push_back(Log(subject, -1, amount, EFFECT_REBATE));
        RecoverMP(subject, amount);
        AddEffect(subject, new RebateEffect(*(RebateEffect*)rebate));
    }

    auto dot = offend->GetEffect(EFFECT_DOT);
    if (dot && ((DotEffect*)dot)->NeedHit()) {
        int amount = ((DotEffect*)dot)->DotInstant();
        if (log)
            logs.push_back(Log(subject, object, amount, EFFECT_DOT));
        TakeDamage(subject, object, offend->GetEffects(), defend->GetEffects(), offend->GetAttribute(), amount);
        AddEffect(object, new DotEffect(*(DotEffect*)dot));
    }
}

void Controller::TakeDamage(int subject, int object, std::vector<Effect*> offend, std::vector<Effect*> defend,
    ATTRIBUTE_TYPE attribute, int amount, bool log) {
    auto physical = std::find_if(offend.begin(), offend.end(), [](Effect* effect) {return effect->GetType() == EFFECT_PHYSICAL; });
    if (log)
        logs.push_back(Log(subject, object, attribute, physical != offend.end() ? 0 : amount, physical != offend.end() ? amount : 0));
    players[object]->TakeDamage(amount, physical != offend.end());

    auto rebound = std::find_if(defend.begin(), defend.end(), [](Effect* effect) {return effect->GetType() == EFFECT_REBOUND; });
    if (rebound != defend.end()) {
        int damage = amount * ((ReboundEffect*)*rebound)->GetRatio(attribute);
        if (damage > 0) {
            logs.push_back(Log(object, subject, attribute, physical != offend.end() ? 0 : damage, physical != offend.end() ? damage : 0, EFFECT_REBOUND));
            TakeDamage(object, subject, defend, offend, attribute, physical != offend.end() ? 0 : damage, physical != offend.end() ? damage : 0, false);
        }
    }

    auto absorb = std::find_if(defend.begin(), defend.end(), [](Effect* effect) {return effect->GetType() == EFFECT_ABSORB; });
    if (absorb != defend.end()) {
        int mp = amount * ((AbsorbEffect*)*absorb)->GetRatio(attribute);
        logs.push_back(Log(object, subject, mp, EFFECT_ABSORB));
        RecoverMP(object, mp);
    }
}

void Controller::TakeDamage(int subject, int object, std::vector<Effect*> offend, std::vector<Effect*> defend,
    ATTRIBUTE_TYPE attribute, int atk, int hp, bool log) {
    int amount = atk > 0 ? atk : hp;
    bool physical = hp > 0;

    if (log)
        logs.push_back(Log(subject, object, attribute, atk, hp));
    players[object]->TakeDamage(amount, physical);

    auto rebound = std::find_if(defend.begin(), defend.end(), [](Effect* effect) {return effect->GetType() == EFFECT_REBOUND; });
    if (rebound != defend.end()) {
        int damage = amount * ((ReboundEffect*)*rebound)->GetRatio(attribute);
        if (damage > 0) {
            logs.push_back(Log(object, subject, attribute, physical ? 0 : damage, physical ? damage : 0, EFFECT_REBOUND));
            TakeDamage(object, subject, defend, offend, attribute, physical ? 0 : damage, physical ? damage : 0, false);
        }
    }

    auto absorb = std::find_if(defend.begin(), defend.end(), [](Effect* effect) {return effect->GetType() == EFFECT_ABSORB; });
    if (absorb != defend.end()) {
        int mp = amount * ((AbsorbEffect*)*absorb)->GetRatio(attribute);
        logs.push_back(Log(object, subject, mp, EFFECT_ABSORB));
        RecoverMP(object, mp);
    }
}

void Controller::DodgeSuccess(int subject, int object, bool log) {
    if(log)
        logs.push_back(Log(subject, object));
    players[object]->DodgeSuccess();
}
