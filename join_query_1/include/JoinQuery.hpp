#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class JoinQuery {
private:
  std::string m_name = "";

public:
    JoinQuery(const std::string& name) {}    
    ~JoinQuery() {
    }    

    std::string selectExJson(sqlite3* db, std::string in_sql) {
        std::stringstream json;
        std::cout << "in_sql=" << in_sql << std::endl;

        json << "[";
        
        const char* sql = in_sql.c_str();
        sqlite3_stmt* stmt;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            return "[]";
        }
        
        bool first = true;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (!first) json << ",";
            first = false;
            
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* buy_item_name = sqlite3_column_text(stmt, 1);
            
            json << "{"
                 << "\"dept_id\":" << id << ","
                 << "\"buy_item_name\":\"" << (buy_item_name ? reinterpret_cast<const char*>(buy_item_name) : "") << "\""
                 << "}";
        }
        
        sqlite3_finalize(stmt);
        json << "]";
        return json.str();
    }
};