#include <vector>
#include <unordered_map>
#include <mutex>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Ledger {
private:
    std::vector<Block> blockchain;
    std::unordered_map<std::string, uint64_t> account_balances;
    std::mutex ledger_mutex;

public:
    bool add_block(const Block& block) {
        std::lock_guard<std::mutex> lock(ledger_mutex);
        if (!blockchain.empty() && block.get_header().prev_block_hash != blockchain.back().get_block_hash()) {
            return false;
        }
        blockchain.push_back(block);
        update_balances(block.get_transactions());
        return true;
    }

    void update_balances(const std::vector<std::string>& txs) {
        for (const auto& tx_str : txs) {
            std::string sender = tx_str.substr(0, 42);
            std::string receiver = tx_str.substr(42, 42);
            uint64_t amount = std::stoull(tx_str.substr(84, 20));

            account_balances[sender] = (account_balances[sender] > amount) ? account_balances[sender] - amount : 0;
            account_balances[receiver] += amount;
        }
    }

    uint64_t get_balance(const std::string& address) {
        std::lock_guard<std::mutex> lock(ledger_mutex);
        return account_balances[address];
    }

    size_t get_chain_height() {
        std::lock_guard<std::mutex> lock(ledger_mutex);
        return blockchain.size();
    }

    Block get_latest_block() {
        std::lock_guard<std::mutex> lock(ledger_mutex);
        return blockchain.back();
    }

    bool is_chain_valid() {
        std::lock_guard<std::mutex> lock(ledger_mutex);
        for (size_t i = 1; i < blockchain.size(); ++i) {
            if (blockchain[i].get_header().prev_block_hash != blockchain[i-1].get_block_hash()) {
                return false;
            }
        }
        return true;
    }
};
