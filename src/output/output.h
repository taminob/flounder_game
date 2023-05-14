#ifndef FLOUNDER_GAME_OUTPUT_H
#define FLOUNDER_GAME_OUTPUT_H

#include "output_levels.h"

#include <ostream>

#include <fmt/format.h>

namespace flounder
{
template<typename StreamType>
class BaseOutput
{
public:
    BaseOutput() = default;
    virtual ~BaseOutput() = default;
    BaseOutput(const BaseOutput&) = default;
    BaseOutput(BaseOutput&&) noexcept = default;
    BaseOutput& operator=(const BaseOutput&) = default;
    BaseOutput& operator=(BaseOutput&&) noexcept = default;
    virtual StreamType& stream() = 0;

    template<typename Argument>
    BaseOutput& operator<<(Argument&& argument)
    {
        stream() << argument;
        return *this;
    }

    virtual BaseOutput& operator<<(OutputLevel level)
    {
        this->current_level = level;
        return *this;
    }

protected:
    OutputLevel currentLevel() { return current_level; }

private:
    OutputLevel current_level = OutputLevel::none;
};

using Output = BaseOutput<std::ostream>;
} // namespace flounder

#endif // FLOUNDER_GAME_OUTPUT_H
