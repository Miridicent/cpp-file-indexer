#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>

struct FileInfo {
    std::filesystem::path path;
    std::string filename;
    std::string extension;
    std::uintmax_t size; 
};

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

        std::string searchExtension;
        
        std::cout << "Enter an extension to search for: ";
        std::cin >> searchExtension;

        for (const auto& file : files)
        {
            if (file.extension == searchExtension)
            {
                std::cout << file.path << std::endl;
            }
        }
    }

    return 0;
}