#include <iostream>
#include <filesystem>

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

        std::filesystem::directory_iterator iterator(directoryPath);

        for (const auto& entry : iterator)
        {
            if (entry.is_directory())
            {
                std::cout << "Directory: " << entry.path() << std::endl;
                
            }
            else 
            {
                std::cout << "File: " << entry.path() << std::endl;
            }
        }
    }

    return 0;
}