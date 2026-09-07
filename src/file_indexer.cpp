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

void searchByExtension(const std::vector<FileInfo>& files, const std::string& extension)
{

    bool found = false;

    for (const auto& file : files)
    {
        if (toLower(file.extension) == toLower(extension))
        {
            std::cout << file.path << std::endl;
            found = true;
        }
    }

    if(!found)
    {
        std::cout << "No files found with extension: " << extension << std::endl;
    }
}

void searchByFilename(const std::vector<FileInfo>& files, const std::string& filename)
{

    bool found = false;

    for (const auto& file : files)
    {
        if (toLower(file.filename) == toLower(filename))
        {
            std::cout << file.path << std::endl;
            found = true;
        }
    }

    if(!found)
    {
        std::cout << "No files found with filename: " << filename << std::endl;
    }
}

void searchBySize(const std::vector<FileInfo>& files, std::uintmax_t minimumSize)
{
    bool found = false;

    for (const auto& file : files)
    {
        if (file.size >= minimumSize)
        {
            std::cout << file.path << " - " << file.size << " bytes" << std::endl;
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "no files found with a size of "
                  << minimumSize << " bytes or larger." << std::endl;
    }
}

void showStatistics(const std::vector<FileInfo>& files)
{
    std::uintmax_t totalSize = 0;

    for (const auto& file : files)
    {
        totalSize += file.size;
    }

    std::cout << "\n===== Index Statistics =====\n";
    std::cout << "Total files: " << files.size() << std::endl;
    std::cout << "Total size: " << totalSize << " bytes" << std::endl;

    double averageSize = 0;

    if (!files.empty())
    {
        averageSize = static_cast<double>(totalSize) / files.size();

    }

    std::cout << "Average file size: " << averageSize << " bytes" << std::endl;

    std::uintmax_t largestFileSize = 0;
    std::string largestFilePath;

    for (const auto& file : files)
    {
        if (file.size > largestFileSize)
        {
            largestFileSize = file.size;
            largestFilePath = file.path.string();
        }
    }

    std::cout << "Largest file: " << largestFilePath
              << " (" << largestFileSize << " bytes)" << std::endl;

    std::uintmax_t smallestFileSize = 0;
    std::string smallestFilePath;

    for (const auto& file : files)
    {
        if (smallestFilePath.empty() || file.size < smallestFileSize)
        {
            smallestFileSize = file.size;
            smallestFilePath = file.path.string();
        }
    }

    std::cout << "Smallest file: " << smallestFilePath
          << " (" << smallestFileSize << " bytes)" << std::endl;

    std::map<std::string, int> extensionCounts;

    for (const auto& file : files)
    {
        extensionCounts[file.extension]++;
    }

    std::cout << "\nFiles by extension:\n";

    for (const auto& entry : extensionCounts)
    {
        if (entry.first.empty())
        {
            std::cout << "  [no extension]: " << entry.second << std::endl;
        }
        else
        {
            std::cout << "  " << entry.first << ": " << entry.second << std::endl;
        }
    }
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