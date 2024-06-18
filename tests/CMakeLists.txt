cmake_minimum_required(VERSION 3.28)
project(tests C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)


include_directories(${LIB_DIR}/criterion-2.4.2/include)
link_directories(${LIB_DIR}/criterion-2.4.2/lib)

# For each of your test source files
set(TEST_SOURCES utils_test.c)

add_custom_target(tests)

foreach(test_src ${TEST_SOURCES})
    # Get the file name without an extension
    get_filename_component(test_name ${test_src} NAME_WE)

    # Add executable for this test source
    add_executable(${test_name} ${test_src})

    # Link the test executable with the Criterion library
    target_link_libraries(${test_name} ${GLIB_LIBRARIES} criterion opengl-poc-lib)

    # Register the test with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})

    add_dependencies(tests ${test_name})
endforeach()

add_custom_command(TARGET tests POST_BUILD COMMAND ctest -C $<CONFIGURATION> --output-on-failure)
