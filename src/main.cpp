#include "command_line/command_line_parser.h"
#include "output/cerr_output.h"
#include "output/cout_output.h"
#include "output/file_output.h"
#include "output/output_manager.h"

#include <chrono>
#include <iostream>

std::shared_ptr<flounder::OutputManager> createOutputManager()
{
    auto output = std::make_shared<flounder::OutputManager>();
    auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
    output->addOutput(
     std::make_unique<flounder::FileOutput>(std::to_string(timestamp) + "-flounder_log"));
    output->addOutput(std::make_unique<flounder::CoutOutput>(), flounder::OutputLevel::user);
    output->addOutput(std::make_unique<flounder::CerrOutput>(),
     flounder::OutputLevel::fatal | flounder::OutputLevel::error | flounder::OutputLevel::warning |
      flounder::OutputLevel::notice);
    return output;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    auto output = createOutputManager();

    auto parser = flounder::CommandLineParser("Flounders are fish.",
     flounder::CommandLineOptions::generalOptions(),
     flounder::CommandLineOptions::subcommandsOptions(), output);
    auto command_line_arguments = parser.parse(argc, argv);
}
