#ifndef FLOUNDER_GAME_DISCOVERY_DISCOVERY_GAME_H
#define FLOUNDER_GAME_DISCOVERY_DISCOVERY_GAME_H

#include "game/turn_game.h"

namespace flounder::discovery
{
template<typename GameInformation>
class DiscoveryGame : public TurnGame<GameInformation>
{
};
} // namespace flounder::discovery
#endif // FLOUNDER_GAME_DISCOVERY_DISCOVERY_GAME_H
