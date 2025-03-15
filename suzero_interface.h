#ifndef SUZERO_INTERFACE_H
#define SUZERO_INTERFACE_H

#include <cstdint>
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <memory>

inline void hash_combine(std::size_t& seed) { }

template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    hash_combine(seed, rest...);
}

struct StateForAI
{
    bool isWhiteTrun;
    bool hasSelection;
    std::vector<uint64_t>  bitboards;
    std::array<std::vector<int>, 2> shapeOfBoards;
    int pieceCoords[4];
};

template<>
struct std::hash<StateForAI>
{
    std::size_t operator()(const StateForAI& s) const noexcept
    {
        size_t seed = 0;
        hash_combine(seed, s.isWhiteTrun, s.hasSelection);
        hash_combine(seed, s.pieceCoords[0], s.pieceCoords[1], s.pieceCoords[2], s.pieceCoords[3]);
        for(uint64_t x: s.bitboards)
        {
            x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
            x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
            seed ^= x ^ (x >> 31) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        for(auto xs : s.shapeOfBoards)
        {
            for(auto x : xs)
            {
                seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};


/**
 * This is the interface. An implementation of this interface
 * must override every pure virtual method in this class.
 * Ideally, it also provides a static method `getNewTurnZeroAIMode`
 * which returns a `shared_ptr<SuZeroState>`
 * (See: SuZeroStateDummyImplementation below)
 */
class SuZeroState {
public:
    virtual std::size_t getStateHash()
    {
        StateForAI s = getStateForAI();
        return 0;//std::hash<StateForAI>(s);
    }
    virtual bool getPlayer() = 0;
    virtual bool isGameOver() const = 0;
    virtual int getReward() const = 0;
    virtual StateForAI getStateForAI() const = 0;
    virtual std::tuple<bool, std::vector<int>> getAllLegalAction() const = 0;
    virtual std::array<float, 2> forceScoring() const = 0;
    virtual std::shared_ptr<SuZeroState> switchActivePlayer() const = 0;
    virtual std::shared_ptr<SuZeroState> selectMovePosition(std::array<int, 4>) const = 0;
};

class SuZeroStateDummyImplementation : public SuZeroState {
public:
    bool getPlayer() override 
    {
        return true; // Dummy return value
    }

    bool isGameOver() const override 
    {
        return false; // Dummy return value
    }

    int getReward() const override 
    {
        return 0; // Dummy return value
    }

    StateForAI getStateForAI() const override
    {
        return StateForAI{}; // Return a default-constructed state
    }

    std::tuple<bool, std::vector<int>> getAllLegalAction() const override 
    {
        return {false, {}}; // No legal actions
    }

    std::array<float, 2> forceScoring() const override 
    {
        return {0.0f, 0.0f}; // Dummy scores
    }

    std::shared_ptr<SuZeroState> switchActivePlayer() const override
    {
        return nullptr;
    }

    std::shared_ptr<SuZeroState> selectMovePosition(std::array<int, 4>) const override
    {
        return nullptr;
    }
    
    static std::shared_ptr<SuZeroState> getNewTurnZeroAIMode()
    {
        return std::make_shared<SuZeroStateDummyImplementation>();
    }
};

#endif //SUZERO_INTERFACE_H
