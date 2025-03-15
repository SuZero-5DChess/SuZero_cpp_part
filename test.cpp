#include "suzero_interface.h"
#include "suzero_state_5dcengine.h"
#include <memory>
#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    std::shared_ptr<SuZeroState> s = std::make_shared<SuZeroStateDummyImplementation>();
    unordered_set<StateForAI> a;
    cout << "test finished" << endl;
    return 0;
}
