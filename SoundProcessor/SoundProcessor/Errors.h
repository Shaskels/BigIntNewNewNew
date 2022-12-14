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
	{11, "Error! Failed to get ByteRate"},
	{12, "Error! Failed to get ByteRate"},
	{13, "Error! Failed to get ByteRate"},
	{14, "Error! Failed to get ByteRate"},
	{15, "Error! Failed to get ByteRate"},
	{16, "Error! Failed to get RIFF"},
	{17,"Error! The file does not start with a RIFF"},
	{18, "Error! Failed to get WAVE"},
	{19,"Error! The file does not have WAVE"},
	{20,"Error! Incorrect argument values"},
	{21,"Error! Configuration file don't open"}
	};
};