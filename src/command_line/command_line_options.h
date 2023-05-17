#ifndef FLOUNDER_GAME_COMMAND_LINE_OPTIONS_H
#define FLOUNDER_GAME_COMMAND_LINE_OPTIONS_H

#include "output/output_manager.h"

#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace flounder
{
class CommandLineOptions
{
public:
    using OptionsDescription = boost::program_options::options_description;
    using ArgumentsMap = boost::program_options::variables_map;

public:
    explicit CommandLineOptions(std::shared_ptr<OutputManager> output = nullptr);
    explicit CommandLineOptions(
     std::string program_invocation_name, std::shared_ptr<OutputManager> output = nullptr);

    void setOptions(ArgumentsMap new_general_arguments = {}, std::string subcommand = "",
     ArgumentsMap new_subcommand_arguments = {});

    [[nodiscard]] const auto& generalArguments() const { return parsed_general_arguments; }
    [[nodiscard]] const auto& subcommand() const { return parsed_subcommand; }
    [[nodiscard]] const auto& subcommandArguments() const { return parsed_subcommand_arguments; }

    [[nodiscard]] static OptionsDescription generalOptions();
    [[nodiscard]] static std::map<std::string, OptionsDescription> subcommandsOptions();

private:
    std::string program_invocation_name;
    std::string program_description;
    std::vector<std::string> command_line_arguments;

    ArgumentsMap parsed_general_arguments;
    std::string parsed_subcommand;
    ArgumentsMap parsed_subcommand_arguments;

    std::shared_ptr<OutputManager> output;
};
} // namespace flounder

#endif // FLOUNDER_GAME_COMMAND_LINE_OPTIONS_H
