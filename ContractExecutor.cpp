#include "ContractExecutor.h"
#include <stdexcept>

bool ContractExecutor::deploy_contract(SmartContractBase* contract) {
    if (!contract || contracts.find(contract->get_contract_address()) != contracts.end()) {
        return false;
    }
    contracts[contract->get_contract_address()] = contract;
    execution_logs.push_back("Deployed contract: " + contract->get_contract_address());
    return true;
}

bool ContractExecutor::execute_contract(const std::string& addr, const std::vector<std::string>& params) {
    auto it = contracts.find(addr);
    if (it == contracts.end() || !it->second->is_contract_active()) {
        execution_logs.push_back("Execution failed: " + addr);
        return false;
    }

    bool res = it->second->execute(params);
    execution_logs.push_back("Executed " + addr + ": " + (res ? "success" : "fail"));
    return res;
}

bool ContractExecutor::terminate_contract(const std::string& addr) {
    auto it = contracts.find(addr);
    if (it == contracts.end()) return false;

    it->second->terminate_contract();
    execution_logs.push_back("Terminated contract: " + addr);
    return true;
}

SmartContractBase* ContractExecutor::get_contract(const std::string& addr) {
    auto it = contracts.find(addr);
    return (it != contracts.end()) ? it->second : nullptr;
}

std::vector<std::string> ContractExecutor::get_execution_logs() {
    return execution_logs;
}

void ContractExecutor::clear_logs() {
    execution_logs.clear();
}
