#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <utility>
#include "Transaction.h"

class Wallet {
private:
    std::string public_key;
    std::string private_key;
    uint64_t balance;
    std::string wallet_address;

    std::pair<std::string, std::string> generate_key_pair();
    std::string generate_address(const std::string& pub_key);

public:
    Wallet() {
        auto keys = generate_key_pair();
        public_key = keys.first;
        private_key = keys.second;
        wallet_address = generate_address(public_key);
        balance = 0;
    }

    Transaction create_transaction(const std::string& receiver, uint64_t amount, uint64_t fee);
    bool sign_transaction(Transaction& tx);
    void update_balance(int64_t delta);

    std::string get_public_key() const { return public_key; }
    std::string get_address() const { return wallet_address; }
    uint64_t get_balance() const { return balance; }
};

#endif
