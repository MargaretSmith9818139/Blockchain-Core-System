#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <vector>
#include <string>
#include "SHA256Crypto.h"

class MerkleTree {
private:
    std::vector<std::string> leaves;
    std::vector<std::string> tree;
    std::string root;

    void build_tree();
    std::string hash_pair(const std::string& a, const std::string& b);

public:
    MerkleTree(const std::vector<std::string>& data) : leaves(data) {
        build_tree();
    }

    std::string get_root() const { return root; }
    std::vector<std::string> get_proof(size_t index);
    bool verify_proof(const std::string& leaf, const std::vector<std::string>& proof, const std::string& merkle_root);
};

#endif
