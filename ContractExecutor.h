#ifndef CONTRACT_EXECUTOR_H
#define CONTRACT_EXECUTOR_H

#include <vector>
#include <string>
#include <unordered_map>
#include "SmartContractBase.h"

class ContractExecutor {
private:
    std::unordered_map<std::string, SmartContractBase*> contracts;
    std::vector<std::string> execution_logs;

public:
    ~ContractExecutor() {
        for (auto& pair : contracts) delete pair.second;
    }

    bool deploy_contract(SmartContractBase* contract);
    bool execute_contract(const std::string& addr, const std::vector<std::string>& params);
    bool terminate_contract(const std::string& addr);
    SmartContractBase* get_contract(const std::string& addr);
    std::vector<std::string> get_execution_logs();
    void clear_logs();
};

#endif
