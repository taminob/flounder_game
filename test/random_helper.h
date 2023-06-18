#ifndef FLOUNDER_GAME_TEST_RANDOM_HELPER_H
#define FLOUNDER_GAME_TEST_RANDOM_HELPER_H

#include "utils/flags.h"

#include <concepts>
#include <random>
#include <string>
#include <string_view>

constexpr unsigned int AUTO_SEED = 0x1234;
template<typename Distribution, unsigned int seed = AUTO_SEED>
class Random
{
public:
    explicit constexpr Random(Distribution&& dist) : random_generator{seed}, dist{dist} { }

    constexpr void reset() { random_generator.seed(seed); }

    constexpr auto operator()() { return dist(random_generator); }

private:
    std::mt19937_64 random_generator;
    Distribution dist;
};

// random bool generation

template<typename T>
    requires std::same_as<T, bool>
inline T randomValue()
{
    return Random(std::uniform_int_distribution(0, 1))();
}

// random float generation

template<typename T>
    requires std::floating_point<T>
inline T randomValue(T min, T max)
{
    return Random(std::uniform_real_distribution<T>(min, max))();
}

template<typename T>
    requires std::floating_point<T>
inline T randomValue()
{
    return randomValue<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

// random int generation

template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
inline T randomValue(T min, T max)
{
    return Random(std::uniform_int_distribution<T>(min, max))();
}

template<typename T>
    requires std::integral<T> && (!std::same_as<T, bool>)
inline T randomValue()
{
    return randomValue<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

// random string generation

enum class StringAttribute
{
    none = 0x00,
    upperCase = 0x01,
    lowerCase = 0x02,
    numbers = 0x04,
    specialCharacters = 0x08,
    spaces = 0x10,
    all = 0xFF,
};

using StringAttributes = flounder::Flags<StringAttribute>;

template<typename T>
    requires std::convertible_to<T, std::string>
inline std::string randomValue(
 std::size_t min_length, std::size_t max_length, StringAttributes attributes)
{
    constexpr std::string_view LOWER_CHAR_SET = "abcdefghijklmnopqrstuvwxyz";
    constexpr std::string_view UPPER_CHAR_SET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr std::string_view NUMBER_CHAR_SET = "1234567890";
    constexpr std::string_view SPECIAL_CHAR_SET = "!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?";

    std::string total_char_set;
    if(attributes & StringAttribute::lowerCase)
        total_char_set += LOWER_CHAR_SET;
    if(attributes & StringAttribute::upperCase)
        total_char_set += UPPER_CHAR_SET;
    if(attributes & StringAttribute::numbers)
        total_char_set += NUMBER_CHAR_SET;
    if(attributes & StringAttribute::specialCharacters)
        total_char_set += SPECIAL_CHAR_SET;
    if(attributes & StringAttribute::spaces)
        total_char_set += ' ';

    std::string result;
    std::size_t length = Random(
     std::uniform_int_distribution<std::size_t>(min_length, max_length))();
    auto random = Random(std::uniform_int_distribution<std::size_t>(0, total_char_set.size() - 1));
    for(std::size_t i = 0; i < length; ++i)
        result += total_char_set.at(random());
    return result;
}

template<typename T>
    requires std::convertible_to<T, std::string>
inline std::string randomValue(std::size_t min_length, std::size_t max_length)
{
    return randomValue<T>(min_length, max_length, StringAttribute::all);
}

template<typename T>
    requires std::convertible_to<T, std::string>
inline std::string randomValue(StringAttributes attributes)
{
	constexpr auto MAX_LENGTH = 1e6;
    return randomValue<T>(0, MAX_LENGTH, attributes);
}

template<typename T>
    requires std::convertible_to<T, std::string>
inline std::string randomValue()
{
    return randomValue<T>(StringAttribute::all);
}

// random array generation

template<typename T, std::size_t n, typename... Args>
inline std::array<T, n> randomValues(Args&&... args)
{
    std::array<T, n> result;
    for(auto& value : result)
        value = randomValue<T>(args...);
    return result;
}

#endif // FLOUNDER_GAME_TEST_RANDOM_HELPER_H
