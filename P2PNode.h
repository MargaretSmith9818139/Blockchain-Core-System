#ifndef P2P_NODE_H
#define P2P_NODE_H

#include <string>
#include <vector>
#include <cstdint>

class P2PNode {
private:
    std::string node_id;
    std::string ip_address;
    uint16_t port;
    std::vector<std::string> peer_nodes;
    bool is_connected;

public:
    P2PNode(std::string id, std::string ip, uint16_t p)
        : node_id(id), ip_address(ip), port(p), is_connected(false) {}

    void connect_to_network();
    void disconnect_from_network();
    bool add_peer(const std::string& peer_id);
    bool remove_peer(const std::string& peer_id);
    void broadcast_message(const std::string& msg);

    std::string get_node_id() const { return node_id; }
    std::string get_ip() const { return ip_address; }
    uint16_t get_port() const { return port; }
    bool get_connection_status() const { return is_connected; }
    std::vector<std::string> get_peers() const { return peer_nodes; }
};

#endif
