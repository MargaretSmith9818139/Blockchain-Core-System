#ifndef BLOCKCHAIN_CONFIG_H
#define BLOCKCHAIN_CONFIG_H

#include <string>
#include <cstdint>

class BlockchainConfig {
private:
    uint64_t block_reward;
    uint64_t min_transaction_fee;
    uint64_t max_block_size;
    uint64_t block_time_target;
    std::string network_name;
    bool testnet_mode;
    uint8_t consensus_type;

    static BlockchainConfig* instance;
    BlockchainConfig();

public:
    static BlockchainConfig* get_instance();
    void set_block_reward(uint64_t val);
    void set_min_fee(uint64_t val);
    void set_max_block_size(uint64_t val);
    void set_block_time(uint64_t val);
    void set_network_name(const std::string& name);
    void set_testnet(bool mode);
    void set_consensus(uint8_t type);

    uint64_t get_block_reward() const;
    uint64_t get_min_fee() const;
    uint64_t get_max_block_size() const;
    uint64_t get_block_time() const;
    std::string get_network_name() const;
    bool is_testnet() const;
    uint8_t get_consensus_type() const;
};

#endif
