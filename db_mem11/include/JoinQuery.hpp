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

    json ex_json_list(
      sqlite3* db, std::vector<std::string> columnNames, const std::string& sql 
    ) {
        json result;
        result["status"] = "success";

        std::cout << "selectTableSql.sql=" << sql << "\n";            

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            result["status"] = "error";
            result["error"] = sqlite3_errmsg(db);
            return result;
        }
        int columnCount = columnNames.size();

        // データ行を取得
        json rows = json::array();

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json row;

            for (int i = 0; i < columnCount; i++) {
                const std::string colName = columnNames[i];
                int colType = sqlite3_column_type(stmt, i);
                //std::cout << "colName=" << colName << std::endl;
                //std::cout << "colType=" << colType << std::endl;
                switch (colType) {
                    case SQLITE_INTEGER:
                        row[colName] = sqlite3_column_int64(stmt, i);
                        break;
                    case SQLITE_FLOAT:
                        row[colName] = sqlite3_column_double(stmt, i);
                        break;
                    case SQLITE_TEXT:
                        row[colName] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                        break;
                    case SQLITE_BLOB:
                        // BLOBデータはBase64などに変換するか、文字列として扱う
                        row[colName] = "[BLOBデータ]";
                        break;
                    case SQLITE_NULL:
                    default:
                        row[colName] = nullptr;
                        break;
                }
            }
            rows.push_back(row);
        }

        sqlite3_finalize(stmt);

        result["columns"] = columnNames;
        result["row_count"] = rows.size();
        result["data"] = rows;

        return result;
    }

    json ex_select_chat_post_list(sqlite3* db, const std::string& sql ) {
        //json result;
        std::vector<std::string> columnNames;
        columnNames.push_back("id");
        columnNames.push_back("chatId");
        columnNames.push_back("userId");
        columnNames.push_back("title");
        columnNames.push_back("body");
        columnNames.push_back("createdAt");
        columnNames.push_back("updatedAt");
        columnNames.push_back("name");

        json result= ex_json_list(db ,columnNames, sql );
        return result;
    }

    json ex_select_chat_thread_list(sqlite3* db, const std::string& sql ) {
        json result;
        std::vector<std::string> columnNames;
        columnNames.push_back("id");
        columnNames.push_back("chatId");
        columnNames.push_back("chatPostId");
        columnNames.push_back("userId");
        columnNames.push_back("title");
        columnNames.push_back("body");
        columnNames.push_back("createdAt");
        columnNames.push_back("updatedAt");
        columnNames.push_back("name");
        result= ex_json_list(db , columnNames, sql );
        return result;
    }    

};