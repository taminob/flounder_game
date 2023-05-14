#ifndef FLOUNDER_GAME_CERR_OUTPUT_H
#define FLOUNDER_GAME_CERR_OUTPUT_H

#include "output.h"

#include <iostream>

namespace flounder
{
class CerrOutput : public Output
{
public:
    CerrOutput() = default;
    std::ostream& stream() override
    {
        if(currentLevel() == OutputLevel::error || currentLevel() == OutputLevel::fatal)
            std::cerr << OutputManipulator::RED;
        else if(currentLevel() == OutputLevel::warning)
            std::cerr << OutputManipulator::YELLOW;
        else
            std::cerr << OutputManipulator::RESET;
        return std::cerr;
    }
};

} // namespace flounder

#endif // FLOUNDER_GAME_CERR_OUTPUT_H
