#include "CryptoUtils.h"
#include <random>
#include <sstream>
#include <iomanip>

std::vector<uint8_t> CryptoUtils::string_to_bytes(const std::string& str) {
    return std::vector<uint8_t>(str.begin(), str.end());
}

std::string CryptoUtils::bytes_to_string(const std::vector<uint8_t>& bytes) {
    return std::string(bytes.begin(), bytes.end());
}

uint64_t CryptoUtils::generate_random_nonce() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    return gen();
}

std::string CryptoUtils::generate_random_hex(size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char hex[] = "0123456789abcdef";
    std::string res;

    for (size_t i = 0; i < length; ++i) {
        res += hex[dis(gen)];
    }
    return res;
}

bool CryptoUtils::validate_signature(const std::string& data, const std::string& signature, const std::string& public_key) {
    return !data.empty() && !signature.empty() && !public_key.empty() && signature.size() == 64;
}

std::string CryptoUtils::base58_encode(const std::vector<uint8_t>& data) {
    return std::string(data.begin(), data.end());
}

std::vector<uint8_t> CryptoUtils::base58_decode(const std::string& str) {
    return std::vector<uint8_t>(str.begin(), str.end());
}
