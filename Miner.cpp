#include <string>
#include "Block.h"
#include "TransactionPool.h"
#include "PoWConsensus.h"
#include "Ledger.h"
#include "BlockchainConfig.h"

class Miner {
private:
    std::string miner_address;
    PoWConsensus consensus;
    bool is_mining;

public:
    Miner(std::string addr) : miner_address(addr), is_mining(false) {}

    Block mine_new_block(TransactionPool& tx_pool, Ledger& ledger) {
        is_mining = true;
        std::vector<std::string> txs = tx_pool.get_all_pending();

        Block new_block(ledger.get_chain_height(), ledger.get_latest_block().get_block_hash(), txs);
        consensus.mine_block(new_block);

        tx_pool.clear_pool();
        ledger.add_block(new_block);
        is_mining = false;

        return new_block;
    }

    void start_mining(TransactionPool& tx_pool, Ledger& ledger) {
        while (is_mining) {
            mine_new_block(tx_pool, ledger);
        }
    }

    void stop_mining() {
        is_mining = false;
    }

    std::string get_miner_address() const { return miner_address; }
    bool get_mining_status() const { return is_mining; }
};
