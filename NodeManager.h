#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "P2PNode.h"

class NodeManager {
private:
    std::unordered_map<std::string, P2PNode*> nodes;
    std::vector<std::string> active_nodes;

public:
    ~NodeManager() {
        for (auto& pair : nodes) delete pair.second;
    }

    bool register_node(P2PNode* node);
    bool remove_node(const std::string& node_id);
    bool activate_node(const std::string& node_id);
    bool deactivate_node(const std::string& node_id);
    std::vector<P2PNode*> get_all_active_nodes();
    P2PNode* get_node_by_id(const std::string& node_id);
    size_t get_active_node_count();
};

#endif
