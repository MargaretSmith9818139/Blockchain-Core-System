#include "Block.h"
#include "SHA256Crypto.h"
#include <vector>
#include <string>

class GenesisBlockCreator {
public:
    static Block create_genesis_block() {
        std::vector<std::string> genesis_txs = {
            "GENESIS_TX_INITIAL_REWARD",
            "NETWORK_BOOTSTRAP_TX"
        };

        Block genesis(0, "00000000000000000000000000000000", genesis_txs);
        genesis.set_difficulty(1);
        genesis.set_nonce(12345);

        std::string hash = SHA256Crypto::generate_hash(genesis.get_header().get_header_data());
        genesis.set_block_hash(hash);

        return genesis;
    }

    static bool validate_genesis_block(const Block& block) {
        if (block.get_header().block_height != 0) return false;
        if (block.get_header().prev_block_hash != "00000000000000000000000000000000") return false;
        if (block.get_transactions().size() < 2) return false;
        return true;
    }
};
