#include <iostream>
#include <filesystem>

int main(int argc, char* argv[])
{
    std::cout << "File Indexer starting...\n";

    for (int i = 0; i < argc; i++)
    {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    std::filesystem::path directoryPath = argv[1];
    std::filesystem::directory_iterator iterator = directoryPath;

    if (std::filesystem::exists(directoryPath))
    {
        std::cout << "Directory exists." << std::endl;
    }
    else 
    {
        std::cout << "Error! Directory not found." << std::endl;
    }

    return 0;
}