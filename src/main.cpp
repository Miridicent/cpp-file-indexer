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
        std::cout << "Error: Please provide a directory path.";
        return 1;
    }

    std::filesystem::path directoryPath = argv[1];

    if (std::filesystem::exists(directoryPath))
    {
        std::cout << "Directory exists." << std::endl;
    }
    else 
    {
        std::cout << "Error! Directory not found.";
    }

    return 0;
}