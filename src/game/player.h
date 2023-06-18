#ifndef FLOUNDER_GAME_PLAYER_H
#define FLOUNDER_GAME_PLAYER_H

#include "game_context.h"
#include "output/output_manager.h"

namespace flounder
{
template<typename GameType>
class Player
{
public:
    explicit Player(std::shared_ptr<OutputManager> output = nullptr);

    void prepare();
    void act(const GameContext<typename GameType::Information>& context);

private:
    std::shared_ptr<OutputManager> output;
};

} // namespace flounder

#include "player.hpp"

#endif // FLOUNDER_GAME_PLAYER_H
