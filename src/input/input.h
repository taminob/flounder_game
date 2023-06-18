#ifndef FLOUNDER_GAME_INPUT_H
#define FLOUNDER_GAME_INPUT_H

#include <memory>
#include <mutex>
#include <ostream>

namespace flounder
{
struct InputManipulator
{
    static constexpr const char* RESET = "\033[49m";

    static constexpr const char* NO_ECHO = "TODO";
    static constexpr const char* HEX = "0x";
};

template<typename StreamType, typename LockType>
class BaseInput
{
public:
    BaseInput() = default;
    explicit BaseInput(std::shared_ptr<std::mutex> mutex) : base_mutex{std::move(mutex)}
    {
        if(!mutex)
            mutex = std::make_shared<std::mutex>();
    }
    virtual ~BaseInput() = default;
    BaseInput(const BaseInput&) = default;
    BaseInput(BaseInput&&) noexcept = default;
    BaseInput& operator=(const BaseInput&) = default;
    BaseInput& operator=(BaseInput&&) noexcept = default;
    virtual StreamType& stream() = 0;

    template<typename Argument>
    BaseInput& operator>>(Argument& argument)
    {
        auto stream_lock = createStreamLock();
        stream() >> argument;
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
        std::unique_lock<LockType> lock;
    };

protected:
    virtual std::unique_ptr<BaseStreamLock> createStreamLock()
    {
        return std::make_unique<BaseStreamLock>(*this->base_mutex);
    }

private:
    std::shared_ptr<LockType> base_mutex;
};

using Input = BaseInput<std::ostream, std::mutex>;
} // namespace flounder

#endif // FLOUNDER_GAME_INPUT_H
