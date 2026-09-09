//file_indexer.h

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>
#include <map>

struct FileInfo
{
    std::filesystem::path path;
    std::string filename;
    std::string extension;
    std::uintmax_t size;
};

struct Statistics
{
    std::uintmax_t totalSize;
    double averageSize;
    std::uintmax_t largestFileSize;
    std::filesystem::path largestFilePath;
    std::uintmax_t smallestFileSize;
    std::filesystem::path smallestFilePath;
    std::map<std::string, int> extensionCounts;
};

std::string toLower(std::string text);

std::vector<FileInfo> searchByExtension(
    const std::vector<FileInfo>& files, 
    const std::string& extension);

std::vector<FileInfo> searchByFilename(
    const std::vector<FileInfo>& files,
    const std::string& filename
);

std::vector<FileInfo> searchBySize(
    const std::vector<FileInfo>& files,
    std::uintmax_t minimumSize
);

Statistics calculateStatistics(const std::vector<FileInfo>& files);

std::vector<FileInfo> indexDirectory(
    const std::filesystem::path& directoryPath

);