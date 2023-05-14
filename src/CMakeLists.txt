find_package(fmt 8.1.0 REQUIRED)

set(TARGET_NAME "flounder_game")

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt)
