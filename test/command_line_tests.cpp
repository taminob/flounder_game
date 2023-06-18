#include "command_line/command_line_parser.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <thread>

class CommandLineParserTest : public testing::Test
{
protected:
    void SetUp() override
    {
        try
        {
        }
        catch(const std::exception& exception)
        {
            FAIL() << "Failed to execute SetUp: " << exception.what();
        }
    }

    void TearDown() override { }

protected:
    static constexpr std::string_view TEST_INVOCATION_NAME = "invocation_name";
    static flounder::CommandLineParser::OptionsDescription testOptionsDescription()
    {
        flounder::CommandLineParser::OptionsDescription options;
        options.add_options()("abc,a", "ABC");
        return options;
    }
};

TEST_F(CommandLineParserTest, emptyOptionsAndArguments)
{
    flounder::CommandLineParser test_parser(
     "", flounder::CommandLineParser::OptionsDescription(), {}, nullptr);
    EXPECT_THROW(test_parser.parse({}), std::runtime_error);
}

TEST_F(CommandLineParserTest, onlyInvocationName)
{
    flounder::CommandLineParser test_parser(
     "", flounder::CommandLineParser::OptionsDescription(), {}, nullptr);
    EXPECT_NO_THROW(test_parser.parse({std::string{TEST_INVOCATION_NAME}}));
}

TEST_F(CommandLineParserTest, testUnknownArgument)
{
    flounder::CommandLineParser test_parser(
     "", flounder::CommandLineParser::OptionsDescription(), {}, nullptr);
    EXPECT_DEATH(test_parser.parse({"invocation_name", "-x"}), "");
}

TEST_F(CommandLineParserTest, testValidArguments)
{
    auto test_options_description = testOptionsDescription();
    auto test_argument_name = test_options_description.options().front()->long_name();
    flounder::CommandLineParser test_parser(
     "", test_options_description, {}, nullptr);
    EXPECT_NO_THROW(test_parser.parse({"invocation_name", "--abc"}));
}
