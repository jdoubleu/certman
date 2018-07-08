# Download and unpack googletest at configure time
configure_file(${PROJECT_SOURCE_DIR}/cmake/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

function(add_unit_tests)
    file(GLOB_RECURSE CERTMAN_UNIT_TESTS "${PROJECT_SOURCE_DIR}/tests/unit/*.cpp")

    set(CERTMAN_TEST_FIXTURES ${PROJECT_SOURCE_DIR}/tests/fixtures)
    add_definitions(-DCERTMAN_TEST_FIXTURES=${CERTMAN_TEST_FIXTURES})

    add_executable(${PROJECT_NAME}_tests_unit ${CERTMAN_UNIT_TESTS})
    target_link_libraries(${PROJECT_NAME}_tests_unit gtest_main ${PROJECT_NAME}_main)

    add_test(NAME unit_tests COMMAND ${PROJECT_NAME}_tests_unit)
endfunction()
