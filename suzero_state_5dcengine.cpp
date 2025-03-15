#include "suzero_state_5dcengine.h"

bool SuZeroState_5dcengine::getPlayer()
{
    return false;
}

bool SuZeroState_5dcengine::isGameOverForAI() const
{
    return false;
}

int SuZeroState_5dcengine::getRewardForAI() const
{
    return 0;
}

StateForAI SuZeroState_5dcengine::getStateForAI() const
{
    return StateForAI();
}

std::tuple<bool, std::vector<int>> SuZeroState_5dcengine::getAllLegalActionForAI() const
{
    return std::tuple<bool, std::vector<int>>();
}

std::array<float, 2> SuZeroState_5dcengine::forceScoring() const
{
    return std::array<float, 2>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::switchActivePlayerForAI() const
{
    return std::shared_ptr<SuZeroState>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::selectMovePositionForAI(std::array<int, 4>) const
{
    return std::shared_ptr<SuZeroState>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::getNewTurnZeroAIMode()
{
    return std::make_shared<SuZeroState_5dcengine>();
}
