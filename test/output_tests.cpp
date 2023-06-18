#include "random_helper.h"

#include "output/output.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <thread>

class OutputTest : public testing::Test
{
public:
    struct StreamStub
    {
        template<typename T>
        StreamStub& operator<<(T&& value)
        {
            capturedOutput.push_back(value);
            return *this;
        }

        std::vector<std::any> capturedOutput;
    };

    struct TestOutput : public flounder::BaseOutput<StreamStub>
    {
        Stream& stream() override { return streamStub; }
        StreamStub streamStub;
    };

protected:
    void SetUp() override
    {
        try
        {
            // do something
        }
        catch(const std::exception& exception)
        {
            FAIL() << "Failed to execute SetUp: " << exception.what();
        }
    }

    void TearDown() override { }

protected:
    TestOutput output;
};

template<typename T>
class TypedOutputTest : public OutputTest
{
};

using SingleValueTestTypes = testing::Types<std::string, int, double, char, bool>;
TYPED_TEST_SUITE(TypedOutputTest, SingleValueTestTypes);
TYPED_TEST(TypedOutputTest, singleValueOutput)
{
    TypeParam test_input{};
    test_input = randomValue<TypeParam>();
    this->output << test_input;

    EXPECT_EQ(this->output.streamStub.capturedOutput.size(), 1);
    TypeParam test_output;
    EXPECT_NO_THROW(
     { test_output = std::any_cast<TypeParam>(this->output.streamStub.capturedOutput.at(0)); });
    EXPECT_EQ(test_output, test_input);
}

TYPED_TEST(TypedOutputTest, multiValueOutput)
{
    const auto test_inputs = randomValues<TypeParam, 5>();
    this->output << test_inputs.at(0) << test_inputs.at(1) << test_inputs.at(2) << test_inputs.at(3)
                 << test_inputs.at(4);
    EXPECT_EQ(this->output.streamStub.capturedOutput.size(), 5);
}

TEST_F(OutputTest, mixedValueOutput)
{
    const auto test_input_one = randomValue<int>();
    const auto test_input_two = randomValue<std::string>();
    const auto test_input_three = randomValue<bool>();
    this->output << test_input_one << test_input_two << test_input_three;
    EXPECT_NO_THROW({
        auto test_output = std::any_cast<decltype(test_input_one)>(
         this->output.streamStub.capturedOutput.at(0));
        EXPECT_EQ(test_output, test_input_one);
    });
    EXPECT_NO_THROW({
        auto test_output = std::any_cast<decltype(test_input_two)>(
         this->output.streamStub.capturedOutput.at(1));
        EXPECT_EQ(test_output, test_input_two);
    });
    EXPECT_NO_THROW({
        auto test_output = std::any_cast<decltype(test_input_three)>(
         this->output.streamStub.capturedOutput.at(2));
        EXPECT_EQ(test_output, test_input_three);
    });
}
