#ifndef FLOUNDER_GAME_OUTPUT_H
#define FLOUNDER_GAME_OUTPUT_H

#include "output_levels.h"

#include <memory>
#include <mutex>
#include <ostream>

#include <fmt/format.h>

namespace flounder
{
struct OutputManipulator
{
    static constexpr const char* RESET = "\033[49m";

    static constexpr const char* RED = "\033[91m";
    static constexpr const char* GREEN = "\033[92m";
    static constexpr const char* YELLOW = "\033[93m";
    static constexpr const char* BLUE = "\033[94m";
};

template<typename StreamType>
class BaseOutput
{
public:
    explicit BaseOutput(std::shared_ptr<std::mutex> mutex = nullptr) : mutex{std::move(mutex)}
    {
        if(!this->mutex)
            this->mutex = std::make_shared<std::mutex>();
    }
    virtual ~BaseOutput() = default;
    BaseOutput(const BaseOutput&) = default;
    BaseOutput(BaseOutput&&) noexcept = default;
    BaseOutput& operator=(const BaseOutput&) = default;
    BaseOutput& operator=(BaseOutput&&) noexcept = default;

    using Stream = StreamType;
    virtual Stream& stream() = 0;

    template<typename Argument>
    BaseOutput& operator<<(Argument&& argument)
    {
        auto stream_lock = createStreamLock();
        stream() << argument;
        return *this;
    }

    virtual BaseOutput& operator<<(OutputLevel level)
    {
        this->current_level = level;
        return *this;
    }

    class BaseStreamLock
    {
    public:
        BaseStreamLock() = default;
        explicit BaseStreamLock(std::mutex& stream_mutex) : lock{stream_mutex} { }
        virtual ~BaseStreamLock() = default;
        BaseStreamLock(const BaseStreamLock&) = delete;
        BaseStreamLock(BaseStreamLock&&) noexcept = default;
        BaseStreamLock& operator=(const BaseStreamLock&) = delete;
        BaseStreamLock& operator=(BaseStreamLock&&) noexcept = default;

    private:
        std::unique_lock<std::mutex> lock;
    };

protected:
    OutputLevel currentLevel() { return current_level; }
    virtual std::unique_ptr<BaseStreamLock> createStreamLock()
    {
        return std::make_unique<BaseStreamLock>(*this->mutex);
    }

private:
    OutputLevel current_level = OutputLevel::none;
    std::shared_ptr<std::mutex> mutex;
};

using Output = BaseOutput<std::ostream>;
} // namespace flounder

#endif // FLOUNDER_GAME_OUTPUT_H
