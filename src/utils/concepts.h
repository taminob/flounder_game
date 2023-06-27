#ifndef FLOUNDER_GAME_CONCEPTS_H
#define FLOUNDER_GAME_CONCEPTS_H

#include <string>
#include <type_traits>

namespace flounder {
template <typename T>
concept is_integer = std::is_integral_v<T>;

template <typename T>
concept is_floating_point = std::is_floating_point_v<T>;

template <typename T>
concept is_string = std::is_same_v<T, std::string>;

template <typename T>
concept is_boolean = std::is_same_v<T, bool>;

template <typename T>
concept is_const = std::is_const_v<T>;

template <typename T>
concept is_mutable = !
std::is_const_v<T>;

template <typename T>
concept is_container = requires(T container, const T const_container) {
                         { const_container.begin() } -> std::forward_iterator;
                         { const_container.end() } -> std::forward_iterator;
                         { container.begin() } -> std::forward_iterator;
                         { container.end() } -> std::forward_iterator;
                       };
} // namespace flounder

#endif // FLOUNDER_GAME_CONCEPTS_H
