#include <filesystem>
#include "FileWatcher.h"
#include <iostream>

int main()
{   
    //file to write, use your path
    std::string logs = "C:\\Users\\CuriousPan\\Desktop\\logs2.txt";

    fs::path pathToWatch;

    //loop for creating path and checking if it is valid
    while (true)
    {
        std::cout << "Enter a directory: ";
        std::cin >> pathToWatch;
        try
        {
            if (!fs::exists(pathToWatch) || !fs::is_directory(pathToWatch))
            {
                throw fs::filesystem_error("No such directory", std::error_code());
            }
        }
        catch (fs::filesystem_error e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "Try again" << std::endl;
            continue;
        }
        
        std::cout << "Path is valid\n" << std::endl;
        break;
    }

    FileWatcher fileWatcher(pathToWatch, logs);
    fileWatcher.start();
}