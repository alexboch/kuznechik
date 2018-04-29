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
	const int data_size = 25;
	byte data[data_size];
	for (int i = 0; i < data_size; i++)
	{
		data[i] = i;
	}
	kz.Encrypt(data, data_size);
    return 0;
}

