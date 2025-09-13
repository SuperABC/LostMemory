#include "player.h"
#include "controller.h"

#include <iostream>
#include <algorithm>

//#define RANDOM_MOVE
#define SPECIFIC_MOVE


using namespace std;

std::vector<std::string> attributeText = {
    "无属性",
    "金属性",
    "木属性",
    "水属性",
    "火属性",
    "土属性",
    "五行属性"
};

int GetRandom(int range) {
    if (range <= 0)return 0;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, range - 1);
    int ret = dist(rng);

    return ret;
}

void PrintNews(vector<Log> news, vector<Player*> players) {
    for (auto n : news) {
        switch (n.type) {
        case LOG_MP:
            cout << players[n.subject]->GetName() << "真气量回复至" << players[n.subject]->GetCurrentMP() << endl;
            break;
        case LOG_ATK:
            cout << players[n.subject]->GetName() << "武力值回复至" << players[n.subject]->GetCurrentATK() << endl;
            break;
        case LOG_HP:
            cout << players[n.subject]->GetName() << "健康值回复至" << players[n.subject]->GetCurrentHP() << endl;
            break;
        case LOG_CONSUME:
            cout << players[n.subject]->GetName() << "消耗" << n.amount << "点武力值" << endl;
            break;
        case LOG_SKIP:
            cout << players[n.subject]->GetName() << "跳过回合" << endl;
            break;
        case LOG_MOVE:
            cout << players[n.subject]->GetName() << "消耗" << n.amount << "点真气对" << players[n.object]->GetName() << "出招：" <<
                n.name << ", 点数" << n.pointAtk << endl;
            break;
        case LOG_DAMAGE:
            cout << players[n.subject]->GetName() << "对" << players[n.object]->GetName() << "造成";
            if (n.pointAtk > 0) {
                cout << attributeText[n.attribute] << n.pointAtk << "点招式武力伤害" << endl;
            }
            else {
                cout  << n.pointHp << "点招式物理伤害" << endl;
            }
            break;
        case LOG_DODGE:
            cout << players[n.object]->GetName() << "闪避成功" << endl;
            break;
        case LOG_EFFECT:
            switch (n.effect) {
            case EFFECT_PENETRATE:
                cout << players[n.subject]->GetName() << "对" << players[n.object]->GetName() << "造成";
                if (n.pointAtk > 0) {
                    cout << attributeText[n.attribute] << n.pointAtk << "点穿透武力伤害" << endl;
                }
                else {
                    cout << n.pointHp << "点穿透物理伤害" << endl;
                }
                break;
            case EFFECT_REBOUND:
                cout << players[n.subject]->GetName() << "对" << players[n.object]->GetName() << "造成";
                if (n.pointAtk > 0) {
                    cout << attributeText[n.attribute] << n.pointAtk << "点反弹武力伤害" << endl;
                }
                else {
                    cout << n.pointHp << "点反弹物理伤害" << endl;
                }
                break;
            case EFFECT_ABSORB:
                cout << players[n.subject]->GetName() << "吸收" << n.amount << "点真气" << endl;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

int main() {
    Player player1("张三", 1000, 1200, 1600, 20, 40);
    Player player2("李四", 1000, 1080, 1800, 22, 40);
    vector<Player*> players = { &player1, &player2 };
    for (auto action : actions) {
        player1.AddAction(action);
        player2.AddAction(action);
    }

    Controller game({ &player1, &player2 });

    cout << "《五行斗诀》战斗开始！" << endl;
    cout << player1.GetName() << " VS " << player2.GetName() <<  endl;

    int turnCount = 0;
    while (player1.IsAlive() && player2.IsAlive()) {
        cout << "\n--- 第 " << ++turnCount << " 回合 ---" << endl;
        cout << player1.GetName() << ": HP=" << player1.GetCurrentHP()
            << ", ATK=" << player1.GetCurrentATK()
            << ", MP=" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << ": HP=" << player2.GetCurrentHP()
            << ", ATK=" << player2.GetCurrentATK()
            << ", MP=" << player2.GetCurrentMP() << endl;

        game.StartTurn();
        PrintNews(game.GetNews(), players);

        Action *action1, *action2;
#ifdef RANDOM_MOVE
        if (GetRandom(4)) {
            action1 = player1.GetAction(GetRandom(actions.size() + 20));
        }
        else {
            action1 = player1.GetAction(GetRandom(actions.size() + 10), GetRandom(actions.size() + 10));
        }
        if (GetRandom(4)) {
            action2 = player2.GetAction(GetRandom(actions.size() + 20));
        }
        else {
            action2 = player2.GetAction(GetRandom(actions.size() + 10), GetRandom(actions.size() + 10));
        }
#endif // RANDOM_MOVE
#ifdef SPECIFIC_MOVE
        action1 = actions[20];
        //action1 = new DualAction(actions[31], actions[172]);
        action2 = actions[240];
        //action2 = new DualAction(actions[49], actions[189]);
#endif
        game.ActionTurn({ { action1, 1 }, { action2, 0 } });
        PrintNews(game.GetNews(), players);
        PrintNews(game.GetNews(), players);

        game.CheckTurn({ { action1, 1 }, { action2, 0 } });
        PrintNews(game.GetNews(), players);

        game.EndTurn();
        PrintNews(game.GetNews(), players);

        cout << "回合结束" << endl;

        if (action1 && action1->GetType() != ACTION_SINGLE)delete action1;
        if (action2 && action2->GetType() != ACTION_SINGLE)delete action2;
    }

    if (!player1.IsAlive() && !player2.IsAlive()) {
        cout << "\n战斗结束！同归于尽!" << endl;
    }
    else {
        cout << "\n战斗结束！胜利者: " << (player1.IsAlive() ? player1 : player2).GetName() << "!" << endl;
    }
}