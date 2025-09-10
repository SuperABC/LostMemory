#include "controller.h"

#include <stdexcept>


using namespace std;

Controller::Controller(vector<Player*> players) : players(players) {
    rng.seed(random_device()());
}

bool Controller::CheckCounter(ATTRIBUTE_TYPE a1, ATTRIBUTE_TYPE a2) {
    return ATTRIBUTE_COUNTERS.find({ a1, a2 }) != ATTRIBUTE_COUNTERS.end();
}

double Controller::DodgeChance(int attackerAGI, int defenderAGI) {
    return static_cast<double>(
        defenderAGI * defenderAGI) / (attackerAGI * attackerAGI + defenderAGI * defenderAGI);
}

void Controller::StartTurn() {
    for (auto player : players) {
        player->RecoverMP();
    }
}

void Controller::ActionTurn(vector<pair<Action*, int>> actions) {
    if (actions.size() != players.size())
        throw runtime_error("Players and actions mismatch.");

    for (int i = 0; i < players.size(); i++) {
        if (actions[i].first->GetType() != ACTION_SKIP) {
            players[i]->ConsumePower(actions[i].first->GetPower());
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
                logs.push_back(Log(i, j));
                 continue;
            }
            else {
                int point = actions[i].first->GetPoint();
                players[j]->TakeDamage(point);
                logs.push_back(Log(i, j, actions[i].first->GetAttribute(), point, 0));
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
                    players[j]->TakeDamage(point1 - point2);
                    logs.push_back(Log(i, j, actions[i].first->GetAttribute(), point1 - point2, 0));
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
                    players[i]->TakeDamage(point2 - point1);
                    logs.push_back(Log(j, i, actions[j].first->GetAttribute(), point2 - point1, 0));
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
                int point = actions[i].first->GetPoint();
                players[j]->TakeDamage(point);
                logs.push_back(Log(i, j, actions[i].first->GetAttribute(), point, 0));
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
