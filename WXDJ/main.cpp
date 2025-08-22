#include "player.h"
#include "controller.h"

#include <iostream>
#include <algorithm>


using namespace std;

std::vector<Action *> actions = {
    new MoveAction("基础掌法", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new MoveAction("基础拳法", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new MoveAction("基础腿法", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),
    new MoveAction("进阶掌法", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new MoveAction("进阶拳法", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new MoveAction("进阶腿法", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
};
int GetRandom(int range) {
    if (range <= 0)return 0;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, range - 1);
    int ret = dist(rng);

    return ret;
}

int main() {
    Player player1("张三", 100, 50, 80, 20);
    Player player2("李四", 90, 55, 70, 25);
    player1.AddAction(new SkipAction());
    player2.AddAction(new SkipAction());
    for (auto action : actions) {
        player1.AddAction(action);
        player2.AddAction(action);
    }

    Controller game(&player1, &player2);

    cout << "《五行斗诀》战斗开始！" << endl;
    cout << player1.GetName() << " VS " << player2.GetName() <<  std::endl;

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
        cout << player1.GetName() << "真气量回复至" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << "真气量回复至" << player2.GetCurrentMP() << endl;

        Action *action1 = player1.GetActions()[GetRandom(7)];
        Action* action2 = player2.GetActions()[GetRandom(7)];
        game.ActionTurn(action1, action2);
        if (action1->GetType() == ACTION_SKIP) {
            cout << player1.GetName() << "跳过回合" << endl;
        }
        else {
            cout << player1.GetName() << "出招：" << ((MoveAction *)action1)->GetName() <<
                "，消耗" << action1->GetPower() << "真气量" << endl;
        }
        if (action2->GetType() == ACTION_SKIP) {
            cout << player2.GetName() << "跳过回合" << endl;
        }
        else {
            cout << player2.GetName() << "出招：" << ((MoveAction*)action2)->GetName() <<
                "，消耗" << action2->GetPower() << "真气量" << endl;
        }

        auto check = game.CheckTurn(action1, action2);
        if (check.first == 0) {
            cout << player1.GetName() << "未受伤害" << endl;
        }
        else {
            cout << player1.GetName() << "受到" << check.first << "伤害" << endl;
        }
        if (check.second == 0) {
            cout << player2.GetName() << "未受伤害" << endl;
        }
        else {
            cout << player2.GetName() << "受到" << check.second << "伤害" << endl;
        }

        game.EndTurn();
        cout << "回合结束" << endl;
    }

    Player& winner = player1.IsAlive() ? player1 : player2;
    cout << "\n战斗结束！胜利者: " << winner.GetName() << "!" << endl;
}