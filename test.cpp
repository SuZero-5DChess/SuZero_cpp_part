#include "suzero_interface.h"
#include "suzero_state_5dcengine.h"
#include <memory>
#include <iostream>

using namespace std;

int main()
{
    std::shared_ptr<SuZeroState> s = std::make_shared<SuZeroStateDummyImplementation>();
    cout << "test finished" << endl;
    return 0;
}
