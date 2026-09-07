//file_indexer.h

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>

struct FileInfo
{
    std::filesystem::path path;
    std::string filename;
    std::string extension;
    std::uintmax_t size;
};

std::string toLower(std::string text);

void searchByExtension(
    const std::vector<FileInfo>& files, 
    const std::string& extension);

void searchByFilename(
    const std::vector<FileInfo>& files,
    const std::string& filename
);

void searchBySize(
    const std::vector<FileInfo>& files,
    std::uintmax_t minimumSize
);

void showStatistics(const std::vector<FileInfo>& files);

std::vector<FileInfo> indexDirectory(
    const std::filesystem::path& directoryPath

);