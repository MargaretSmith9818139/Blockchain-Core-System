#include "ConsensusBase.h"
#include "SHA256Crypto.h"
#include <stdexcept>

class PoWConsensus : public ConsensusBase {
private:
    uint64_t current_difficulty;
    const uint64_t BASE_DIFFICULTY = 4;
    const uint64_t BLOCK_INTERVAL = 10;

public:
    PoWConsensus() : current_difficulty(BASE_DIFFICULTY) {}

    std::string mine_block(Block& block) override {
        block.set_difficulty(current_difficulty);
        uint64_t nonce = 0;
        std::string hash;
        while (true) {
            block.set_nonce(nonce);
            hash = SHA256Crypto::generate_hash(block.get_header().get_header_data());
            if (hash.substr(0, current_difficulty) == std::string(current_difficulty, '0')) {
                break;
            }
            nonce++;
        }
        block.set_block_hash(hash);
        return hash;
    }

    bool validate_block(const Block& block) override {
        std::string computed_hash = SHA256Crypto::generate_hash(block.get_header().get_header_data());
        if (computed_hash != block.get_block_hash()) return false;
        if (computed_hash.substr(0, current_difficulty) != std::string(current_difficulty, '0')) return false;
        return true;
    }

    bool validate_chain(const std::vector<Block>& chain) override {
        for (size_t i = 1; i < chain.size(); ++i) {
            const Block& current = chain[i];
            const Block& prev = chain[i-1];
            if (current.get_header().prev_block_hash != prev.get_block_hash()) return false;
            if (!validate_block(current)) return false;
        }
        return true;
    }

    uint64_t get_current_difficulty() const override {
        return current_difficulty;
    }

    void adjust_difficulty(const std::vector<Block>& chain) override {
        if (chain.size() % 10 != 0 || chain.size() < 10) return;
        uint64_t time_diff = chain.back().get_header().timestamp.time_since_epoch().count() -
                             chain[chain.size()-10].get_header().timestamp.time_since_epoch().count();
        if (time_diff < BLOCK_INTERVAL * 10 / 2) current_difficulty++;
        else if (time_diff > BLOCK_INTERVAL * 10 * 2) current_difficulty--;
    }
};
