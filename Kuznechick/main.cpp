// Kuznechick.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Kuznechik.h"
#include <iostream>

int main()
{
	Kuznechik kz;
	const int data_size = 25;
	byte data[data_size];
	for (int i = 0; i < data_size; i++)
	{
		data[i] = i;
	}
	kz.Encrypt(data, data_size);
    return 0;
}

