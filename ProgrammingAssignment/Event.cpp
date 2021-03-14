#include "Event.h"

Event::Event(EventType eventType, FileType fileType, fs::path pathToFile, std::string eventTime) :
	eventType(eventType), fileType(fileType), pathToFile(pathToFile), eventTime(eventTime)
{
	//ctor

}

Event::~Event()
{
	//dtor
}

Event::Event(Event& event) : eventType(event.eventType), fileType(event.fileType), pathToFile(event.pathToFile), eventTime(event.eventTime)
{
	//cctor
}

std::ostream& operator<<(std::ostream& os, const Event& event)
{
		std::string stringEventType;
		std::string stringFileType;
		switch (event.eventType)
		{
		case EventType::CREATED: stringEventType = "CREATING"; break;
		case EventType::DELETED: stringEventType = "DELETING"; break;
		case EventType::EDITED: stringEventType = "EDITING"; break;
		case EventType::RENAMED: stringEventType = "RENAMING"; break;
		default: stringEventType = "Unknown event typed"; break;
		}
	
		switch (event.fileType)
		{
		case FileType::DIRECTORY: stringFileType = "DIRECTORY"; break;
		case FileType::FILE: stringFileType = "REGULAR FILE"; break;
		default: stringFileType = "UNKNOWN FILETYPE"; break;
		}
	
		return os << event.eventTime << "  " << event.pathToFile << "  " << stringFileType << "  " << stringEventType << "\n";
}