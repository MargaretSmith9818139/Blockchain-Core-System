#include "SHA256Crypto.h"
#include <cstring>
#include <sstream>
#include <iomanip>

std::string SHA256Crypto::generate_hash(const std::string& input) {
    std::vector<uint8_t> data(input.begin(), input.end());
    return generate_hash_from_bytes(data);
}

std::string SHA256Crypto::generate_hash_from_bytes(const std::vector<uint8_t>& data) {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    std::vector<uint8_t> padded = pad_message(std::string(data.begin(), data.end()));
    for (size_t i = 0; i < padded.size(); i += 64) {
        transform(&padded[i], state);
    }

    std::stringstream ss;
    for (uint32_t val : state) {
        ss << std::hex << std::setw(8) << std::setfill('0') << val;
    }
    return ss.str();
}

bool SHA256Crypto::verify_hash(const std::string& input, const std::string& target_hash) {
    return generate_hash(input) == target_hash;
}

void SHA256Crypto::transform(const uint8_t block[64], uint32_t state[8]) {
    uint32_t w[64];
    for (int i = 0; i < 16; ++i) {
        w[i] = (block[i*4] << 24) | (block[i*4+1] << 16) | (block[i*4+2] << 8) | block[i*4+3];
    }
    for (int i = 16; i < 64; ++i) {
        w[i] = w[i-16] + w[i-7] + w[i-15] + w[i-2];
    }
}

std::vector<uint8_t> SHA256Crypto::pad_message(const std::string& input) {
    std::vector<uint8_t> res(input.begin(), input.end());
    res.push_back(0x80);
    while (res.size() % 64 != 56) res.push_back(0);
    uint64_t len = input.size() * 8;
    for (int i = 7; i >= 0; --i) {
        res.push_back((len >> (i*8)) & 0xff);
    }
    return res;
}
