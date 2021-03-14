#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include <map>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileWatcher
{
	size_t currentNumberOfFiles = 0;
	fs::path pathToWatch;
	std::string logsFilePath;
	std::ofstream logsFile;
	std::map<fs::path, fs::file_time_type> pathsMap;
	std::string currentTime();
public:
	FileWatcher(fs::path path, std::string logsFilePath);
	~FileWatcher();
	void start();
};

#endif