#include "file_indexer.h"

#include <iostream>

void showMenu(const std::vector<FileInfo>& files)
{
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

                std::vector<FileInfo> results =
                    searchByExtension(files, searchExtension);

                if (results.empty())
                {
                    std::cout << "No files found with extension: "
                            << searchExtension << std::endl;
                }
                else
                {
                    for (const auto& file : results)
                    {
                        std::cout << file.path << std::endl;
                    }
                }

                break;
            }

            case 2:
            {
                std::string searchFilename;

                std::cout << "Enter a filename to search for: ";
                std::cin >> searchFilename;

                std::vector<FileInfo> results = searchByFilename(files, searchFilename);

                if (results.empty())
                {
                    std::cout << "No files found with filename: "
                            << searchFilename << std::endl;
                }
                else 
                {
                    for (const auto& file : results)
                    {
                        std::cout << file.path << std::endl;
                    }
                }
                break;
            }

            case 3:
            {
                long long minimumSize;

                std::cout << "Enter minimum file size in bytes: ";
                std::cin >> minimumSize;

                if (std::cin.fail() || minimumSize < 0)
                {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');

                    std::cout << "Invalid input. Please enter a non-negative number\n";
                    break;
                }

                std::vector<FileInfo> results =
                        searchBySize(files, static_cast<std::uintmax_t>(minimumSize));

                if (results.empty())
                {
                    std::cout << "No files found with a size of "
                            << minimumSize << " bytes or larger." << std::endl;
                }
                else
                {
                    for (const auto& file : results)
                    {
                        std::cout << file.path << " - "
                                << file.size << " bytes" << std::endl;
                    }
                }        
                
                break;
            }

            case 4:
            {

                Statistics statistics = calculateStatistics(files);

                std::cout << "\n===== Index Statistics =====\n";
                std::cout << "Total files: " << files.size() << std::endl;
                std::cout << "Total size: " << statistics.totalSize << " bytes" << std::endl;
                std::cout << "Average file size: " << statistics.averageSize << " bytes" << std::endl;
                std::cout << "Largest file: " << statistics.largestFilePath << " (" << statistics.largestFileSize << " bytes)" << std::endl;
                std::cout << "Smallest file: " << statistics.smallestFilePath << " (" << statistics.smallestFileSize << " bytes)" << std::endl;
                
                std::cout << "\nFiles by extension:\n";
                
                for (const auto& entry : statistics.extensionCounts)
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

                break;
            }

            case 5:
            std::cout << "Exiting...\n";
            return;

            default:
                std::cout << "Invalid choice.\n"; 
            

        }
    }
}


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

        std::vector<FileInfo> files = indexDirectory(directoryPath);
        
        std::cout << "\nIndexed " << files.size() << " files.\n";

        showMenu(files);
    }

    return 0;
}