// Kuznechick.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Kuznechik.h"
#include <iostream>
#include <random>
using namespace kuz;

key_t GenerateMasterKey()
{
	//������������� ���������� ��������� �����
	int max_val = pow(2, 8) - 1;//��������� ����
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
	kz.Encrypt(byte_data, data_size);
    return 0;
}

