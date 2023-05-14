#ifndef FLOUNDER_GAME_OUTPUT_MANAGER_H
#define FLOUNDER_GAME_OUTPUT_MANAGER_H

#include "output.h"
#include "output_levels.h"

#include <vector>

namespace flounder
{
class OutputManager
{
    std::vector<std::pair<std::unique_ptr<Output>, OutputLevels>> outputs;

public:
    OutputManager() = default;
    void addOutput(
     std::unique_ptr<Output> output, OutputLevels levels = OutputLevels{OutputLevel::all})
    {
        outputs.push_back({std::move(output), levels});
    }

    template<typename... Args>
    void user(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::user);
    }
    template<typename... Args>
    void fatal(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::fatal);
    }
    template<typename... Args>
    void error(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::error);
    }
    template<typename... Args>
    void warning(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::warning);
    }
    template<typename... Args>
    void notice(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::notice);
    }
    template<typename... Args>
    void info(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::info);
    }
    template<typename... Args>
    void debug(const std::string& format_string, Args&&... args)
    {
        output(format(format_string, std::forward<Args...>(args...)), OutputLevel::debug);
    }

    template<typename Argument>
    OutputManager& operator<<(Argument&& argument)
    {
        output(argument, current_level);
        return *this;
    }

    OutputManager& operator<<(OutputLevel level)
    {
        this->current_level = level;

        forEachOutput([level](Output& output, OutputLevels /*level_filter*/) { output << level; });
        return *this;
    }

protected:
    template<typename... Args>
    std::string format(const std::string& format_string, Args&&... args)
    {
        return fmt::vformat(format_string, fmt::basic_format_args(std::forward<Args...>(args...)));
    }

    template<typename Argument>
    void output(Argument&& argument, OutputLevel level)
    {
        forEachOutput(
         [level, &argument](Output& output, OutputLevels level_filter)
         {
             if(level_filter.hasLevel(level))
                 output << argument;
         });
    }

    template<typename Func>
    void forEachOutput(Func&& function)
    {
        for(const auto& [output, level_filter] : outputs)
        {
            function(*output, level_filter);
        }
    }

private:
    OutputLevel current_level = OutputLevel::none;
};
} // namespace flounder

#endif // FLOUNDER_GAME_OUTPUT_MANAGER_H
