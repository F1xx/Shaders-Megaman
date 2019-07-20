#include "GamePCH.h"
#include "SaveLoad.h"
#include <iostream>
#include <fstream>

//Takes in a filename and a char*
//The filename is used to find the file to open
// The char* is emptied into the file.
// No appending, pure overwrite
void SaveLoad::SaveToFile(std::string afilename, char* content)
{
	std::ofstream myfile;
	myfile.open("Data/" + afilename);
	if (myfile.is_open())
	{
		myfile << content;
		myfile.close();
	}
}

//Takes in a filename 
//The filename is used to find the file to open and read from
// Returns the contents of the file as a string
std::string SaveLoad::LoadFromFile(std::string afilename)
{
	std::string str;

	//Load
	//read file into a char*
	std::ifstream myfile;
	myfile.open("Data/" + afilename);
	if (myfile.is_open())
	{
		//load the entire file into a string
		for (int i = 0; !myfile.eof(); i++)
		{
			char letter;
			myfile.get(letter);
			str += letter;
		}
		myfile.close();
		return str;
	}
	else
	{
		return ""; //failed to open file
	}
}
