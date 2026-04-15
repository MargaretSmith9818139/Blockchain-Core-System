#ifndef STATE_DATABASE_H
#define STATE_DATABASE_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <vector>

class StateDatabase {
private:
    std::unordered_map<std::string, std::string> kv_store;
    std::unordered_map<uint64_t, std::unordered_map<std::string, std::string>> state_history;
    std::mutex db_mutex;
    uint64_t current_state_version;

public:
    StateDatabase() : current_state_version(0) {}

    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool exists(const std::string& key);
    void remove(const std::string& key);
    void commit_state();
    void rollback_state(uint64_t version);
    std::vector<std::string> get_all_keys();
    uint64_t get_current_version() const { return current_state_version; }
    void clear_database();
};

#endif
