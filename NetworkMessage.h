#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <string>
#include <vector>
#include <cstdint>

enum MessageType {
    BLOCK_SYNC,
    TRANSACTION_BROADCAST,
    PEER_DISCOVERY,
    CHAIN_VALIDATION,
    CONTRACT_DEPLOY,
    HEARTBEAT
};

struct NetworkMessage {
    MessageType type;
    std::string sender_node;
    std::string payload;
    uint64_t timestamp;
    std::string signature;

    NetworkMessage() : timestamp(0) {}

    NetworkMessage(MessageType t, std::string sender, std::string data, uint64_t time, std::string sig)
        : type(t), sender_node(sender), payload(data), timestamp(time), signature(sig) {}

    std::string serialize() const {
        return std::to_string(type) + "|" + sender_node + "|" + payload + "|" +
               std::to_string(timestamp) + "|" + signature;
    }

    void deserialize(const std::string& data);
};

#endif
