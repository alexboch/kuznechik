#pragma once
#include <vector>
#include <array>
#include <random>
#include <exception>
namespace kuz {
	typedef  unsigned char byte;
	using namespace std;
	static const int BLOCK_SIZE = 16;//128 бит
	const int NUM_KEYS = 10;
	static const int KEY_SIZE = 32;//256 бит
	using block_t = array<byte, BLOCK_SIZE>;
	using key_pair = array<block_t,2>;
	using key_t = array<byte, KEY_SIZE>;
	class Kuznechik
	{
	private:

		vector<block_t> _gamma_blocks;
		vector<key_pair> _key_pairs;
		array<block_t, NUM_KEYS> keys;
		block_t GetBlocks(byte* data);
	public:
		byte* Encrypt(byte* data, int dataLength);
		byte* Decrypt(byte* data, int dataLength);
		vector<key_pair> GetRoundKeys(key_t k);
		block_t X(block_t k, block_t a);
		block_t* F(block_t k, block_t a_1, block_t a_0);
		Kuznechik(key_t master_key);
		block_t EncryptBlock(block_t data, key_t key);
		block_t R_inv(block_t a);
		block_t L_inv(block_t a);
		block_t L(block_t a);
		block_t R(block_t a);
		block_t S_inv(block_t a);
		block_t S(block_t a);
		block_t LSX(block_t k, block_t a);
		byte GF_mul(byte a, byte b);
		Kuznechik::~Kuznechik();
	};
}

