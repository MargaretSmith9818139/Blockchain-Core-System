#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <cstdint>

struct Transaction {
    std::string tx_id;
    std::string sender_address;
    std::string receiver_address;
    uint64_t amount;
    uint64_t fee;
    std::string signature;
    uint64_t timestamp;

    Transaction() : amount(0), fee(0), timestamp(0) {}

    Transaction(std::string id, std::string sender, std::string receiver,
                uint64_t amt, uint64_t f, std::string sig, uint64_t time)
        : tx_id(id), sender_address(sender), receiver_address(receiver),
          amount(amt), fee(f), signature(sig), timestamp(time) {}

    std::string get_tx_data() const {
        return tx_id + sender_address + receiver_address +
               std::to_string(amount) + std::to_string(fee) +
               std::to_string(timestamp);
    }
};

#endif
