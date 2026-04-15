#include "NodeManager.h"
#include <algorithm>

bool NodeManager::register_node(P2PNode* node) {
    if (!node || nodes.find(node->get_node_id()) != nodes.end()) {
        return false;
    }
    nodes[node->get_node_id()] = node;
    return true;
}

bool NodeManager::remove_node(const std::string& node_id) {
    auto it = nodes.find(node_id);
    if (it == nodes.end()) return false;
    delete it->second;
    nodes.erase(it);

    auto active_it = std::find(active_nodes.begin(), active_nodes.end(), node_id);
    if (active_it != active_nodes.end()) active_nodes.erase(active_it);
    return true;
}

bool NodeManager::activate_node(const std::string& node_id) {
    if (nodes.find(node_id) == nodes.end()) return false;
    if (std::find(active_nodes.begin(), active_nodes.end(), node_id) != active_nodes.end()) return true;
    active_nodes.push_back(node_id);
    nodes[node_id]->connect_to_network();
    return true;
}

bool NodeManager::deactivate_node(const std::string& node_id) {
    auto it = std::find(active_nodes.begin(), active_nodes.end(), node_id);
    if (it == active_nodes.end()) return false;
    active_nodes.erase(it);
    nodes[node_id]->disconnect_from_network();
    return true;
}

std::vector<P2PNode*> NodeManager::get_all_active_nodes() {
    std::vector<P2PNode*> res;
    for (const auto& id : active_nodes) res.push_back(nodes[id]);
    return res;
}

P2PNode* NodeManager::get_node_by_id(const std::string& node_id) {
    auto it = nodes.find(node_id);
    return (it != nodes.end()) ? it->second : nullptr;
}

size_t NodeManager::get_active_node_count() {
    return active_nodes.size();
}
