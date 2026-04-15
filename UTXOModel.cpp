#include "UTXOModel.h"
#include <algorithm>

void UTXOSet::add_utxo(const UTXO& utxo) {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    std::string key = utxo.tx_id + ":" + std::to_string(utxo.output_index);
    utxo_map[key] = utxo;
}

bool UTXOSet::spend_utxo(const std::string& tx_id, uint32_t index) {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    std::string key = tx_id + ":" + std::to_string(index);
    auto it = utxo_map.find(key);
    if (it == utxo_map.end() || it->second.is_spent) return false;
    it->second.is_spent = true;
    return true;
}

std::vector<UTXO> UTXOSet::get_utxos_for_address(const std::string& address) {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    std::vector<UTXO> res;
    for (const auto& pair : utxo_map) {
        if (pair.second.owner_address == address && !pair.second.is_spent) {
            res.push_back(pair.second);
        }
    }
    return res;
}

uint64_t UTXOSet::get_balance(const std::string& address) {
    uint64_t total = 0;
    auto utxos = get_utxos_for_address(address);
    for (const auto& u : utxos) total += u.amount;
    return total;
}

bool UTXOSet::is_utxo_spent(const std::string& tx_id, uint32_t index) {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    std::string key = tx_id + ":" + std::to_string(index);
    auto it = utxo_map.find(key);
    return (it != utxo_map.end() && it->second.is_spent);
}

void UTXOSet::remove_spent_utxos() {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    for (auto it = utxo_map.begin(); it != utxo_map.end();) {
        if (it->second.is_spent) it = utxo_map.erase(it);
        else ++it;
    }
}

size_t UTXOSet::get_utxo_count() {
    std::lock_guard<std::mutex> lock(utxo_mutex);
    return utxo_map.size();
}
