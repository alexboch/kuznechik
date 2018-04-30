// Kuznechick.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Kuznechik.h"
#include "FileHelper.h"
#include <iostream>
#include <random>
#include <string>
#include <sstream>
using namespace kuz;

key_t GenerateMasterKey()
{
	//Инициализация генератора случайных чисел
	int max_val = pow(2, 8) - 1;//случайный байт
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, max_val);
	key_t master_key;
	for (int i = 0; i < master_key.size(); i++)
	{
		master_key[i] = dis(gen);
	}
	return master_key;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}

int main(int argc,char** argv)
{
	key_t master_key=GenerateMasterKey();
	Kuznechik kz(master_key);
	while (true)
	{
		cout << ">";
		string command;
		getline(cin,command);
		vector<string> input = split(command, ' ');
		
		string cmd = input[0];
		if (cmd == "quit")
		{
			exit(0);
		}
		else
		{
			if (input.size() == 3)
			{
				string input_file_path = input[1];
				string output_file_path = input[2];
				vector<char> v = FileHelper::ReadAllBytes(input_file_path.c_str());
				int data_size = v.size();
				char* chars=&v[0];
				byte* file_data = reinterpret_cast<unsigned char*>(chars);
				char* write_data = nullptr;

				if (input[0] == "enc")//encrypt
				{
					vector<byte> enc_bytes=kz.Encrypt(file_data, data_size);
					byte* byte_arr = &enc_bytes[0];
					write_data = reinterpret_cast<char*> (byte_arr);
					FileHelper::WriteBytes(output_file_path.c_str(), write_data, enc_bytes.size());
				}
				else if (input[0] == "dec")//decrypt
				{
					vector<byte> data_vec(file_data, file_data + data_size);
					byte* output_data = kz.Decrypt(data_vec, data_size);
					write_data = reinterpret_cast<char*>(output_data);
					FileHelper::WriteBytes(output_file_path.c_str(), write_data, data_size);
				}
				
			}
		}
	}

	//char* data = "A short test message A short test message A short test message";
	//int data_size = strlen(data);
	//byte* byte_data = new byte[data_size];
	//for (int i = 0; i < data_size; i++)
	//{
	//	byte_data[i] = (byte)data[i];
	//}
	//block_t block_1;
	////block_1.fill(200);
	//for (int i = 0; i < block_1.size(); i++)
	//{
	//	block_1[i] = i;
	//}
	//block_t rb = kz.R(block_1);
	//block_t rb2 = kz.R_inv(rb);
	//block_t lb=kz.L(block_1);
	//block_t lb2 = kz.L_inv(lb);
	//block_t s1 = kz.S(block_1);
	//block_t s2 = kz.S_inv(s1);
	//vector<byte> enc_vec = kz.Encrypt(byte_data, data_size);
	//
	//byte* dec_data = kz.Decrypt(enc_vec, data_size);




	////delete[] enc_data;
	////delete[] dec_data;
 //   
	// vector<char> v=FileHelper::ReadAllBytes("ReadMe.txt");
	//  char* chars=&v[0];
	//  byte* file_data = reinterpret_cast<unsigned char*>(chars);
	// /*byte* file_data = new byte[v.size()];
	// for (int i = 0; i < v.size(); i++)
	// {
	//	 file_data[i] = v[i];
	// }*/

	// vector<byte> enc_data_file = kz.Encrypt(file_data, v.size());
	// enc_data_file[120] = 0;
	// char* enc_write_data = reinterpret_cast<char*> (&enc_data_file[0]);
	// FileHelper::WriteBytes("Encrypted.txt", enc_write_data, v.size());
	// byte* dec_data_file = kz.Decrypt(enc_data_file, v.size());
	// char* write_data = reinterpret_cast<char*>(dec_data_file);
	// FileHelper::WriteBytes("Decrypted.txt", write_data, v.size());
	return 0;
}

