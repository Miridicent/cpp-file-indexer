#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <algorithm>
#include <cctype>

struct FileInfo {
    std::filesystem::path path;
    std::string filename;
    std::string extension;
    std::uintmax_t size; 
};

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
        if (file.filename == filename)
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

std::vector<FileInfo> files;

int main(int argc, char* argv[])
{
    std::cout << "File Indexer starting...\n";

    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    if (argc < 2)
    {
        std::cout << "Error: Please provide a directory path." << std::endl;
        return 1;
    }

    std::filesystem::path directoryPath = argv[1];
    
    if (!std::filesystem::exists(directoryPath))
    {
        std::cout << "Error! Directory not found." << std::endl;
    }

    else if (!std::filesystem::is_directory(directoryPath))
    {
        std::cout << "Error! This is not a directory." << std::endl;
    }

    else
    {
        std::cout << "Directory found." << std::endl;

        std::filesystem::recursive_directory_iterator iterator(directoryPath);

        for (const auto& entry : iterator)
        {

            if (entry.is_directory() && (entry.path().filename() == ".git" || entry.path().filename() == "build"))
            {
                iterator.disable_recursion_pending();
                std::cout << "Directory: " << entry.path() << std::endl;
                
            }

            else if (entry.is_directory())
            {
                std::cout << "Directory: " << entry.path() << std::endl;
            }

            else 
            {
                FileInfo file;

                file.path = entry.path();
                file.filename = entry.path().filename().string();
                file.extension = entry.path().extension().string();
                file.size = entry.file_size();

                files.push_back(file);

                std::cout << "File: " << entry.path() << std::endl;
                std::cout << "Size: " << entry.file_size() << " bytes" << std::endl;
                std::cout << "Extension: " << entry.path().extension() << std::endl;
            }
        }

        std::cout << "\nIndexed " << files.size() << " files.\n";

        int choice;

        while (true)
        {
            std::cout << "\nWhat would you like to do?\n";
            std::cout << "1. Search by extension\n";
            std::cout << "2. Search by filename\n";
            std::cout << "3. Search by minimum file size\n";
            std::cout << "4. Show statistics\n";
            std::cout << "5. Exit\n";
            std::cout << "Choice: "; 

            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');

                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (choice)
            {
                case 1:
                {
                    std::string searchExtension;

                    std::cout << "Enter an extension to search for: ";
                    std::cin >> searchExtension;

                    searchByExtension(files, searchExtension);
                    break;
                }

                case 2:
                {
                    std::string searchFilename;

                    std::cout << "Enter a filename to search for: ";
                    std::cin >> searchFilename;

                    searchByFilename(files,searchFilename);
                    break;
                }

                case 3:
                {
                    std::uintmax_t minimumSize;

                    std::cout << "Enter minimum file size in bytes: ";
                    std::cin >> minimumSize;

                    if (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');

                        std::cout << "Invalid input. Please enter a number\n";
                        break;
                    }

                    searchBySize(files, minimumSize);
                    break;
                }

                case 4:
                {
                    showStatistics(files);
                    break;
                }

                case 5:
                    std::cout << "Exiting...\n";
                    return 0;
                

                default:
                    std::cout << "Invalid choice.\n"; 
                

            }
        }
    }

    return 0;
}