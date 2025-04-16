#ifndef SUZERO_STATE_5DCENGINE_H
#define SUZERO_STATE_5DCENGINE_H

#include "suzero_interface.h"
#include "state.h"



class SuZeroState_5dcengine : public SuZeroState
{
    state s;
    std::optional<vec4> selection;
public:
    SuZeroState_5dcengine(std::string fen) :s{multiverse{fen}} {}
    static std::shared_ptr<SuZeroState> getNewTurnZeroAIMode();
    bool getPlayer() override;
    bool isGameOver() const override;
    int getReward() const override;
    StateForAI getStateForAI() const override;
    std::tuple<bool, std::vector<int>> getAllLegalAction() const override;
    std::array<float, 2> forceScoring() const override;
    virtual std::shared_ptr<SuZeroState> switchActivePlayer() const override;
    virtual std::shared_ptr<SuZeroState> selectMovePosition(std::array<int, 4>) const override;
};

#endif //SUZERO_STATE_5DCENGINE_H
