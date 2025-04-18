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
    return reward == 0;
}

int SuZeroState_5dcengine::getReward() const
{
    return reward;
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

AllLegalAction SuZeroState_5dcengine::getAllLegalAction() const
{
    std::map<std::tuple<int, int>, std::vector<std::pair<int, int>>> result;
    if(!selection.has_value())
    {
        for(const auto& [p0, bb] : s.gen_movable_pieces())
        {
            std::vector<std::pair<int, int>> rn;
            for(int pos : marked_pos(bb))
            {
                vec4 p = vec4(pos, p0);
                rn.push_back(std::make_pair(p.x(), p.y()));
            }
            result[std::make_tuple(p0.l(), p0.t())] = rn;
        }
        return {s.can_submit(), result};
    }
    else
    {
        vec4 p = selection.value();
        auto moves = s.player ? s.m.gen_moves<true>(p) : s.m.gen_moves<false>(p);
        for(const auto& [q0, bb] : moves)
        {
            std::vector<std::pair<int, int>> rn;
            for(int pos : marked_pos(bb))
            {
                vec4 q = vec4(pos, q0);
                rn.push_back(std::make_pair(q.x(), q.y()));
            }
            result[std::make_tuple(q0.l(), q0.t())] = rn;
        }
        return {s.can_submit(), result};
    }
}

std::array<float, 2> SuZeroState_5dcengine::forceScoring() const
{
    return std::array<float, 2>();
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::switchActivePlayer() const
{
    std::shared_ptr<SuZeroState_5dcengine> ss = std::make_shared<SuZeroState_5dcengine>(*this);
    ss->s.apply_move(full_move::submit());
    return ss;
}

std::shared_ptr<SuZeroState> SuZeroState_5dcengine::selectMovePosition(std::array<int, 4> a)
{
    std::shared_ptr<SuZeroState_5dcengine> ss = std::make_shared<SuZeroState_5dcengine>(*this);
    if(!selection.has_value())
    {
        ss->selection = std::make_optional<vec4>(a[2], a[3], a[1], a[0]);
    }
    else
    {
        vec4 p = selection.value();
        vec4 q = vec4(a[2], a[3], a[1], a[0]);
        bool flag = ss->s.apply_move(full_move::move(p, q-p));
        if(!flag)
        {
            std::cerr << "invalid move " << full_move::move(p, q-p) << std::endl;
            throw std::runtime_error("invalid move");
        }
        if(ss->s.find_check())
        {
            reward = 1;
        }
        else if(ss->s.gen_movable_pieces().empty())
        {
            reward = -1;
        }
    }
    return ss;
}

