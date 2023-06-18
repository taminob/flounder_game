#ifndef FLOUNDER_GAME_TEST_MOCK_OUTPUT_MANAGER_H
#define FLOUNDER_GAME_TEST_MOCK_OUTPUT_MANAGER_H

#include "output/output.h"
#include "output/output_manager.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class StubStream : public std::ostream
{
public:
    template<typename T>
    T get(std::size_t index)
    {
        return std::any_cast<T>(captured_output.at(index));
    }

private:
    std::vector<std::any> captured_output;
};

class StubOutput : public flounder::Output
{
public:
    using flounder::Output::Output;

    std::ostream& stream() override { return stub_stream; }

private:
    StubStream stub_stream;
};

class StubOutputManager : public flounder::OutputManager
{
public:
};

#endif // FLOUNDER_GAME_TEST_MOCK_OUTPUT_MANAGER_H
