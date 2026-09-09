cmake_minimum_required(VERSION 3.20)

project(Fileindexer
	VERSION 1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fileindex
    src/main.cpp
    src/file_indexer.cpp
)

target_include_directories(fileindex PRIVATE include)

include(FetchContent)

FetchContent_Declare(
	googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
	DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(fileindex_tests
	tests/file_indexer_tests.cpp
	src/file_indexer.cpp
)

target_include_directories(fileindex_tests PRIVATE include)

target_link_libraries(fileindex_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(
	fileindex_tests
	CONFIGURATIONS Release
)
