#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

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
        memset(&server_addr, 0, sizeof(server_addr));
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
        
        // データ送信: 部分送信(partial write)に対応するためループで全バイト送信
        size_t total_sent = 0;
        size_t to_send = message.length();
        while (total_sent < to_send) {
            ssize_t n = write(sock_fd, message.c_str() + total_sent, to_send - total_sent);
            if (n < 0) {
                if (errno == EINTR) continue;
                std::cerr << "送信エラー: " << strerror(errno) << std::endl;
                return false;
            }
            if (n == 0) break;
            total_sent += n;
        }
        
        std::cout << "送信: " << message;

        // 応答受信: サーバーからのデータが1024バイトを超える場合でも全て受信するためループ処理
        //  - 最初はブロッキングreadで応答を待つ
        //  - 以降はselect + 短時間タイムアウトで残りデータを全て回収
        std::string response;
        char buffer[4096];

        ssize_t bytes_read = read(sock_fd, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                std::cerr << "接続が切断されました" << std::endl;
            } else {
                std::cerr << "受信エラー: " << strerror(errno) << std::endl;
            }
            return false;
        }
        response.append(buffer, bytes_read);

        // 追加データが到着している間は全て読み取る
        // サーバーが複数TCPパケットに分割して送信した場合に対応
        while (true) {
            fd_set read_fds;
            FD_ZERO(&read_fds);
            FD_SET(sock_fd, &read_fds);

            // 200ms以内に追加データが来なければメッセージ終端とみなす
            // 継続的なストリームではなくリクエスト-レスポンス型を想定
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 200 * 1000; // 200ms

            int sel = select(sock_fd + 1, &read_fds, nullptr, nullptr, &tv);
            if (sel < 0) {
                if (errno == EINTR) continue;
                std::cerr << "selectエラー: " << strerror(errno) << std::endl;
                break;
            }
            if (sel == 0) {
                // タイムアウト = 追加データなし、受信完了
                break;
            }
            if (!FD_ISSET(sock_fd, &read_fds)) {
                break;
            }

            bytes_read = read(sock_fd, buffer, sizeof(buffer));
            if (bytes_read < 0) {
                if (errno == EINTR) continue;
                if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                std::cerr << "受信エラー: " << strerror(errno) << std::endl;
                return false;
            }
            if (bytes_read == 0) {
                // サーバー側が切断
                break;
            }
            response.append(buffer, bytes_read);
            // バッファサイズより小さくてもTCP分割の可能性があるため継続してselectで確認
        }
        
        std::cout << "応答 (" << response.size() << " bytes): " << response;
        // 末尾に改行がなければ追加
        if (!response.empty() && response.back() != '\n') {
            std::cout << std::endl;
        }
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
    
    TCPClient client(server_ip, port);
    if (!client.connect()) {
        return 1;
    }
    
    // インタラクティブモード
    std::cout << "メッセージを入力 (終了は 'quit' または 'exit')" << std::endl;
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit" || input == "q") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        // 改行を追加
        input += "\n";
        if (!client.sendMessage(input)) {
            break;
        }
    }
    
    return 0;
}