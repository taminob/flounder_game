find_package(GTest REQUIRED)

include_directories(../ ../src)

add_executable(tests output_tests.cpp command_line_tests.cpp)

target_link_libraries(tests PRIVATE GTest::GTest GTest::Main gmock fmt::fmt
                                    Boost::program_options Threads::Threads ${LIBRARY_NAME})
