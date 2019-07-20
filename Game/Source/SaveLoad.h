#pragma once

class SaveLoad
{
public:
	static void SaveToFile(std::string afilename, char* content);
	static std::string LoadFromFile(std::string afilename);
};