#include "player.h"
#include "controller.h"

#include <iostream>
#include <algorithm>


using namespace std;

std::vector<Action *> actions = {
    new MoveAction("�����Ʒ�", ATTRIBUTE_NONE, 15, 12, Realm::YELLOW_INIT),
    new MoveAction("����ȭ��", ATTRIBUTE_NONE, 18, 15, Realm::YELLOW_INIT),
    new MoveAction("�����ȷ�", ATTRIBUTE_NONE, 22, 18, Realm::YELLOW_INIT),
    new MoveAction("�����Ʒ�", ATTRIBUTE_NONE, 28, 20, Realm::MYSTIC_INIT),
    new MoveAction("����ȭ��", ATTRIBUTE_NONE, 35, 25, Realm::MYSTIC_INIT),
    new MoveAction("�����ȷ�", ATTRIBUTE_NONE, 40, 28, Realm::MYSTIC_INIT),
};
int GetRandom(int range) {
    if (range <= 0)return 0;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(0, range - 1);
    int ret = dist(rng);

    return ret;
}

int main() {
    Player player1("����", 100, 50, 80, 20);
    Player player2("����", 90, 55, 70, 25);
    player1.AddAction(new SkipAction());
    player2.AddAction(new SkipAction());
    for (auto action : actions) {
        player1.AddAction(action);
        player2.AddAction(action);
    }

    Controller game(&player1, &player2);

    cout << "�����ж�����ս����ʼ��" << endl;
    cout << player1.GetName() << " VS " << player2.GetName() <<  std::endl;

    int turnCount = 0;
    while (player1.IsAlive() && player2.IsAlive()) {
        cout << "\n--- �� " << ++turnCount << " �غ� ---" << endl;
        cout << player1.GetName() << ": HP=" << player1.GetCurrentHP()
            << ", ATK=" << player1.GetCurrentATK()
            << ", MP=" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << ": HP=" << player2.GetCurrentHP()
            << ", ATK=" << player2.GetCurrentATK()
            << ", MP=" << player2.GetCurrentMP() << endl;

        game.StartTurn();
        cout << player1.GetName() << "�������ظ���" << player1.GetCurrentMP() << endl;
        cout << player2.GetName() << "�������ظ���" << player2.GetCurrentMP() << endl;

        Action *action1 = player1.GetActions()[GetRandom(7)];
        Action* action2 = player2.GetActions()[GetRandom(7)];
        game.ActionTurn(action1, action2);
        if (action1->GetType() == ACTION_SKIP) {
            cout << player1.GetName() << "�����غ�" << endl;
        }
        else {
            cout << player1.GetName() << "���У�" << ((MoveAction *)action1)->GetName() <<
                "������" << action1->GetPower() << "������" << endl;
        }
        if (action2->GetType() == ACTION_SKIP) {
            cout << player2.GetName() << "�����غ�" << endl;
        }
        else {
            cout << player2.GetName() << "���У�" << ((MoveAction*)action2)->GetName() <<
                "������" << action2->GetPower() << "������" << endl;
        }

        auto check = game.CheckTurn(action1, action2);
        if (check.first == 0) {
            cout << player1.GetName() << "δ���˺�" << endl;
        }
        else {
            cout << player1.GetName() << "�ܵ�" << check.first << "�˺�" << endl;
        }
        if (check.second == 0) {
            cout << player2.GetName() << "δ���˺�" << endl;
        }
        else {
            cout << player2.GetName() << "�ܵ�" << check.second << "�˺�" << endl;
        }

        game.EndTurn();
        cout << "�غϽ���" << endl;
    }

    Player& winner = player1.IsAlive() ? player1 : player2;
    cout << "\nս��������ʤ����: " << winner.GetName() << "!" << endl;
}