#ifndef FLOUNDER_GAME_COUT_OUTPUT_H
#define FLOUNDER_GAME_COUT_OUTPUT_H

#include "output.h"

#include <iostream>

namespace flounder
{
class CoutOutput : public Output
{
public:
    CoutOutput() = default;
    ~CoutOutput() override { std::cout << std::flush; }
    CoutOutput(const CoutOutput&) = default;
    CoutOutput(CoutOutput&&) = default;
    CoutOutput& operator=(const CoutOutput&) = default;
    CoutOutput& operator=(CoutOutput&&) = default;

    std::ostream& stream() override { return std::cout; }
};

} // namespace flounder

#endif // FLOUNDER_GAME_COUT_OUTPUT_H
