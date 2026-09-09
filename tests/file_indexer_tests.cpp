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

    std::vector<FileInfo> results =
        searchByExtension(files, ".cpp");

    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].filename, "test.cpp");
    EXPECT_EQ(results[1].filename, "main.cpp");
}

TEST(searchByExtensionTest, IsCaseInsensitive)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100},
        FileInfo{std::filesystem::path("readme.md"), "readme.md", ".md", 200}
    };

    std::vector<FileInfo> results =
        searchByExtension(files, ".CPP");

    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].filename, "test.cpp");
}

TEST(searchByFilenameTest, FindsMatchingFilename)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100},
        FileInfo{std::filesystem::path("readme.md"), "readme.md", ".md", 200},
        FileInfo{std::filesystem::path("main.cpp"), "main.cpp", ".cpp", 300}
    };

    std::vector <FileInfo> results =
        searchByFilename(files, "MAIN.CPP");
    
        ASSERT_EQ(results.size(), 1);
        EXPECT_EQ(results[0].filename, "main.cpp");
}

TEST(searchByFilenameTest, IsCaseInsensitive)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100},
        FileInfo{std::filesystem::path("README.md"), "README.md", ".md", 200}
    };

    std::vector<FileInfo> results =
        searchByFilename(files, "readme.MD");

    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].filename, "README.md");
}

TEST(searchBySizeTest, FindsFilesAboveMinimumSize)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("small.txt"), "small.txt", ".txt", 100},
        FileInfo{std::filesystem::path("medium.cpp"), "medium.cpp", ".cpp", 500},
        FileInfo{std::filesystem::path("large.cpp"), "large.cpp", ".cpp", 1000}

    };

    std::vector<FileInfo> results =
        searchBySize(files, 500);

    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].filename, "medium.cpp");
    EXPECT_EQ(results[1].filename, "large.cpp");
}

TEST(calculateStatisticsTest, CalculateCorrectStatistics)
{
    std::vector<FileInfo> files = 
    {
        FileInfo{std::filesystem::path("small.txt"), "small.txt", ".txt", 100},
        FileInfo{std::filesystem::path("medium.cpp"), "medium.cpp", ".cpp", 500},
        FileInfo{std::filesystem::path("large.cpp"), "large.cpp", ".cpp", 1000}
    };

    Statistics statistics = calculateStatistics(files);

    EXPECT_EQ(statistics.totalSize, 1600);
    EXPECT_DOUBLE_EQ(statistics.averageSize, 1600.0 / 3);

    EXPECT_EQ(statistics.largestFileSize, 1000);
    EXPECT_EQ(statistics.largestFilePath, std::filesystem::path("large.cpp"));

    EXPECT_EQ(statistics.smallestFileSize, 100);
    EXPECT_EQ(statistics.smallestFilePath, std::filesystem::path("small.txt"));

    EXPECT_EQ(statistics.extensionCounts[".cpp"], 2);
    EXPECT_EQ(statistics.extensionCounts[".txt"], 1);
}

TEST(calculateStatisticsTest, HandlesEmptyFileList)
{
    std::vector<FileInfo> files;

    Statistics statistics = calculateStatistics(files);

    EXPECT_EQ(statistics.totalSize, 0);
    EXPECT_DOUBLE_EQ(statistics.averageSize, 0.0);
    EXPECT_EQ(statistics.largestFileSize, 0);
    EXPECT_EQ(statistics.smallestFileSize, 0);
    EXPECT_TRUE(statistics.largestFilePath.empty());
    EXPECT_TRUE(statistics.smallestFilePath.empty());
    EXPECT_TRUE(statistics.extensionCounts.empty());
}

TEST(searchByExtensionTest, ReturnsEmptyWhenNoMatch)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100},
        FileInfo{std::filesystem::path("readme.md"), "readme.md", ".md", 200}
    };

    std::vector<FileInfo> results =
        searchByExtension(files, ".txt");

    EXPECT_TRUE(results.empty());
}

TEST(searchByFilenameTest, ReturnsEmptyWhenNoMatch)
{
    std::vector<FileInfo> files =
    {
        FileInfo(std::filesystem::path("test.cpp"), "test.cpp", ".cpp", 100),
        FileInfo(std::filesystem::path("readme.md"), "readme.md", ".md", 200)
    };

    std::vector<FileInfo> results = searchByFilename(files, "missing.txt");

    EXPECT_TRUE(results.empty());
}

TEST(searchBySizeTest, ReturnsEmptyWhenNoFileMeetsMinimumSize)
{
    std::vector<FileInfo> files =
    {
        FileInfo{std::filesystem::path("small.txt"), "small.txt", ".txt", 100},
        FileInfo{std::filesystem::path("medium.cpp"), "medium.cpp", ".cpp", 500}
    };

    std::vector<FileInfo> results =
        searchBySize(files, 1000);

    EXPECT_TRUE(results.empty());
}