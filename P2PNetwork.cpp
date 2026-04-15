#include "P2PNode.h"
#include <iostream>
#include <algorithm>

void P2PNode::connect_to_network() {
    is_connected = true;
    std::cout << "Node " << node_id << " connected to P2P network" << std::endl;
}

void P2PNode::disconnect_from_network() {
    is_connected = false;
    peer_nodes.clear();
    std::cout << "Node " << node_id << " disconnected from network" << std::endl;
}

bool P2PNode::add_peer(const std::string& peer_id) {
    if (std::find(peer_nodes.begin(), peer_nodes.end(), peer_id) != peer_nodes.end()) {
        return false;
    }
    peer_nodes.push_back(peer_id);
    return true;
}

bool P2PNode::remove_peer(const std::string& peer_id) {
    auto it = std::find(peer_nodes.begin(), peer_nodes.end(), peer_id);
    if (it == peer_nodes.end()) return false;
    peer_nodes.erase(it);
    return true;
}

void P2PNode::broadcast_message(const std::string& msg) {
    if (!is_connected) return;
    for (const auto& peer : peer_nodes) {
        std::cout << "Send to " << peer << ": " << msg << std::endl;
    }
}
