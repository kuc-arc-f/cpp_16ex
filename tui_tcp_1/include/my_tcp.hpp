#pragma once
#include <iostream>
#include "tcp_client.hpp"

class MyTcp {
private:
    std::string m_name = "";
public:
    explicit MyTcp(std::string str){}
    ~MyTcp() {}
    
    std::string sendMessage(const std::string& input) {
      std::string ret = "";

      std::string server_ip = "127.0.0.1";
      int port = 8888;

      if (input.empty()) {
          return ret;
      }      

      TCPClient client(server_ip, port);
      if (!client.connect()) {
          return ret;
      }
      ret = client.sendMessage(input);      

      return ret;
    }
};
