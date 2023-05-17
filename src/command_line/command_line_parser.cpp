#include "command_line_parser.h"
#include "utils/utils.h"

#include <boost/program_options.hpp>

namespace flounder
{
CommandLineParser::CommandLineParser(std::string program_description,
 CommandLineParser::OptionsDescription general_options,
 std::map<std::string, CommandLineParser::OptionsDescription> subcommands_options,
 std::shared_ptr<OutputManager> output) :
 program_description{std::move(program_description)},
 general_options{std::move(general_options)},
 subcommands_options{std::move(subcommands_options)}, output{std::move(output)}
{
    if(!this->output)
        this->output = std::make_shared<OutputManager>();
}

CommandLineOptions CommandLineParser::parse(int argc, const char* const argv[])
{
    return parse({argv, argv + argc});
}

CommandLineOptions CommandLineParser::parse(std::vector<std::string> args)
{
    if(args.empty())
        throw std::runtime_error(
         "Arguments can't be empty (at least the program invocation name is required)!");

    auto program_invocation_name = args.front();
    args.erase(args.begin());

    CommandLineOptions parse_result{program_invocation_name, output};

    auto general_parse_result = parseGeneralArguments(args);
    boost::program_options::notify(general_parse_result.generalArguments);

    if(hasSubcommand())
    {
        auto subcommand_parse_result = parseSubcommandArguments(general_parse_result);
        boost::program_options::notify(subcommand_parse_result.subcommandArguments);

        parse_result.setOptions(general_parse_result.generalArguments,
         subcommand_parse_result.subcommand, subcommand_parse_result.subcommandArguments);
    }
    else
    {
        parse_result.setOptions(general_parse_result.generalArguments);
    }
    return parse_result;
}

// return value are the unprocessed args;
// these will contain the subcommand with its options and any unrecognized general option
CommandLineParser::GeneralParseResult CommandLineParser::parseGeneralArguments(
 const std::vector<std::string>& command_line_arguments)
{
    GeneralParseResult general_parse_result;
    // use the first positional argument as subcommand and all following as its options
    boost::program_options::positional_options_description subcommand_with_unparsed_options;
    // create copy and add subcommand if necessary to hide these internal options in help text
    auto general_options_with_subcommand = general_options;
    if(hasSubcommand())
    {
        general_options_with_subcommand.add_options()("subcommand",
         boost::program_options::value<std::string>(),
         "Subcommand to execute")("subcommand_options",
         boost::program_options::value<std::vector<std::string>>(), "Options for subcommand");

        subcommand_with_unparsed_options.add("subcommand", 1).add("subcommand_options", -1);
    }
    // parse general options and subcommand
    try
    {
        auto parser = boost::program_options::command_line_parser(command_line_arguments)
                       .options(general_options_with_subcommand)
                       .positional(subcommand_with_unparsed_options);
        if(hasSubcommand())
        {
            parser.allow_unregistered();
        }
        auto parsed = parser.run();

        boost::program_options::store(parsed, general_parse_result.generalArguments);

        // collect unrecognized options for subcommand option parsing;
        // this will include the subcommand and any invalid general option
        general_parse_result.unprocessedArguments = boost::program_options::collect_unrecognized(
         parsed.options, boost::program_options::include_positional);
    }
    catch(const boost::program_options::error& exception)
    {
        *this->output << OutputLevel::error
                      << "Error while parsing general options: " << exception.what() << '\n';
        helpAndQuit(ExitCode::invalidArguments);
    }

    return general_parse_result;
}

// use subcommands_options to parse the corresponding options of the given subcommand
CommandLineParser::SubcommandParseResult CommandLineParser::parseSubcommandArguments(
 const CommandLineParser::GeneralParseResult& general_parse_result)
{
    CommandLineParser::SubcommandParseResult subcommand_parse_result;
    subcommand_parse_result.subcommand = retrieveSubcommand(general_parse_result);
    try
    {
        auto parsed = boost::program_options::command_line_parser(
         general_parse_result.unprocessedArguments)
                       .options(subcommands_options.at(subcommand_parse_result.subcommand))
                       .run();

        boost::program_options::store(parsed, subcommand_parse_result.subcommandArguments);
    }
    catch(const boost::program_options::error& exception)
    {
        *this->output << OutputLevel::error
                      << "Error while parsing subcommand options: " << exception.what() << '\n';
        helpAndQuit(ExitCode::invalidArguments);
    }
    catch(const std::out_of_range& exception)
    {
        // in case subcommand can not be found
    }
    return subcommand_parse_result;
}

std::string CommandLineParser::retrieveSubcommand(
 const CommandLineParser::GeneralParseResult& general_parse_result)
{
    std::string subcommand;
    try
    {
        auto subcommand_entry = general_parse_result.generalArguments["subcommand"];
        if(!subcommand_entry.empty())
        {
            subcommand = subcommand_entry.as<std::string>();
            if(subcommands_options.find(subcommand) == subcommands_options.end())
            {
                throw std::runtime_error("Unknown subcommand: " + subcommand);
            }
        }
    }
    catch(const boost::bad_any_cast& exception)
    {
        *this->output << "Error while parsing subcommand: " << exception.what() << '\n';
        utils::quit(ExitCode::invalidArguments);
    }
    catch(const std::exception& exception)
    {
        *this->output << OutputLevel::error << exception.what() << '\n';
        utils::quit(ExitCode::invalidArguments);
    }
    return subcommand;
}

[[noreturn]] void CommandLineParser::helpAndQuit(ExitCode exit_code) const
{
    printHelp();
    utils::quit(exit_code);
}

void CommandLineParser::printHelp() const
{
    if(!program_description.empty())
    {
        *this->output << OutputLevel::user << program_description << '\n';
    }
    if(hasSubcommand())
    {
        *this->output << OutputLevel::user
                      << "Usage: program [general_options] [subcommand] [subcommand_options]\n\n";
    }
    else
    {
        *this->output << OutputLevel::user << "Usage: program [options]\n\n";
    }

    *this->output << general_options << '\n';

    for(const auto& subcommand_options : subcommands_options)
    {
        *this->output << OutputLevel::user << subcommand_options.second << '\n';
    }
}
} // namespace flounder
