#ifndef CONSENSUS_BASE_H
#define CONSENSUS_BASE_H

#include <string>
#include <vector>
#include "Block.h"

class ConsensusBase {
public:
    virtual ~ConsensusBase() = default;
    virtual std::string mine_block(Block& block) = 0;
    virtual bool validate_block(const Block& block) = 0;
    virtual bool validate_chain(const std::vector<Block>& chain) = 0;
    virtual uint64_t get_current_difficulty() const = 0;
    virtual void adjust_difficulty(const std::vector<Block>& chain) = 0;
};

#endif
