#ifndef FLOUNDER_GAME_FLAGS_H
#define FLOUNDER_GAME_FLAGS_H

#include <initializer_list>

namespace flounder
{
template<typename FlagEnum, typename InternalType = unsigned int>
class Flags
{
public:
    constexpr Flags() : value{0} { }
    // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
    explicit(false) constexpr Flags(FlagEnum flag) : Flags{{flag}} { }
    constexpr Flags(std::initializer_list<FlagEnum> flags) : value{0x00}
    {
        for(auto flag : flags)
            this->add(flag);
    }

    constexpr void add(FlagEnum flag) { this->value |= toInternal(flag); }
    constexpr void remove(FlagEnum flag) { this->value &= ~toInternal(flag); }

    [[nodiscard]] constexpr bool has(FlagEnum flag) const
    {
        return (this->value & toInternal(flag)) != 0x00;
    }
    [[nodiscard]] constexpr bool operator&(FlagEnum flag) const { return has(flag); }

    constexpr Flags operator|(Flags rhs) const { return Flags{this->value | rhs.value}; }
    constexpr Flags operator|(FlagEnum rhs) const { return *this | Flags{rhs}; }
    constexpr Flags& operator|=(Flags rhs)
    {
        add(rhs);
        return *this;
    }
    constexpr Flags& operator|=(FlagEnum rhs) { return *this |= Flags{rhs}; }

protected:
    explicit constexpr Flags(InternalType value) : value{value} { }
    static constexpr InternalType toInternal(FlagEnum level)
    {
        return static_cast<InternalType>(level);
    }

private:
    InternalType value;
};

template<typename FlagEnum>
inline Flags<FlagEnum> operator|(FlagEnum lhs, FlagEnum rhs)
{
    return Flags<FlagEnum>({lhs, rhs});
}

template<typename FlagEnum>
inline Flags<FlagEnum> operator|(FlagEnum lhs, Flags<FlagEnum> rhs)
{
    return rhs | lhs;
}
} // namespace flounder

#endif // FLOUNDER_GAME_FLAGS_H
