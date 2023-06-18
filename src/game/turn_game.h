#ifndef FLOUNDER_GAME_TURN_GAME_H
#define FLOUNDER_GAME_TURN_GAME_H

#include "game.h"

namespace flounder
{
template<typename GameInformation>
class TurnGame : public Game<GameInformation>
{
public:
    TurnGame() = default;

    void start() override { }
};
} // namespace flounder

#endif // FLOUNDER_GAME_TURN_GAME_H
