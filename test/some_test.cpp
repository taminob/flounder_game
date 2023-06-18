#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <thread>

class SomeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        try
        {
            // do something
        }
        catch(const std::exception& exception)
        {
            FAIL() << "Failed to execute Setup: " << exception.what();
        }
    }

    void TearDown() override { }
};

TEST_F(SomeTest, testSomehing)
{
    EXPECT_TRUE(true);
}
