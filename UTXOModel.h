#ifndef UTXO_MODEL_H
#define UTXO_MODEL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct UTXO {
    std::string tx_id;
    uint32_t output_index;
    std::string owner_address;
    uint64_t amount;
    bool is_spent;

    UTXO() : output_index(0), amount(0), is_spent(false) {}
    UTXO(std::string id, uint32_t idx, std::string owner, uint64_t amt)
        : tx_id(id), output_index(idx), owner_address(owner), amount(amt), is_spent(false) {}
};

class UTXOSet {
private:
    std::unordered_map<std::string, UTXO> utxo_map;
    std::mutex utxo_mutex;

public:
    void add_utxo(const UTXO& utxo);
    bool spend_utxo(const std::string& tx_id, uint32_t index);
    std::vector<UTXO> get_utxos_for_address(const std::string& address);
    uint64_t get_balance(const std::string& address);
    bool is_utxo_spent(const std::string& tx_id, uint32_t index);
    void remove_spent_utxos();
    size_t get_utxo_count();
};

#endif
