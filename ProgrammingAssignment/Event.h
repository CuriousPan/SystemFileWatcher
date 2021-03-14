#ifndef EVENT_H
#define EVENT_H
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

enum class EventType
{
	CREATED, DELETED, EDITED, RENAMED
};

enum class FileType
{
	FILE, DIRECTORY
};

class Event
{
	const EventType eventType;
	const FileType fileType;
	const fs::path pathToFile;
	const std::string eventTime;
public:
	Event(EventType eventType, FileType fileType, fs::path pathToFile, std::string eventTime);
	~Event();
	Event(Event& event);
	//void printEvent();
	friend std::ostream& operator<<(std::ostream& os, const Event& event);
};

#endif