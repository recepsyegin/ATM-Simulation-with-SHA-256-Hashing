#include "sha256.h"

#include <iomanip>
#include <sstream>


// SHA-256 constants
const uint32_t K[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

SHA256::SHA256()
{
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
    totalLength = 0;
}

uint32_t SHA256::rightRotate(uint32_t value,uint32_t bits)
{
    return (value >> bits) | (value << (32 - bits));
}

uint32_t SHA256::sigma0(uint32_t x)
{
    return rightRotate(x, 7) ^ rightRotate(x, 18) ^ (x >> 3);
}

uint32_t SHA256::sigma1(uint32_t x) {
    return rightRotate(x, 17) ^ rightRotate(x, 19) ^ (x >> 10);
}

uint32_t SHA256::Sigma0(uint32_t x) {
    return rightRotate(x, 2) ^ rightRotate(x, 13) ^ rightRotate(x, 22);
}

uint32_t SHA256::Sigma1(uint32_t x) {
    return rightRotate(x, 6) ^ rightRotate(x, 11) ^ rightRotate(x, 25);
}

uint32_t SHA256::choice(uint32_t x, uint32_t y, uint32_t z)
{
    return(x & y) ^ (~x & z);
}

uint32_t SHA256::majority(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

void SHA256::transform(const uint8_t* data)
{
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, hh;
    uint32_t t1, t2;

    // Seperate the message into 16*32-bit
    for (int i = 0,j=0; i < 16; i++, j += 4)
        w[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);

    // 16-63 arasi kelimeleri genislet
    for (int i = 16; i < 64; i++)
        w[i] = sigma1(w[i - 2]) + w[i - 7] + sigma0(w[i - 15]) + w[i - 16];
    
    a = h[0];
    b = h[1];
    c = h[2];
    d = h[3];
    e = h[4];
    f = h[5];
    g = h[6];
    hh = h[7];
}

void SHA256::pad() {
    buffer.push_back(0x80);
    size_t origSize = buffer.size();
    size_t padSize;

    if (buffer.size() % 64 < 56) {
        padSize = 56 - (buffer.size() % 64);
    }
    else {
        padSize = 56 + (64 - (buffer.size() % 64));
    }

    buffer.resize(buffer.size() + padSize);

    // Uzunlu�u ekle (bit cinsinden, big-endian)
    uint64_t bitLength = totalLength * 8;
    for (int i = 0; i < 8; i++) {
        buffer.push_back((bitLength >> (56 - i * 8)) & 0xFF);
    }
}

void SHA256::finalize() {
    pad();

    
    for (size_t i = 0; i < buffer.size(); i += 64) {
        transform(&buffer[i]);
    }
}

void SHA256::update(const std::string& input) {
    for (char c : input) {
        buffer.push_back(c);
    }
    totalLength += input.size();

    
    while (buffer.size() >= 64) {
        std::vector<uint8_t> block(buffer.begin(), buffer.begin() + 64);
        transform(block.data());
        buffer.erase(buffer.begin(), buffer.begin() + 64);
    }
}

std::string SHA256::digest() {
    finalize();

    std::stringstream ss;
    for (int i = 0; i < 8; i++) {
        ss << std::hex << std::setfill('0') << std::setw(8) << h[i];
    }

    return ss.str();
}

std::string SHA256::hash(const std::string& input) {
    SHA256 sha;
    sha.update(input);
    return sha.digest();
}