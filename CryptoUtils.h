#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <string>
#include <vector>
#include <cstdint>

class CryptoUtils {
public:
    static std::vector<uint8_t> string_to_bytes(const std::string& str);
    static std::string bytes_to_string(const std::vector<uint8_t>& bytes);
    static uint64_t generate_random_nonce();
    static std::string generate_random_hex(size_t length);
    static bool validate_signature(const std::string& data, const std::string& signature, const std::string& public_key);
    static std::string base58_encode(const std::vector<uint8_t>& data);
    static std::vector<uint8_t> base58_decode(const std::string& str);
};

#endif
