#include "BlockHeader.h"
#include <vector>
#include <string>

class Block {
private:
    BlockHeader header;
    std::vector<std::string> transactions;
    std::string block_hash;

public:
    Block(uint64_t height, const std::string& prev_hash, const std::vector<std::string>& txs) {
        header.block_height = height;
        header.prev_block_hash = prev_hash;
        transactions = txs;
        header.timestamp = std::chrono::system_clock::now();
        generate_merkle_root();
    }

    void generate_merkle_root() {
        if (transactions.empty()) {
            header.merkle_root = "00000000000000000000000000000000";
            return;
        }
        std::string root = transactions[0];
        for (size_t i = 1; i < transactions.size(); ++i) {
            root += transactions[i];
        }
        header.merkle_root = root;
    }

    void set_nonce(uint64_t n) { header.nonce = n; }
    void set_difficulty(uint64_t d) { header.difficulty = d; }
    void set_block_hash(const std::string& hash) { block_hash = hash; }

    BlockHeader get_header() const { return header; }
    std::vector<std::string> get_transactions() const { return transactions; }
    std::string get_block_hash() const { return block_hash; }
};
