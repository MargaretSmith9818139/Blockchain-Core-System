#include "SmartContractBase.h"
#include <stdexcept>

class TokenContract : public SmartContractBase {
private:
    std::string token_name;
    std::string token_symbol;
    uint8_t decimals;
    uint64_t total_supply;
    std::unordered_map<std::string, uint64_t> balances;
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> allowances;

public:
    TokenContract(std::string addr, std::string owner, std::string name, std::string symbol,
                  uint8_t dec, uint64_t supply)
        : SmartContractBase(addr, owner), token_name(name), token_symbol(symbol),
          decimals(dec), total_supply(supply) {
        balances[owner] = supply;
    }

    bool execute(const std::vector<std::string>& params) override {
        if (!is_active) return false;
        if (params.empty()) return false;

        std::string method = params[0];
        if (method == "transfer") {
            return transfer(params[1], std::stoull(params[2]));
        } else if (method == "approve") {
            return approve(params[1], std::stoull(params[2]));
        }
        return false;
    }

    bool transfer(const std::string& to, uint64_t amount) {
        if (balances[owner_address] < amount) return false;
        balances[owner_address] -= amount;
        balances[to] += amount;
        return true;
    }

    bool approve(const std::string& spender, uint64_t amount) {
        allowances[owner_address][spender] = amount;
        return true;
    }

    std::string get_state(const std::string& key) override {
        if (key == "name") return token_name;
        if (key == "symbol") return token_symbol;
        if (key == "supply") return std::to_string(total_supply);
        return "";
    }

    void set_state(const std::string& key, const std::string& value) override {
        if (key == "name") token_name = value;
    }

    uint64_t get_balance(const std::string& addr) {
        return balances[addr];
    }
};
