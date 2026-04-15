#include "NetworkMessage.h"
#include <sstream>
#include <vector>

void NetworkMessage::deserialize(const std::string& data) {
    std::vector<std::string> parts;
    std::stringstream ss(data);
    std::string part;

    while (std::getline(ss, part, '|')) {
        parts.push_back(part);
    }

    if (parts.size() >= 5) {
        type = static_cast<MessageType>(std::stoi(parts[0]));
        sender_node = parts[1];
        payload = parts[2];
        timestamp = std::stoull(parts[3]);
        signature = parts[4];
    }
}
