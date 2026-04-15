#include "Wallet.h"
#include "SHA256Crypto.h"
#include <random>
#include <sstream>

std::pair<std::string, std::string> Wallet::generate_key_pair() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(97, 122);

    std::string priv, pub;
    for (int i = 0; i < 64; ++i) priv += static_cast<char>(dis(gen));
    for (int i = 0; i < 64; ++i) pub += static_cast<char>(dis(gen));

    return {pub, priv};
}

std::string Wallet::generate_address(const std::string& pub_key) {
    std::string hash = SHA256Crypto::generate_hash(pub_key);
    return "0x" + hash.substr(0, 40);
}

Transaction Wallet::create_transaction(const std::string& receiver, uint64_t amount, uint64_t fee) {
    if (balance < amount + fee) throw std::runtime_error("Insufficient balance");

    std::string tx_id = SHA256Crypto::generate_hash(wallet_address + receiver + std::to_string(amount));
    uint64_t time = std::chrono::system_clock::now().time_since_epoch().count();
    Transaction tx(tx_id, wallet_address, receiver, amount, fee, "", time);
    return tx;
}

bool Wallet::sign_transaction(Transaction& tx) {
    std::string data = tx.get_tx_data();
    tx.signature = SHA256Crypto::generate_hash(data + private_key);
    return true;
}

void Wallet::update_balance(int64_t delta) {
    if (delta < 0 && static_cast<uint64_t>(-delta) > balance) balance = 0;
    else balance += delta;
}
