add_library(${LIBRARY_NAME} command_line/command_line_options.cpp
                            command_line/command_line_parser.cpp)
target_link_libraries(${LIBRARY_NAME} fmt::fmt Boost::program_options Threads::Threads)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE Threads::Threads ${LIBRARY_NAME})
