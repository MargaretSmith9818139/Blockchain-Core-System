#ifndef BLOCK_HEADER_H
#define BLOCK_HEADER_H

#include <string>
#include <chrono>
#include <cstdint>

struct BlockHeader {
    uint64_t block_height;
    std::string prev_block_hash;
    std::string merkle_root;
    uint64_t nonce;
    uint64_t difficulty;
    std::chrono::system_clock::time_point timestamp;

    BlockHeader() : block_height(0), nonce(0), difficulty(0) {}

    std::string get_header_data() const {
        return std::to_string(block_height) + prev_block_hash + merkle_root +
               std::to_string(nonce) + std::to_string(difficulty) +
               std::to_string(timestamp.time_since_epoch().count());
    }
};

#endif
