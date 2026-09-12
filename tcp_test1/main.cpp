#include <chrono>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>

// JSON用エイリアス
using json = nlohmann::json;

struct QueryReq {
    std::string action_name;
    std::string table;
    std::string sql;
};
// struct <=> json の変換が魔法のように可能になります
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueryReq, action_name, table, sql)

class TCPClient {
private:
    int sock_fd;
    std::string server_ip;
    int port;
    bool connected;
    
public:
    TCPClient(const std::string& ip, int port) : server_ip(ip), port(port), connected(false) {
        sock_fd = -1;
    }
    
    ~TCPClient() {
        disconnect();
    }
    
    bool connect() {
        // ソケット作成
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd < 0) {
            std::cerr << "ソケット作成失敗" << std::endl;
            return false;
        }
        
        // サーバーアドレス設定
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        
        if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
            std::cerr << "無効なIPアドレス" << std::endl;
            close(sock_fd);
            return false;
        }
        
        // サーバーに接続
        if (::connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "接続失敗" << std::endl;
            close(sock_fd);
            return false;
        }
        
        connected = true;
        std::cout << "サーバー接続成功: " << server_ip << ":" << port << std::endl;
        return true;
    }
    
    void disconnect() {
        connected = false;
        if (sock_fd >= 0) {
            close(sock_fd);
            sock_fd = -1;
        }
        std::cout << "切断しました" << std::endl;
    }
    
    bool sendMessage(const std::string& message) {
        if (!connected) {
            std::cerr << "未接続です" << std::endl;
            return false;
        }
        
        // データ送信
        int bytes_sent = write(sock_fd, message.c_str(), message.length());
        if (bytes_sent < 0) {
            std::cerr << "送信エラー" << std::endl;
            return false;
        }        
        //std::cout << "送信: " << message;
        // 応答受信
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        
        int bytes_read = read(sock_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            std::cerr << "受信エラー" << std::endl;
            return false;
        }
        //std::cout << "応答: " << buffer;
        return true;
    }
};

int main(int argc, char* argv[]) {
    std::string server_ip = "127.0.0.1";
    int port = 8080;
    
    if (argc > 1) {
        server_ip = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
    }
    // 開始時刻
    auto start = std::chrono::high_resolution_clock::now();
    
    TCPClient client(server_ip, port);
    try{    
        if (!client.connect()) {
            return 1;
        }
        for(int i = 0; i < 1000; i++) {
            std::string str_num = std::to_string(i);
            QueryReq req;
            req.action_name = "update";
            req.table = "todos";
            req.sql = "INSERT INTO todos (title) VALUES ('title_" + str_num + "');";        
            json j = req;
            std::string json_str = j.dump();

            bool ok = client.sendMessage(json_str);
            if(ok == false){
                return -1;
            }
        }
        client.disconnect();
        auto end = std::chrono::high_resolution_clock::now();
        // 差分（ミリ秒）
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "time: " << duration.count() << " ms" << std::endl;        
    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] " << e.what() << std::endl;
        return 0;
    }
   
    return 0;
}