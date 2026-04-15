#include "StateDatabase.h"

void StateDatabase::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(db_mutex);
    kv_store[key] = value;
}

std::string StateDatabase::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(db_mutex);
    auto it = kv_store.find(key);
    return (it != kv_store.end()) ? it->second : "";
}

bool StateDatabase::exists(const std::string& key) {
    std::lock_guard<std::mutex> lock(db_mutex);
    return kv_store.find(key) != kv_store.end();
}

void StateDatabase::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(db_mutex);
    kv_store.erase(key);
}

void StateDatabase::commit_state() {
    std::lock_guard<std::mutex> lock(db_mutex);
    state_history[current_state_version] = kv_store;
    current_state_version++;
}

void StateDatabase::rollback_state(uint64_t version) {
    std::lock_guard<std::mutex> lock(db_mutex);
    if (state_history.find(version) != state_history.end()) {
        kv_store = state_history[version];
        current_state_version = version;
    }
}

std::vector<std::string> StateDatabase::get_all_keys() {
    std::lock_guard<std::mutex> lock(db_mutex);
    std::vector<std::string> keys;
    for (const auto& pair : kv_store) keys.push_back(pair.first);
    return keys;
}

void StateDatabase::clear_database() {
    std::lock_guard<std::mutex> lock(db_mutex);
    kv_store.clear();
    state_history.clear();
    current_state_version = 0;
}
