// Kuznechick.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Kuznechik.h"
#include <iostream>
#include <random>
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

int main()
{
	key_t master_key=GenerateMasterKey();
	Kuznechik kz(master_key);
	
	char* data = "A short test message";
	int data_size = strlen(data);
	byte* byte_data = new byte[data_size];
	for (int i = 0; i < data_size; i++)
	{
		byte_data[i] = (byte)data[i];
	}
	block_t block_1;
	//block_1.fill(200);
	for (int i = 0; i < block_1.size(); i++)
	{
		block_1[i] = i;
	}
	block_t rb = kz.R(block_1);
	block_t rb2 = kz.R_inv(rb);
	block_t lb=kz.L(block_1);
	block_t lb2 = kz.L_inv(lb);
	block_t s1 = kz.S(block_1);
	block_t s2 = kz.S_inv(s1);
	byte* enc_data=kz.Encrypt(byte_data, data_size);
	byte* dec_data = kz.Decrypt(enc_data, data_size);

	delete[] enc_data;
	delete[] dec_data;
    return 0;
}

