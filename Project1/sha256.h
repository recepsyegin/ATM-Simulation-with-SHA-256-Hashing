#pragma once
class sha256
{
};

#pragma once


#include <string>
#include <cstdint>
#include <vector>

class SHA256
{
private:
	uint32_t h[8];
	std::vector<uint8_t> buffer;
	uint64_t totalLength;	// Toplam mesaj uzunluðu (bit)

	// Helper functions
	static uint32_t rightRotate(uint32_t value,uint32_t bits);
	static uint32_t sigma0(uint32_t x);
	static uint32_t sigma1(uint32_t x);
	static uint32_t Sigma0(uint32_t x);
	static uint32_t Sigma1(uint32_t x);
	static uint32_t choice(uint32_t x, uint32_t y, uint32_t z);
	static uint32_t majority(uint32_t x, uint32_t y, uint32_t z);

	void transform(const uint8_t* data);
	void pad();
	void finalize();

public:
	SHA256();
	void update(const std::string& input);
	std::string digest();
	static std::string hash(const std::string& input);

};