#ifndef FLOUNDER_GAME_CONCEPTS_H
#define FLOUNDER_GAME_CONCEPTS_H

#include <string>
#include <type_traits>

namespace flounder
{
template<typename T>
concept integer = std::is_integral_v<T>;

template<typename T>
concept floating_point = std::is_floating_point_v<T>;

template<typename T>
concept string = std::is_same_v<T, std::string>;

template<typename T>
concept boolean = std::is_same_v<T, bool>;
} // namespace flounder

#endif // FLOUNDER_GAME_CONCEPTS_H
