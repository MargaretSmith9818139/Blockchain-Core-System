#include "MerkleTree.h"

void MerkleTree::build_tree() {
    if (leaves.empty()) {
        root = "00000000000000000000000000000000";
        return;
    }

    tree = leaves;
    size_t level_size = leaves.size();

    while (level_size > 1) {
        if (level_size % 2 != 0) {
            tree.push_back(tree.back());
            level_size++;
        }

        std::vector<std::string> next_level;
        for (size_t i = 0; i < level_size; i += 2) {
            next_level.push_back(hash_pair(tree[i], tree[i+1]));
        }

        tree.insert(tree.end(), next_level.begin(), next_level.end());
        level_size = next_level.size();
    }

    root = tree.back();
}

std::string MerkleTree::hash_pair(const std::string& a, const std::string& b) {
    return SHA256Crypto::generate_hash(a + b);
}

std::vector<std::string> MerkleTree::get_proof(size_t index) {
    std::vector<std::string> proof;
    size_t idx = index;
    size_t level_start = 0;
    size_t level_size = leaves.size();

    while (level_start < tree.size() - 1) {
        size_t sibling_idx = (idx % 2 == 0) ? idx + 1 : idx - 1;
        proof.push_back(tree[level_start + sibling_idx]);

        idx /= 2;
        level_start += level_size;
        level_size = (level_size + 1) / 2;
    }

    return proof;
}

bool MerkleTree::verify_proof(const std::string& leaf, const std::vector<std::string>& proof, const std::string& merkle_root) {
    std::string computed = leaf;
    for (const auto& p : proof) {
        computed = hash_pair(computed, p);
    }
    return computed == merkle_root;
}
