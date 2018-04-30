#include "stdafx.h"
#include "Kuznechik.h"

using namespace kuz;


const byte l_vec[16] = {
	148,32,133,16,194,192,1,251,1,192,194,16,133,32,148,1
};

const byte pi[0x100] = {
	0xFC, 0xEE, 0xDD, 0x11, 0xCF, 0x6E, 0x31, 0x16, 	// 00..07
	0xFB, 0xC4, 0xFA, 0xDA, 0x23, 0xC5, 0x04, 0x4D, 	// 08..0F
	0xE9, 0x77, 0xF0, 0xDB, 0x93, 0x2E, 0x99, 0xBA, 	// 10..17
	0x17, 0x36, 0xF1, 0xBB, 0x14, 0xCD, 0x5F, 0xC1, 	// 18..1F
	0xF9, 0x18, 0x65, 0x5A, 0xE2, 0x5C, 0xEF, 0x21, 	// 20..27
	0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F, 	// 28..2F
	0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0, 	// 30..37
	0x06, 0x0B, 0xED, 0x98, 0x7F, 0xD4, 0xD3, 0x1F, 	// 38..3F
	0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB, 	// 40..47
	0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC, 	// 48..4F
	0xB5, 0x70, 0x0E, 0x56, 0x08, 0x0C, 0x76, 0x12, 	// 50..57
	0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87, 	// 58..5F
	0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7, 	// 60..67
	0xF3, 0x91, 0x78, 0x6F, 0x9D, 0x9E, 0xB2, 0xB1, 	// 68..6F
	0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E, 	// 70..77
	0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57, 	// 78..7F
	0xDF, 0xF5, 0x24, 0xA9, 0x3E, 0xA8, 0x43, 0xC9, 	// 80..87
	0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03, 	// 88..8F
	0xE0, 0x0F, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC, 	// 90..97
	0xDC, 0xE8, 0x28, 0x50, 0x4E, 0x33, 0x0A, 0x4A, 	// 98..9F
	0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44, 	// A0..A7
	0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41, 	// A8..AF
	0xAD, 0x45, 0x46, 0x92, 0x27, 0x5E, 0x55, 0x2F, 	// B0..B7
	0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B, 	// B8..BF
	0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7, 	// C0..C7
	0x30, 0x37, 0x6B, 0xE4, 0x88, 0xD9, 0xE7, 0x89, 	// C8..CF
	0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE, 	// D0..D7
	0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61, 	// D8..DF
	0x20, 0x71, 0x67, 0xA4, 0x2D, 0x2B, 0x09, 0x5B, 	// E0..E7
	0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52, 	// E8..EF
	0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0, 	// F0..F7
	0xD1, 0x66, 0xAF, 0xC2, 0x39, 0x4B, 0x63, 0xB6, 	// F8..FF
};

const byte pi_inv[0x100] = {
	0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0, 	// 00..07
	0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91, 	// 08..0F
	0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18, 	// 10..17
	0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F, 	// 18..1F
	0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4, 	// 20..27
	0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7, 	// 28..2F
	0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9, 	// 30..37
	0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5, 	// 38..3F
	0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B, 	// 40..47
	0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F, 	// 48..4F
	0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F, 	// 50..57
	0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E, 	// 58..5F
	0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2, 	// 60..67
	0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B, 	// 68..6F
	0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11, 	// 70..77
	0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C, 	// 78..7F
	0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F, 	// 80..87
	0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36, 	// 88..8F
	0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1, 	// 90..97
	0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD, 	// 98..9F
	0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0, 	// A0..A7
	0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA, 	// A8..AF
	0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D, 	// B0..B7
	0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58, 	// B8..BF
	0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67, 	// C0..C7
	0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04, 	// C8..CF
	0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88, 	// D0..D7
	0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80, 	// D8..DF
	0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE, 	// E0..E7
	0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26, 	// E8..EF
	0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7, 	// F0..F7
	0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74	 	// F8..FF
};

/*Прибавляет 1 к 128-битному числу в виде массива из 16 байт*/
block_t Increment(block_t block)
{
	block_t result = block;
	int remain = 0;
	do
	{
		//for (int i = block.size() - 1; i >= 0; i--)
		for (int i = 0; i < block.size();i++)
		{
			byte b = result[i];
			if (b < 255)
			{
				result[i]++;
				remain = 0;
				break;
			}
			else
			{
				result[i] = 0;
				remain = 1;
			}
		}
	} while (remain != 0);
	return result;
}

/*
Переводит 32-разрядное число в массив из 4-х байт
*/
byte* ToByteArray(uint32_t n)
{
	byte* result = new byte[4];
	for (int i = 0; i < 4; i++)
	{
		byte b;
		b = n >> (4 - i) - 1;
		result[i] = b;
	}
	return result;
}


block_t Kuznechik::LSX(block_t k, block_t a)
{
	block_t x = X(k, a);
	block_t sx = S(x);
	block_t lsx = L(sx);
	return lsx;
}

vector<byte> Kuznechik::Encrypt(byte* data, int dataLength)
{
	//Инициализация генератора случайных чисел
	int max_val = pow(2, 8) - 1;//случайный байт

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, max_val);
	int blocks_num = dataLength / BLOCK_SIZE;//кол-во блоков
	int bytes_left = dataLength%BLOCK_SIZE;
	
	if (bytes_left != 0)
	{
		blocks_num++;
	}
	//block_t* data_blocks = new block_t[blocks_num];
	vector<block_t> data_blocks;
	
	data_blocks.assign(blocks_num, block_t());
	for (int i = 0; i < dataLength; i += BLOCK_SIZE)
	{
		int bytes_left = dataLength - i;
		int block_index = i / BLOCK_SIZE;
		if (bytes_left > BLOCK_SIZE)
		{
			for (int j = 0; j < BLOCK_SIZE; j++)
			{
				data_blocks[block_index][j] = data[i + j];
			}
		}
		else//Если кол-во байт не кратно размеру блока, то взять остаток и дополнить нулями
		{
			data_blocks[block_index].fill(0);//заполнить нулями
			//for (int k = BLOCK_SIZE - 1, k1 = 0; k >= BLOCK_SIZE - bytes_left; k--, k1++)
			for(int j=0;j<bytes_left;j++)
			{
				data_blocks[block_index][j] = data[i+j];
			}
		}

	}
	block_t gamma_block=first_gamma;//С ним будет ксориться блок данны
	//gamma_block.fill(0);
	
#pragma region Гаммирование

	for (int i = 0; i < blocks_num; i++)
	{
		_gamma_blocks.push_back(gamma_block);
		gamma_block = Increment(gamma_block);
	}

	/*Поксорить входные блоки с гамма-блоками*/
	for (int i = 0; i < blocks_num; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			data_blocks[i][j] ^= _gamma_blocks[i][j];
		}
	}
#pragma endregion
	//byte* encrypted_data = new byte[dataLength];
	vector<byte> encrypted_data;
	encrypted_data.assign(BLOCK_SIZE*blocks_num, 0);
	for (int i = 0; i < blocks_num; i++)
	{

		block_t lsx = LSX(keys[0], data_blocks[i]);
		for (int k = 1; k < NUM_KEYS - 1; k++)
		{
			lsx = LSX(keys[k], lsx);
		}
		block_t enc_block = X(keys[NUM_KEYS - 1], lsx);
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			encrypted_data[i*BLOCK_SIZE + j] = enc_block[j];
			
		}
	}
	
	return encrypted_data;
}

byte * kuz::Kuznechik::Decrypt(vector<byte> data, int dataLength)
{
	int blocks_num = dataLength / BLOCK_SIZE;//кол-во блоков
	int bytes_left = dataLength%BLOCK_SIZE;
	if (bytes_left != 0)
	{
		blocks_num++;
	}
	//block_t* data_blocks = new block_t[blocks_num];
	vector<block_t> data_blocks;
	data_blocks.assign(blocks_num, block_t());
	for (int i = 0; i < dataLength; i += BLOCK_SIZE)
	{
		int bytes_left = dataLength - i;
		int block_index = i / BLOCK_SIZE;

		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			data_blocks[block_index][j] = data[i + j];
		}
	}
	vector<block_t> decrypted_blocks;
	for (int i = 0; i < blocks_num; i++)
	{
		block_t block = data_blocks[i];

		block_t x = X(keys[NUM_KEYS-1], block);
		block_t li = L_inv(x);
		block_t si = S_inv(li);
		/*Обратные преобразования для каждого блока*/
		for (int j = NUM_KEYS - 2; j > 0; j--)
		{
			x = X(keys[j], si);
			li = L_inv(x);
			si = S_inv(li);
		}
		block_t dec_block = X(keys[0], si);
		decrypted_blocks.push_back(dec_block);
	}
	/*Обратное гаммирование*/
	for (int i = 0; i < blocks_num; i++)
	{
		decrypted_blocks[i] = X(decrypted_blocks[i], _gamma_blocks[i]);
	}
	byte* dec_data = new byte[BLOCK_SIZE*blocks_num];
	for (int i = 0; i < blocks_num; i++)
	{
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			dec_data[i*BLOCK_SIZE + j] = decrypted_blocks[i][j];
		}
	}
	return dec_data;
}


/*
Развертывание раундовых ключей
*/
vector<key_pair> Kuznechik::GetRoundKeys(key_t k)
{
	block_t c[32];//итерационнные константы
	const int num_keys = 10;
	const int NUM_KEY_PAIRS = 5;
	key_pair keys[NUM_KEY_PAIRS];
	for (int i = 1; i <= 32; i++)//Счетчиковая последовательность
	{
		block_t vi;
		std::fill(vi.begin(), vi.end(), i);//Заполнить значениями i
		c[i - 1] = L(vi);
	}
	/*Первые два ключа создаются делением пополам*/
	block_t k1;
	for (int i = KEY_SIZE / 2, j = 0; i < KEY_SIZE; i++, j++)
	{
		k1[j] = k[i];
	}
	block_t k2;
	for (int j = 0; j < KEY_SIZE / 2; j++)
	{
		k2[j] = k[j];
	}
	keys[0][0] = k1;
	keys[0][1] = k2;
	for (int i = 0; i < NUM_KEY_PAIRS - 1; i++)
	{
		block_t round_key = c[i];
		for (int j = 0; j < 8; j++)//8 итераций сети Фейстеля
		{
			block_t* x = F(c[i + j], k1, k2);
			k1 = x[0];
			k2 = x[1];
		}
		keys[i + 1][0] = k1;
		keys[i + 1][1] = k2;
	}
	vector<key_pair> kps;
	for (int i = 0; i < NUM_KEY_PAIRS; i++)
	{
		kps.push_back(keys[i]);
	}
	return kps;
	//return vector<key_pair>();
}



/*
Умножение чисел в поле Галуа над x^8+x^7+x^6+x+1
*/
byte Kuznechik::GF_mul(byte a, byte b)
{
	uint8_t c = 0;
	uint8_t hi_bit;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (b & 1)
			c ^= a;
		hi_bit = a & 0x80;
		a <<= 1;
		if (hi_bit)
			a ^= 0xc3; // Полином x^8 + x^7 + x^6 + x + 1
		b >>= 1;
	}
	return c;
}

/*Операция, ксорящая блоки*/
block_t Kuznechik::X(block_t k, block_t a)
{
	block_t x;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		x[i] = k[i] ^ a[i];
	}
	return x;
}

block_t* Kuznechik::F(block_t k, block_t a_1, block_t a_0)
{
	block_t lsx = L(S((X(k, a_1))));
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		lsx[i] ^= a_0[i];
	}
	block_t f[2] = { lsx,a_1 };
	return f;
}



block_t Kuznechik::S(block_t a)
{
	block_t s;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		s[i] = pi[a[i]];
	}
	return s;
}

block_t Kuznechik::S_inv(block_t a)
{
	block_t s_inv;
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		s_inv[i] = pi_inv[a[i]];
	}
	return s_inv;
}


block_t Kuznechik::R(block_t a)
{
	block_t r;
	byte a_15 = 0;
	for (int i = 0; i < 15; i++)
	{
		r[i] = a[i+1];
		//a_15 ^= GF_mul(a[i], l_vec[i]);
	}
	for (int i = 15,j=0; i >= 0; i--,j++)
	{
		a_15 ^= GF_mul(a[i], l_vec[j]);
	}
	
	r[BLOCK_SIZE - 1] = a_15;//рез-т сложения в последний байт
	return r;
}

block_t Kuznechik::R_inv(block_t a)
{
	int i;
	byte a_0;
	a_0 = 0;
	block_t r_inv;
	for (int i = 0; i < 15; i++)
	{
		r_inv[i+1] = a[i];
	}
	a_0 = a[15];
	for (int i = 14,j=0; i >= 0; i--,j++)
	{
		a_0 ^= GF_mul(a[i], l_vec[j]);
	}
	r_inv[0] = a_0;
	return r_inv;
}

block_t Kuznechik::L(block_t a)
{
	block_t l = a;
	for (int i = 0; i < 16; i++)
	{
		l = R(l);//16 раз повторить преобразование R
	}
	return l;
}

block_t Kuznechik::L_inv(block_t a)
{
	block_t l_inv = a;
	for (int i = 0; i < 16; i++)
	{
		l_inv = R_inv(l_inv);
	}
	return l_inv;
}


block_t Kuznechik::EncryptBlock(block_t data, key_t key)
{
	throw std::runtime_error("Not implemented");
}



Kuznechik::Kuznechik(key_t master_key)
{
	_key_pairs = GetRoundKeys(master_key);
	int j = 0;
	for (int i = 0; i < _key_pairs.size(); i++, j += 2)
	{
		keys[j] = _key_pairs[i][0];
		keys[j + 1] = _key_pairs[i][1];
	}
	int max_val = 255;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, max_val);
	/*Сгенерировать блок гаммирования*/
	first_gamma.fill(0);
	for (int i = 0; i < BLOCK_SIZE / 2; i++)
	{
		byte rand_byte = dis(gen);
		first_gamma[i] = rand_byte;
	}
}

void kuz::Kuznechik::LoadKeys()
{
	const char* keys_path = "keys";
	vector<char> data=FileHelper::ReadAllBytes(keys_path);
	char* chars = &data[0];
	byte* bytes = reinterpret_cast<byte*>(chars);
	int j = 0;
	
	for (int i = 0,j=0; i < NUM_KEYS; i++)//загрузить 10 раундовых улючей
	{
		block_t round_key;
		for (int k = 0; k < BLOCK_SIZE; k++)
		{
			round_key[k] = bytes[i*BLOCK_SIZE + k];
		}
		j += BLOCK_SIZE;
	}
	block_t first_gamma;
	//Загрузить 1-ю гамму
	for (int k = j,l=0; k < (j + BLOCK_SIZE); k++,l++)
	{
		first_gamma[l] = bytes[k];
	}
	
}

Kuznechik::~Kuznechik()
{
}