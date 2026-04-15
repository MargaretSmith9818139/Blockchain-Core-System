#ifndef SHA256_CRYPTO_H
#define SHA256_CRYPTO_H

#include <string>
#include <vector>

class SHA256Crypto {
public:
    static std::string generate_hash(const std::string& input);
    static std::string generate_hash_from_bytes(const std::vector<uint8_t>& data);
    static bool verify_hash(const std::string& input, const std::string& target_hash);

private:
    static void transform(const uint8_t block[64], uint32_t state[8]);
    static std::vector<uint8_t> pad_message(const std::string& input);
};

#endif
