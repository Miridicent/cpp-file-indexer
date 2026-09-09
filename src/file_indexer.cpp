//file_indexer.cpp

#include "file_indexer.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>

std::string toLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
                    [](unsigned char c)
                    {
                        return std::tolower(c);
                    });
    return text;
}

std::vector<FileInfo> searchByExtension(const std::vector<FileInfo>& files, const std::string& extension)
{

    std::vector<FileInfo> results;

    for (const auto& file : files)
    {
        if (toLower(file.extension) == toLower(extension))
        {
            results.push_back(file);
        }
    }

    return results;
}

std::vector<FileInfo> searchByFilename(const std::vector<FileInfo>& files, const std::string& filename)
{
    std::vector<FileInfo> results;

    for (const auto& file : files)
    {
        if (toLower(file.filename) == toLower(filename))
        {
            results.push_back(file);
        }
    }

    return results;
}

std::vector<FileInfo> searchBySize(const std::vector<FileInfo>& files, std::uintmax_t minimumSize)
{
    std::vector<FileInfo> results;

    for (const auto& file : files)
    {
        if (file.size >= minimumSize)
        {
            results.push_back(file);
        }
    }

    return results;
}

Statistics calculateStatistics(const std::vector<FileInfo>& files)
{
    Statistics statistics{};

    for (const auto& file : files)
    {
        statistics.totalSize += file.size;
    }

    if (!files.empty())
    {
        statistics.averageSize = static_cast<double>(statistics.totalSize) / files.size();

        statistics.largestFileSize = files[0].size;
        statistics.largestFilePath = files[0].path;

        statistics.smallestFileSize = files[0].size;
        statistics.smallestFilePath = files[0].path;
    }


    for (const auto& file : files)
    {
        if (file.size > statistics.largestFileSize)
        {
            statistics.largestFileSize = file.size;
            statistics.largestFilePath = file.path;
        }

        if (file.size < statistics.smallestFileSize)
        {
            statistics.smallestFileSize = file.size;
            statistics.smallestFilePath = file.path;
        }

        statistics.extensionCounts[file.extension]++;
    }

    return statistics;

}

std::vector<FileInfo> indexDirectory(const std::filesystem::path& directoryPath)
{
    std::vector<FileInfo> files;

    std::error_code error;

    std::filesystem::recursive_directory_iterator iterator(directoryPath, std::filesystem::directory_options::skip_permission_denied, error);

    if (error)
    {
        std::cout << "Error accessing directory: " << error.message() << std::endl;
        return files;
    }

    for (const auto& entry : iterator)
        {
            std::error_code entryError;
            bool isDirectory = entry.is_directory(entryError);

            if (entryError)
            {
                std::cout << "Could not access: "
                          << entry.path() << " - "
                          << entryError.message() << std::endl;
                continue;
            }
            
            if (isDirectory && (entry.path().filename() == ".git" || entry.path().filename() == "build"))
            {
                iterator.disable_recursion_pending();
                std::cout << "Directory: " << entry.path() << std::endl;
                    
            }

            else if (isDirectory)
            {
                std::cout << "Directory: " << entry.path() << std::endl;
            }

            else 
            {
                FileInfo file;

                file.path = entry.path();
                file.filename = entry.path().filename().string();
                file.extension = entry.path().extension().string();

                std::error_code sizeError;
                file.size = entry.file_size(sizeError);

                if (sizeError)
                {
                    std::cout << "Could not read file size: " 
                              << entry.path() << " - "
                              << sizeError.message() << std::endl;
                    continue;
                }

                files.push_back(file);

                std::cout << "File: " << entry.path() << std::endl;
                std::cout << "Size: " << file.size << " bytes" << std::endl;
                std::cout << "Extension: " << file.extension << std::endl;
            }
            
        }

        return files;
}