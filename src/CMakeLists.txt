find_package(Boost 1.68.0 REQUIRED COMPONENTS program_options)
find_package(fmt 8.1.0 REQUIRED)

set(TARGET_NAME "flounder_game")

add_executable(${TARGET_NAME} main.cpp command_line/command_line_options.cpp
                              command_line/command_line_parser.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt Boost::program_options)
