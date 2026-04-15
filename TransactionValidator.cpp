#include <string>
#include "Transaction.h"
#include "Wallet.h"
#include "CryptoUtils.h"

class TransactionValidator {
public:
    static bool validate_basic_structure(const Transaction& tx) {
        if (tx.tx_id.empty()) return false;
        if (tx.sender_address.empty() || tx.receiver_address.empty()) return false;
        if (tx.amount == 0 && tx.fee == 0) return false;
        if (tx.timestamp == 0) return false;
        return true;
    }

    static bool validate_signature(const Transaction& tx) {
        if (tx.signature.empty()) return false;
        std::string data = tx.get_tx_data();
        return CryptoUtils::validate_signature(data, tx.signature, tx.sender_address);
    }

    static bool validate_balance(const Transaction& tx, uint64_t balance) {
        return balance >= tx.amount + tx.fee;
    }

    static bool validate_duplicate(const Transaction& tx, const std::unordered_map<std::string, bool>& tx_pool) {
        return tx_pool.find(tx.tx_id) == tx_pool.end();
    }

    static bool full_transaction_validation(const Transaction& tx, uint64_t balance, const std::unordered_map<std::string, bool>& tx_pool) {
        return validate_basic_structure(tx) &&
               validate_signature(tx) &&
               validate_balance(tx, balance) &&
               validate_duplicate(tx, tx_pool);
    }
};
