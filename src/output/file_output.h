#ifndef FLOUNDER_GAME_FILE_OUTPUT_H
#define FLOUNDER_GAME_FILE_OUTPUT_H

#include "output.h"

#include <fstream>

namespace flounder
{
class FileOutput : public Output
{
public:
    explicit FileOutput(const std::string& file_name, bool append = false) :
     file_stream{file_name, (append) ? std::ios_base::app : std::ios_base::out}
    {
    }
    std::ostream& stream() override { return file_stream; }

private:
    std::ofstream file_stream;
};

} // namespace flounder

#endif // FLOUNDER_GAME_FILE_OUTPUT_H
