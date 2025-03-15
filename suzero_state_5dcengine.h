#ifndef SUZERO_STATE_5DCENGINE_H
#define SUZERO_STATE_5DCENGINE_H

#include "suzero_interface.h"

class SuZeroState_5dcengine : public SuZeroState {
public:
    static std::shared_ptr<SuZeroState> getNewTurnZeroAIMode();
    bool getPlayer() override;
    bool isGameOverForAI() const override;
    int getRewardForAI() const override;
    StateForAI getStateForAI() const override;
    std::tuple<bool, std::vector<int>> getAllLegalActionForAI() const override;
    std::array<float, 2> forceScoring() const override;
    virtual std::shared_ptr<SuZeroState> switchActivePlayerForAI() const override;
    virtual std::shared_ptr<SuZeroState> selectMovePositionForAI(std::array<int, 4>) const override;
};

#endif //SUZERO_STATE_5DCENGINE_H
