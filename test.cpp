#include "suzero_interface.h"
#include "suzero_state_5dcengine.h"
#include <memory>
#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    std::shared_ptr<SuZeroState> s = SuZeroState_5dcengine::getNewTurnZeroAIMode();
    unordered_set<StateForAI> a;
    cout << s->getStateHash() << endl;
    cout << s->getAllLegalAction().canSwitchPlayer << endl;
    s = s->selectMovePosition({0,1,0,1});
    cout << s->getStateHash() << endl;
    cout << s->getAllLegalAction().canSwitchPlayer << endl;
    s = s->selectMovePosition({0,1,0,2});
    cout << s->getStateHash() << endl;
    cout << s->getAllLegalAction().canSwitchPlayer << endl;
    s = s->switchActivePlayer();
    cout << s->getStateHash() << endl;
    return 0;
}
