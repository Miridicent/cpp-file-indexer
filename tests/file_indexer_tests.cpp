//file_indexer_tests.cpp

#include "file_indexer.h"
#include <gtest/gtest.h>

TEST(toLowerTest, ConvertsUppercaseToLowercase)
{
    EXPECT_EQ(toLower("HELLO"), "hello");
}

TEST(searchByExtensionTest, FindsMatchingExtension)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100},
        FileInfo{std::filesystem::path("readme.md"), "readme.md", ".md", 200},
        FileInfo{std::filesystem::path("main.cpp"), "main.cpp", ".cpp", 300}
    };

    // This test checks that the functions can be called.
    searchByExtension(files, ".cpp");
}