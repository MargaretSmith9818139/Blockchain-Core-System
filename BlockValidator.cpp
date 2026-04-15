#include <string>
#include <vector>
#include "Block.h"
#include "SHA256Crypto.h"
#include "Transaction.h"

class BlockValidator {
public:
    static bool validate_block_structure(const Block& block) {
        if (block.get_header().block_height < 0) return false;
        if (block.get_header().prev_block_hash.empty()) return false;
        if (block.get_header().merkle_root.empty()) return false;
        return true;
    }

    static bool validate_block_hash(const Block& block) {
        std::string computed = SHA256Crypto::generate_hash(block.get_header().get_header_data());
        return computed == block.get_block_hash();
    }

    static bool validate_merkle_root(const Block& block) {
        std::vector<std::string> txs = block.get_transactions();
        if (txs.empty()) return block.get_header().merkle_root == "00000000000000000000000000000000";

        std::string root = txs[0];
        for (size_t i = 1; i < txs.size(); ++i) root += txs[i];
        return root == block.get_header().merkle_root;
    }

    static bool validate_transactions(const Block& block) {
        for (const auto& tx_str : block.get_transactions()) {
            if (tx_str.size() < 100) return false;
        }
        return true;
    }

    static bool full_block_validation(const Block& block) {
        return validate_block_structure(block) &&
               validate_block_hash(block) &&
               validate_merkle_root(block) &&
               validate_transactions(block);
    }
};
