#ifndef FLOUNDER_GAME_COMMAND_LINE_PARSER_H
#define FLOUNDER_GAME_COMMAND_LINE_PARSER_H

#include "command_line_options.h"
#include "output/output_manager.h"
#include "utils/constants.h"

#include <map>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace flounder
{
class CommandLineParser
{
public:
    using OptionsDescription = boost::program_options::options_description;
    using ArgumentsMap = boost::program_options::variables_map;

public:
    CommandLineParser(std::string program_description, OptionsDescription general_options,
     std::map<std::string, OptionsDescription> subcommands_options,
     std::shared_ptr<OutputManager> output = nullptr);

    CommandLineOptions parse(int argc, const char* const argv[]);
    CommandLineOptions parse(std::vector<std::string> args);

protected:
    [[nodiscard]] bool hasSubcommand() const { return !subcommands_options.empty(); }

    struct GeneralParseResult
    {
        /// Includes the general arguments and a key for the subcommand
        ArgumentsMap generalArguments;
        /// Includes all arguments that were not a general argument or a subcommand
        std::vector<std::string> unprocessedArguments;
    };
    struct SubcommandParseResult
    {
        std::string subcommand;
        ArgumentsMap subcommandArguments;
    };
    GeneralParseResult parseGeneralArguments(
     const std::vector<std::string>& all_command_line_arguments);
    SubcommandParseResult parseSubcommandArguments(const GeneralParseResult& general_parse_result);
    /// Retrieve subcommand from given parse result
    ///
    /// @return The valid subcommand or an empty string if no subcommand was found
    ///
    /// @throw If subcommand is invalid
    std::string retrieveSubcommand(const GeneralParseResult& general_parse_result);

    void printHelp() const;
    [[noreturn]] void helpAndQuit(ExitCode exit_code) const;

private:
    std::string program_description;
    OptionsDescription general_options;
    std::map<std::string, OptionsDescription> subcommands_options;

    std::shared_ptr<OutputManager> output;
};
} // namespace flounder

#endif // FLOUNDER_GAME_COMMAND_LINE_PARSER_H
