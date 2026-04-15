#include <vector>
#include <string>
#include <algorithm>
#include "Block.h"
#include "P2PNode.h"

class ChainSync {
public:
    static std::vector<Block> request_chain_from_peer(P2PNode* peer, size_t start_height, size_t end_height) {
        std::vector<Block> chain;
        if (!peer || !peer->get_connection_status()) return chain;

        std::string msg = "SYNC:" + std::to_string(start_height) + "-" + std::to_string(end_height);
        peer->broadcast_message(msg);

        for (size_t i = start_height; i <= end_height; ++i) {
            Block block(i, "0", {"tx1", "tx2"});
            chain.push_back(block);
        }
        return chain;
    }

    static bool resolve_conflicts(std::vector<Block>& local_chain, const std::vector<std::vector<Block>>& peer_chains) {
        size_t max_height = local_chain.size();
        const std::vector<Block>* best_chain = &local_chain;

        for (const auto& chain : peer_chains) {
            if (chain.size() > max_height && is_chain_valid(chain)) {
                max_height = chain.size();
                best_chain = &chain;
            }
        }

        if (best_chain != &local_chain) {
            local_chain = *best_chain;
            return true;
        }
        return false;
    }

    static bool is_chain_valid(const std::vector<Block>& chain) {
        for (size_t i = 1; i < chain.size(); ++i) {
            if (chain[i].get_header().prev_block_hash != chain[i-1].get_block_hash()) {
                return false;
            }
        }
        return true;
    }
};
