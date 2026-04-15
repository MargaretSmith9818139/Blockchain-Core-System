#ifndef SMART_CONTRACT_BASE_H
#define SMART_CONTRACT_BASE_H

#include <string>
#include <vector>
#include <unordered_map>

class SmartContractBase {
protected:
    std::string contract_address;
    std::string owner_address;
    bool is_active;
    std::unordered_map<std::string, std::string> contract_storage;

public:
    SmartContractBase(std::string addr, std::string owner)
        : contract_address(addr), owner_address(owner), is_active(true) {}

    virtual ~SmartContractBase() = default;
    virtual bool execute(const std::vector<std::string>& params) = 0;
    virtual std::string get_state(const std::string& key) = 0;
    virtual void set_state(const std::string& key, const std::string& value) = 0;
    virtual void terminate_contract() { is_active = false; }

    std::string get_contract_address() const { return contract_address; }
    std::string get_owner() const { return owner_address; }
    bool is_contract_active() const { return is_active; }
};

#endif
