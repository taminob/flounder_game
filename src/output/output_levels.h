#ifndef FLOUNDER_GAME_OUTPUT_LEVELS_H
#define FLOUNDER_GAME_OUTPUT_LEVELS_H

#include <initializer_list>

namespace flounder
{
enum class OutputLevel
{
    none = 0x00,
    user = 0x01,
    fatal = 0x02,
    error = 0x04,
    warning = 0x08,
    notice = 0x10,
    info = 0x20,
    debug = 0x40,
    all = 0xFF
};

class OutputLevels
{
public:
    OutputLevels() : value{0} { }
    // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
    explicit(false) OutputLevels(OutputLevel level) : OutputLevels({level}) { }
    OutputLevels(std::initializer_list<OutputLevel> levels) : value{0x00}
    {
        for(auto level : levels)
            addLevel(level);
    }

    void addLevel(OutputLevel level) { this->value |= toInternal(level); }
    void removeLevel(OutputLevel level) { this->value &= ~toInternal(level); }

    [[nodiscard]] bool hasLevel(OutputLevel level) const
    {
        return (this->value & toInternal(level)) != 0x00;
    }

    OutputLevels operator|(OutputLevels rhs) const { return OutputLevels{this->value | rhs.value}; }

private:
    explicit OutputLevels(unsigned int value) : value{value} { }
    static unsigned int toInternal(OutputLevel level) { return static_cast<unsigned int>(level); }

private:
    unsigned int value;
};

inline OutputLevels operator|(OutputLevel lhs, OutputLevel rhs)
{
    return OutputLevels({lhs, rhs});
}

inline OutputLevels operator|(OutputLevels lhs, OutputLevel rhs)
{
    lhs.addLevel(rhs);
    return lhs;
}

inline OutputLevels operator|(OutputLevel lhs, OutputLevels rhs)
{
    return rhs | lhs;
}
} // namespace flounder

#endif // FLOUNDER_GAME_OUTPUT_LEVELS_H
