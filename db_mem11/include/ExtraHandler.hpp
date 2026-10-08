#pragma once
#include <iostream>
#include <nlohmann/json.hpp> // JSONライブラリ

//#include "MemDatabase.hpp"
//using json = nlohmann::json;

class ExtraHandler {
private:
    std::string m_name;

public:
    explicit ExtraHandler(std::string str){}
    ~ExtraHandler() {}

    std::string handler(sqlite3* db, std::string action_name, std::string sql)
    {
        std::string ret = "";
        return ret;
    }
};
