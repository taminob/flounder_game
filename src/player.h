#ifndef FLOUNDER_GAME_PLAYER_H
#define FLOUNDER_GAME_PLAYER_H

#include "output/output_manager.h"

namespace flounder
{
class GameContext;

template<typename GameType>
class Player
{
public:
    Player();
    explicit Player(std::shared_ptr<OutputManager> output);

    void prepare();
    void act(const GameContext<typename GameType::Information>& context);

private:
    std::shared_ptr<OutputManager> output;
};

#include "player.hpp"

} // namespace flounder

#endif // FLOUNDER_GAME_PLAYER_H
