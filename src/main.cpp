#include "file_indexer.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>
#include <map>
//#include <algorithm>
//#include <cctype>






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
                    long long minimumSize;

                    std::cout << "Enter minimum file size in bytes: ";
                    std::cin >> minimumSize;

                    if (std::cin.fail() || minimumSize < 0)
                    {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');

                        std::cout << "Invalid input. Please enter a non negative number\n";
                        break;
                    }

                    searchBySize(files, static_cast<std::uintmax_t>(minimumSize));
                    break;
                }

                case 4:
                {
                    showStatistics(files);
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