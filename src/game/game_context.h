#ifndef FLOUNDER_GAME_GAME_GAME_CONTEXT_H
#define FLOUNDER_GAME_GAME_GAME_CONTEXT_H

namespace flounder
{
template<typename GameInformation>
class GameContext
{
public:
    GameContext() = default;

    void request(GameInformation&& information) { (void*)information; }
};
} // namespace flounder

#endif // FLOUNDER_GAME_GAME_GAME_CONTEXT_H
