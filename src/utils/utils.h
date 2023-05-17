#ifndef FLOUNDER_GAME_UTILS_H
#define FLOUNDER_GAME_UTILS_H

#include "constants.h"

#include <cstdlib>
#include <mutex>

namespace flounder::utils
{
[[noreturn]] inline void quit(ExitCode exit_code)
{
    static std::mutex exit_mutex;
    std::unique_lock<std::mutex> const exit_lock{exit_mutex};
    // NOLINTNEXTLINE(concurrency-mt-unsafe)
    std::exit(static_cast<int>(exit_code));
}
} // namespace flounder::utils

#endif // FLOUNDER_GAME_UTILS_H
