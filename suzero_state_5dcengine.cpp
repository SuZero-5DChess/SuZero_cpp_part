#include "suzero_state_5dcengine.h"

const static std::string t0_fen = ""
"[Size 8x8]"
"[r*nbqk*bnr*/p*p*p*p*p*p*p*p*/8/8/8/8/P*P*P*P*P*P*P*P*/R*NBQK*BNR*:0:0:b]\n"
"[r*nbqk*bnr*/p*p*p*p*p*p*p*p*/8/8/8/8/P*P*P*P*P*P*P*P*/R*NBQK*BNR*:0:1:w]\n";

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::getNewTurnZeroAIMode()
{
    return std::make_shared<SuZeroState_5dcengine>(t0_fen);
}

bool SuZeroState_5dcengine::getPlayer()
{
    return !s.player;
}

bool SuZeroState_5dcengine::isGameOver() const
{
    if(s.match_status != match_status_t::PLAYING)
    {
        return true;
    }
    else if(s.gen_movable_pieces().empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int SuZeroState_5dcengine::getReward() const
{
    if(s.match_status != match_status_t::PLAYING)
    {
        return 1;
    }
    else if(s.gen_movable_pieces().empty())
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

StateForAI SuZeroState_5dcengine::getStateForAI() const
{
    std::vector<uint64_t> bbs;
    std::array<std::vector<int>, 2>  shapes;
    int l = 0, t = 0, x = 0, y = 0;
    if(selection.has_value())
    {
        vec4 v = selection.value();
        l = v.l();
        t = v.t();
        x = v.x();
        y = v.y();
    }
    const multiverse& m = s.m;
    int count = 0;
    for(int l = m.l_min; l <= m.l_max; l++)
    {
        int u = multiverse::l_to_u(l);
        count += m.timeline_end[u] - m.timeline_start[u] + 1;
    }
    bbs.reserve(count*12);
    for(int l = m.l_min; l <= m.l_max; l++)
    {
        int u = multiverse::l_to_u(l);
        for(int v = m.timeline_start[u]; v <= m.timeline_end[u]; v++)
        {
            auto [t,c] = multiverse::v_to_tc(v);
            std::shared_ptr<board> bp = m.get_board(l, t, c);
            bbs.push_back(bp->black() & bp->king());
            bbs.push_back(bp->black() & bp->queen());
            bbs.push_back(bp->black() & bp->rook());
            bbs.push_back(bp->black() & bp->knight());
            bbs.push_back(bp->black() & bp->bishop());
            bbs.push_back(bp->black() & bp->pawn());
            bbs.push_back(bp->white() & bp->king());
            bbs.push_back(bp->white() & bp->queen());
            bbs.push_back(bp->white() & bp->rook());
            bbs.push_back(bp->white() & bp->knight());
            bbs.push_back(bp->white() & bp->bishop());
            bbs.push_back(bp->white() & bp->pawn());
        }
    }
    for(int l = 0; l <= m.l_max; l++)
    {
        int u = multiverse::l_to_u(l);
        shapes[0].push_back(m.timeline_start[u]);
        shapes[0].push_back(m.timeline_end[u]);
    }
    for(int l = 0; l >= m.l_min; l--)
    {
        int u = multiverse::l_to_u(l);
        shapes[1].push_back(m.timeline_start[u]);
        shapes[1].push_back(m.timeline_end[u]);
    }
    StateForAI ss = {
        .isWhiteTrun = !s.player,
        .hasSelection = selection.has_value(),
        .shapeOfBoards = std::move(shapes),
        .bitboards = std::move(bbs),
        .pieceCoords = {l, t, x, y}
    };
    return ss;
}

std::tuple<bool, std::vector<int>> SuZeroState_5dcengine::getAllLegalAction() const
{
    return std::tuple<bool, std::vector<int>>();
}

std::array<float, 2> SuZeroState_5dcengine::forceScoring() const
{
    return std::array<float, 2>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::switchActivePlayer() const
{
    return std::shared_ptr<SuZeroState>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::selectMovePosition(std::array<int, 4>) const
{
    return std::shared_ptr<SuZeroState>();
}

