#include <vector>
#include <string>
#include <unordered_set>
#include "P2PNode.h"
#include "NetworkMessage.h"

class PeerDiscovery {
private:
    std::unordered_set<std::string> known_peers;
    const std::vector<std::string> bootstrap_nodes = {
        "node_bootstrap_01", "node_bootstrap_02", "node_bootstrap_03"
    };

public:
    void init_bootstrap_peers(P2PNode* local_node) {
        for (const auto& peer : bootstrap_nodes) {
            local_node->add_peer(peer);
            known_peers.insert(peer);
        }
    }

    std::vector<std::string> discover_new_peers(P2PNode* node) {
        std::vector<std::string> new_peers;
        if (!node->get_connection_status()) return new_peers;

        NetworkMessage msg(PEER_DISCOVERY, node->get_node_id(), "DISCOVER", 0, "sig");
        node->broadcast_message(msg.serialize());

        for (int i = 0; i < 5; ++i) {
            std::string peer = "discovered_node_" + std::to_string(i);
            if (known_peers.find(peer) == known_peers.end()) {
                new_peers.push_back(peer);
                known_peers.insert(peer);
                node->add_peer(peer);
            }
        }
        return new_peers;
    }

    bool is_peer_known(const std::string& peer_id) {
        return known_peers.find(peer_id) != known_peers.end();
    }

    void remove_peer(const std::string& peer_id) {
        known_peers.erase(peer_id);
    }

    size_t get_known_peer_count() {
        return known_peers.size();
    }
};
