#include "player.h"

namespace flounder
{
template<typename GameType>
Player<GameType>::Player(std::shared_ptr<OutputManager> output) : output{std::move(output)}
{
    if(!output)
        output = std::make_shared<OutputManager>();
}

template<typename GameType>
void Player<GameType>::prepare()
{
}

template<typename GameType>
void Player<GameType>::act(const GameContext<typename GameType::Information>& context)
{
    (void*)context;
}
} // namespace flounder
