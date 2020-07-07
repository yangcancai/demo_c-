cmake_minimum_required(VERSION 3.16)
project(demo_cmake VERSION 1.0.0)
add_executable(demo_cmake main/Tutorial.cpp)
configure_file(main/TutorialConfig.h.in TutorialConfig.h)
target_include_directories(demo_cmake PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_subdirectory(MathFunctions)
add_subdirectory(common)
target_link_libraries(demo_cmake PUBLIC
        MathFunctions)
install(TARGETS demo_cmake DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
        DESTINATION include)


enable_testing()

# does the application run
add_test(NAME Runs COMMAND demo_cmake 25)

# does the usage message work?
add_test(NAME Usage COMMAND demo_cmake)
set_tests_properties(Usage
        PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
        )

# define a function to simplify adding tests
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg}
            PROPERTIES PASS_REGULAR_EXPRESSION ${result}
            )
endfunction(do_test)

# do a bunch of result based tests
do_test(demo_cmake 4 "4 is 2")
do_test(demo_cmake 9 "9 is 3")
do_test(demo_cmake 5 "5 is 2.236")
do_test(demo_cmake 7 "7 is 2.645")
do_test(demo_cmake 25 "25 is 5")
do_test(demo_cmake -25 "-25 is [-nan|nan|0]")
do_test(demo_cmake 0.0001 "0.0001 is 0.01")