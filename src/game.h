#ifndef FLOUNDER_GAME_GAME_H
#define FLOUNDER_GAME_GAME_H

#include "player.h"

namespace flounder
{
template<typename GameInformation>
class GameContext
{
public:
    GameContext() = default;

    void request(GameInformation) { }
};

template<typename GameInformation>
class Game
{
public:
    Game();

    virtual ~Game() = default;
    Game(const Game&) = default;
    Game(Game&&) noexcept = default;
    Game& operator=(const Game&) = default;
    Game& operator=(Game&&) noexcept = default;

    virtual void start() = 0;

    using Information = GameInformation;

private:
    std::vector<Player> players;
};
} // namespace flounder

#endif // FLOUNDER_GAME_GAME_H
