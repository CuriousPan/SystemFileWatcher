#pragma warning(disable : 4996)
#include "FileWatcher.h"
#include "Event.h"
#include <iostream>

std::string FileWatcher::currentTime()
{
	auto now = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
	std::string currentSystemTime = std::ctime(&nowTime);
	return currentSystemTime;
}

FileWatcher::FileWatcher(fs::path pathToWatch, std::string logsFilePath)
{
	this->pathToWatch = pathToWatch;
	this->logsFilePath = logsFilePath;
	logsFile.open(logsFilePath, std::ios::app);
	//create a map with last modification of a given file in the directory
	for (auto& file : fs::directory_iterator(this->pathToWatch))
	{
		pathsMap.emplace(file.path(), fs::last_write_time(file));
	}
	
}

FileWatcher::~FileWatcher()
{
	logsFile.close();
}

void FileWatcher::start()
{
	std::cout << "Proccess started" << std::endl;

	while (true)
	{
		try {
			currentNumberOfFiles = std::distance(fs::directory_iterator(pathToWatch), fs::directory_iterator());

			auto it = pathsMap.begin();
			while (it != pathsMap.end())
			{
				if (!fs::exists(it->first.string()))
				{
					if (currentNumberOfFiles < pathsMap.size())
					{
						//file deleted
						FileType fileType = (fs::is_regular_file(it->first) ? FileType::FILE : FileType::DIRECTORY);
						Event event(EventType::DELETED, fileType, it->first, currentTime());
						std::cout << event << std::endl;
						logsFile << event << "\n";
						it = pathsMap.erase(it);
						break;
					}
					else
					{

						//file is renamed
						FileType fileType = (fs::is_regular_file(it->first) ? FileType::FILE : FileType::DIRECTORY);
						Event event(EventType::RENAMED, fileType, it->first, currentTime());
						std::cout << event << std::endl;
						logsFile << event << "\n";
						it = pathsMap.erase(it);
						break;
					}
				}
				else
				{
					it++;
				}
			}

			for (auto& file : fs::directory_iterator(pathToWatch))
			{
				if (pathsMap.count(file.path()) == 0)
				{

					//file is create
					pathsMap.emplace(file.path(), fs::last_write_time(file));
					FileType fileType = (fs::is_regular_file(file) ? FileType::FILE : FileType::DIRECTORY);
					Event event(EventType::CREATED, fileType, file.path(), currentTime());
					std::cout << event << std::endl;
					logsFile << event << "\n";
					break;
				}
				else
				{
					if (pathsMap[file.path()] != fs::last_write_time(file))
					{

						//file is modified
						pathsMap[file.path()] = fs::last_write_time(file.path());
						FileType fileType = (fs::is_regular_file(file.path()) ? FileType::FILE : FileType::DIRECTORY);
						Event event(EventType::EDITED, fileType, file.path(), currentTime());
						std::cout << event << std::endl;
						logsFile << event << "\n";
						break;
					}
				}
			}
		}
		catch (fs::filesystem_error)
		{
			std::cout << "Error cought" << std::endl;
		}
	}
}