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
    rng.seed(random_device()());
}

void Controller::StartTurn() {
    for (int i = 0; i < players.size(); i++) {
        RecoverMP(i, -1);
    }
}

void Controller::ActionTurn(vector<pair<Action*, int>> actions) {
    if (actions.size() != players.size())
        throw runtime_error("Players and actions mismatch.");

    for (int i = 0; i < players.size(); i++) {
        if (actions[i].first->GetType() != ACTION_SKIP) {
            MakeMove(i, actions[i].second, actions[i].first->GetPower(), actions[i].first->GetText(), actions[i].first->GetPoint());
        }
        else {
            SkipMove(i);
        }
    }
}

void Controller::CheckTurn(vector<pair<Action*, int>> actions) {
    if (actions.size() != players.size())
        throw runtime_error("Players and actions mismatch.");

    for (int i = 0; i < players.size(); i++) {
        if (actions[i].first->GetType() == ACTION_SKIP)continue;

        int j = actions[i].second;

        if (actions[j].first->GetType() == ACTION_SKIP) {
            uniform_real_distribution<double> dist(0.0, 1.0);
            double dodgeChance = DodgeChance(players[i]->GetAGI(), players[j]->GetAGI());
            if (dist(rng) < dodgeChance) {
                DodgeSuccess(i, j);
                continue;
            }
            else {
                TakeDamage(i, j, actions[i].first->GetAttribute(), actions[i].first->GetPoint(), false);
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
                    TakeDamage(i, j, actions[i].first->GetAttribute(), point1 - point2, false);
                    if (auto effect = actions[i].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point2 * ((PenetrateEffect*)effect)->GetRatio(actions[j].first->GetAttribute());
                        players[j]->TakeDamage(penerate);
                        logs.push_back(Log(i, j, actions[i].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                    }
                    if (auto effect = actions[j].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point2 * ((PenetrateEffect*)effect)->GetRatio(actions[i].first->GetAttribute());
                        players[i]->TakeDamage(penerate);
                        logs.push_back(Log(j, i, actions[j].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                    }
                }
                else if (point2 > point1) {
                    TakeDamage(j, i, actions[j].first->GetAttribute(), point2 - point1, false);
                    if (auto effect = actions[i].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point1 * ((PenetrateEffect*)effect)->GetRatio(actions[j].first->GetAttribute());
                        players[j]->TakeDamage(penerate);
                        logs.push_back(Log(i, j, actions[i].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                    }
                    if (auto effect = actions[j].first->GetEffect(EFFECT_PENETRATE)) {
                        int penerate = point1 * ((PenetrateEffect*)effect)->GetRatio(actions[i].first->GetAttribute());
                        players[i]->TakeDamage(penerate);
                        logs.push_back(Log(j, i, actions[j].first->GetAttribute(), penerate, 0, EFFECT_PENETRATE));
                    }
                }
            }
            else {
                TakeDamage(i, j, actions[i].first->GetAttribute(), actions[i].first->GetPoint(), false);
            }
        }
    }
}

void Controller::EndTurn() {
    for (auto player : players) {
        player->UpdateRealm();
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

void Controller::RecoverMP(int player, int amount) {
    players[player]->RecoverMP(amount);
    logs.push_back(Log(LOG_MP, player, amount));
}

void Controller::ConsumeMP(int player, int amount) {
    players[player]->ConsumeMP(amount);
    logs.push_back(Log(LOG_CONSUME, player, amount));
}

void Controller::MakeMove(int subject, int object, int amount, std::string name, int point) {
    players[subject]->ConsumeMP(amount);
    logs.push_back(Log(subject, object, amount, name, point));
}

void Controller::SkipMove(int player) {
    logs.push_back(Log(player));
}

void Controller::RecoverATK(int player, int amount) {
    players[player]->RecoverATK(amount);
    logs.push_back(Log(LOG_ATK, player, amount));
}

void Controller::RecoverHP(int player, int amount) {
    players[player]->RecoverHP(amount);
    logs.push_back(Log(LOG_HP, player, amount));
}

void Controller::TakeDamage(int subject, int object, ATTRIBUTE_TYPE attribute, int amount, bool physical) {
    players[object]->TakeDamage(amount, physical);
    logs.push_back(Log(subject, object, attribute, physical ? 0 : amount, physical ? amount : 0));
}

void Controller::DodgeSuccess(int subject, int object) {
    players[object]->DodgeSuccess();
    logs.push_back(Log(subject, object));
}
