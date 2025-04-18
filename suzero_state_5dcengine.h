#ifndef SUZERO_STATE_5DCENGINE_H
#define SUZERO_STATE_5DCENGINE_H

#include "suzero_interface.h"
#include "state.h"



class SuZeroState_5dcengine : public SuZeroState
{
    state s;
    std::optional<vec4> selection;
    int reward;
public:
    SuZeroState_5dcengine(std::string fen) :s{multiverse{fen}}, reward{0} {}
    static std::shared_ptr<SuZeroState> getNewTurnZeroAIMode();
    bool getPlayer() override;
    bool isGameOver() const override;
    int getReward() const override;
    StateForAI getStateForAI() const override;
    AllLegalAction getAllLegalAction() const override;
    std::array<float, 2> forceScoring() const override;
    std::shared_ptr<SuZeroState> switchActivePlayer() const override;
    std::shared_ptr<SuZeroState> selectMovePosition(std::array<int, 4>) override;
};

#endif //SUZERO_STATE_5DCENGINE_H
