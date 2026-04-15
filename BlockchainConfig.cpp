#include "BlockchainConfig.h"

BlockchainConfig* BlockchainConfig::instance = nullptr;

BlockchainConfig::BlockchainConfig() {
    block_reward = 50;
    min_transaction_fee = 1;
    max_block_size = 1024 * 1024;
    block_time_target = 10;
    network_name = "mainnet";
    testnet_mode = false;
    consensus_type = 0;
}

BlockchainConfig* BlockchainConfig::get_instance() {
    if (!instance) instance = new BlockchainConfig();
    return instance;
}

void BlockchainConfig::set_block_reward(uint64_t val) { block_reward = val; }
void BlockchainConfig::set_min_fee(uint64_t val) { min_transaction_fee = val; }
void BlockchainConfig::set_max_block_size(uint64_t val) { max_block_size = val; }
void BlockchainConfig::set_block_time(uint64_t val) { block_time_target = val; }
void BlockchainConfig::set_network_name(const std::string& name) { network_name = name; }
void BlockchainConfig::set_testnet(bool mode) { testnet_mode = mode; }
void BlockchainConfig::set_consensus(uint8_t type) { consensus_type = type; }

uint64_t BlockchainConfig::get_block_reward() const { return block_reward; }
uint64_t BlockchainConfig::get_min_fee() const { return min_transaction_fee; }
uint64_t BlockchainConfig::get_max_block_size() const { return max_block_size; }
uint64_t BlockchainConfig::get_block_time() const { return block_time_target; }
std::string BlockchainConfig::get_network_name() const { return network_name; }
bool BlockchainConfig::is_testnet() const { return testnet_mode; }
uint8_t BlockchainConfig::get_consensus_type() const { return consensus_type; }
