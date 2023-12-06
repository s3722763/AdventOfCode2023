cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_policy(SET CMP0135 NEW)

project(AdventOfCode2023)

add_library(${PROJECT_NAME}_LIB STATIC)

target_sources(${PROJECT_NAME}_LIB
    PUBLIC
        FILE_SET CXX_MODULES
            BASE_DIRS
                "${CMAKE_CURRENT_SORUCE_DIR}"
            FILES
                "src/day1.cpp"
                "src/day2.cpp"
                "src/day3.cpp"
                "src/day4.cpp")

target_compile_features(${PROJECT_NAME}_LIB PUBLIC cxx_std_20)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE "src/main.cpp")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_LIB)

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/input ${CMAKE_CURRENT_BINARY_DIR}/input
)
add_dependencies(${PROJECT_NAME} copy_assets)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_TEST)
target_sources(${PROJECT_NAME}_TEST
   PRIVATE
        test/test_day1.cpp
        test/test_day2.cpp
        test/test_day3.cpp
        test/test_day4.cpp)

target_link_libraries(${PROJECT_NAME}_TEST
    PRIVATE
        gtest_main gmock
        ${PROJECT_NAME}_LIB)

enable_testing()
add_test(AllTests ${PROJECT_NAME}_TEST)