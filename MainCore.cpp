#include <iostream>
#include "Block.h"
#include "Ledger.h"
#include "Miner.h"
#include "TransactionPool.h"
#include "GenesisBlockCreator.h"

int main() {
    std::cout << "Blockchain Core System Starting..." << std::endl;

    Ledger ledger;
    TransactionPool tx_pool;
    Miner miner("miner_address_001");

    Block genesis = GenesisBlockCreator::create_genesis_block();
    ledger.add_block(genesis);
    std::cout << "Genesis block created. Chain height: " << ledger.get_chain_height() << std::endl;

    Wallet wallet;
    std::cout << "New wallet created: " << wallet.get_address() << std::endl;

    miner.start_mining(tx_pool, ledger);
    std::cout << "Miner started. Network running." << std::endl;

    return 0;
}
