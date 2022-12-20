#pragma once
#include <map>
#include <string>

#define ERROR_VALUE 0
#define SUCCESS 1

class Errors {
public:
	std::map <int, std::string> errors = {
	{1, "Error! File could not be opened"},
	{3, "Error! Failed to get ChunkSize"},
	{4, "Error! Failed to get Format"},
	{5, "Error! Failed to get Subchunk1ID"},
	{6, "Error! Failed to get Subchunk1Size"},
	{7, "Error! Failed to get AudioFormat"},
	{8, "Error! Failed to get NumChannels"},
	{9, "Error! Failed to get SampleRate"},
	{10, "Error! Failed to get ByteRate"},
	{11, "Error! Failed to get BlockAlign"},
	{12, "Error! Failed to get BitsPerSample"},
	{13, "Error! Failed to get data"},
	{14, "Error! Failed to get subChunk2Size"},
	{15, "Error! Failed to get samples"},
	{16, "Error! Failed to get RIFF"},
	{17,"Error! The file does not start with a RIFF"},
	{18, "Error! Failed to get WAVE"},
	{19,"Error! The file does not have WAVE"},
	{20,"Error! Incorrect argument values"},
	{21,"Error! The configuration file cannot be opened"},
	{22,"Error! Few configuration file arguments"},
	{23,"Error! There is no such converter" },
	{24,"Error! Unable to save file"},
	{25, "Error! Few command line arguments"},
	{26, "Error! Incorrect command line input format"}
	};
};