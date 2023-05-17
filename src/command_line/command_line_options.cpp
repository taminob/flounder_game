#include "command_line_options.h"

#include <boost/program_options.hpp>

namespace flounder
{
CommandLineOptions::CommandLineOptions(std::shared_ptr<OutputManager> output) :
 CommandLineOptions{"", std::move(output)}
{
}

CommandLineOptions::CommandLineOptions(
 std::string program_invocation_name, std::shared_ptr<OutputManager> output) :
 program_invocation_name{std::move(program_invocation_name)},
 output{std::move(output)}
{
    if(!this->output)
        this->output = std::make_shared<OutputManager>();
}

void CommandLineOptions::setOptions(CommandLineOptions::ArgumentsMap new_general_arguments,
 std::string subcommand, CommandLineOptions::ArgumentsMap new_subcommand_arguments)
{
    this->parsed_general_arguments = std::move(new_general_arguments);
    this->parsed_subcommand = std::move(subcommand);
    this->parsed_subcommand_arguments = std::move(new_subcommand_arguments);
}

[[nodiscard]] CommandLineOptions::OptionsDescription CommandLineOptions::generalOptions()
{
    OptionsDescription general_options("General options");
    general_options.add_options()("version", boost::program_options::bool_switch(), "");
    return general_options;
}

[[nodiscard]] std::map<std::string, CommandLineOptions::OptionsDescription>
 CommandLineOptions::subcommandsOptions()
{
    OptionsDescription info_options("info options");
    info_options.add_options()(
     "verbose,v", boost::program_options::bool_switch(), "Increase verbosity of output");
    return {{"info", info_options}};
}
} // namespace flounder
