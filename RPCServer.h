#ifndef RPC_SERVER_H
#define RPC_SERVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

class RPCServer {
private:
    uint16_t port;
    bool is_running;
    std::unordered_map<std::string, std::function<std::string(const std::vector<std::string>&)>> handlers;

    void register_default_handlers();
    std::string handle_hello(const std::vector<std::string>& params);
    std::string handle_balance(const std::vector<std::string>& params);
    std::string handle_height(const std::vector<std::string>& params);

public:
    RPCServer(uint16_t p) : port(p), is_running(false) {
        register_default_handlers();
    }

    void start_server();
    void stop_server();
    void register_handler(const std::string& method, std::function<std::string(const std::vector<std::string>&)> func);
    std::string execute_rpc(const std::string& method, const std::vector<std::string>& params);

    uint16_t get_port() const { return port; }
    bool is_server_running() const { return is_running; }
};

#endif
