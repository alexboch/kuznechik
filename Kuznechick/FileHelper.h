#pragma once
#include<vector>
#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

static class FileHelper
{
public:


	static void WriteBytes(const char* path,char* bytes,int num_bytes)
	{
		ofstream out(path, ios::out | ios::binary);
		if (!out)
		{
			throw runtime_error("Error opening file stream");
		}
		out.write(bytes, num_bytes);
		out.flush();
		out.close();
	}

	static std::vector<char> ReadAllBytes(const char* path)
	{
		ifstream ifs(path, ios::binary | ios::ate);
		if (!ifs)
		{
			throw runtime_error("Unable to open file!");
		}
		ifstream::pos_type pos = ifs.tellg();
		
		std::vector<char>  result(pos);

		ifs.seekg(0, ios::beg);
		ifs.read(&result[0], pos);
		ifs.close();
		return result;
	}
};

