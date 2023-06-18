#ifndef FLOUNDER_GAME_TURN_GAME_H
#define FLOUNDER_GAME_TURN_GAME_H

#include "game.h"

namespace flounder
{
class TurnGame : public Game
{
public:
    TurnGame() = default;

    void start() override { }
};
} // namespace flounder

#endif // FLOUNDER_GAME_TURN_GAME_H
