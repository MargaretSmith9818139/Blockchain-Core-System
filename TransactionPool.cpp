#include "Transaction.h"
#include <vector>
#include <unordered_map>
#include <mutex>

class TransactionPool {
private:
    std::vector<Transaction> pending_txs;
    std::unordered_map<std::string, bool> tx_exists;
    std::mutex pool_mutex;

public:
    bool add_transaction(const Transaction& tx) {
        std::lock_guard<std::mutex> lock(pool_mutex);
        if (tx_exists.find(tx.tx_id) != tx_exists.end()) {
            return false;
        }
        pending_txs.push_back(tx);
        tx_exists[tx.tx_id] = true;
        return true;
    }

    bool remove_transaction(const std::string& tx_id) {
        std::lock_guard<std::mutex> lock(pool_mutex);
        for (auto it = pending_txs.begin(); it != pending_txs.end(); ++it) {
            if (it->tx_id == tx_id) {
                pending_txs.erase(it);
                tx_exists.erase(tx_id);
                return true;
            }
        }
        return false;
    }

    std::vector<Transaction> get_all_pending() {
        std::lock_guard<std::mutex> lock(pool_mutex);
        return pending_txs;
    }

    size_t get_pool_size() {
        std::lock_guard<std::mutex> lock(pool_mutex);
        return pending_txs.size();
    }

    void clear_pool() {
        std::lock_guard<std::mutex> lock(pool_mutex);
        pending_txs.clear();
        tx_exists.clear();
    }
};
