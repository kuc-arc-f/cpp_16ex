#pragma once
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "models.hpp"
#include "EmbeddingClient.hpp"
#include "my_config.hpp"
#include "openrouter_client.hpp"
#include "HttpClient.hpp"
#include "JevClient.hpp"

using json = nlohmann::json;

const std::string DB_PATH = "example.db";
const std::string DATA_PATH = "./data";
std::string TABLE_NAME = "document";
std::string API_URL_BASE = "http://localhost:8888";

// 1ファイル分のデータを保持する構造体
struct TextFile {
    std::string filename;
    std::vector<std::string> lines;
};

// .txt ファイルを読み込んで行を返す
TextFile loadTextFile(const std::filesystem::path& filepath) {
    TextFile tf;
    tf.filename = filepath.filename().string();

    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "[警告] ファイルを開けません: " << filepath << "\n";
        return tf;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        tf.lines.push_back(line);
    }
    return tf;
}

class MyRag {
private:
    std::string m_name;

    public:
    explicit MyRag(std::string str){}

    ~MyRag() {}

    std::string llm_search(std::string query, std::string input){
        std::string ret = "";
        try{
            // API_KEYを環境変数から取得（または直接設定）
            const char* api_key = std::getenv("OPENROUTER_API_KEY");
            if (api_key != nullptr) {
                //std::cout << "api_key:" << api_key << std::endl;
            }else{
                std::cerr << "Error: OPENROUTER_API_KEY environment variable not set" << std::endl;
                std::cerr << "Please set it with: export OPENROUTER_API_KEY=your_api_key_here" << std::endl;
                return ret;
            }      
            const char* model_name = std::getenv("OPENROUTER_MODEL");
            if (!model_name) {
                std::cerr << "Error: OPENROUTER_MODEL environment variable not set" << std::endl;
                return ret;
            }          
            std::string resp_str= input;
            std::string out_str = "日本語で、回答して欲しい。 \n要約して欲しい。\n\n";
            if(resp_str.empty()){
                out_str.append("user query: ");
                out_str.append(query);
                out_str.append(" \n");
            }else{
                out_str.append("context:");
                out_str.append(resp_str);
                out_str.append("\n user query: ");
                out_str.append(query);
                out_str.append(" \n");
            }                    
            //std::cout << out_str  << std::endl; 
            OpenRouterClient client(api_key);
            auto response = client.sendChatCompletion(
                model_name,
                out_str,
                1.0,
                2000
            );

            if (response.has_value()) {
                //std::cout << "Response: " << response.value() << std::endl;
                auto outStr = response.value();
                ret = outStr;
                return ret;
            } else {
                std::cerr << "Failed to get response from API" << std::endl;
                return ret;
            }

            return ret;
        } catch (const std::exception& e) {
            std::cout << "Error , main" << std::endl;
        } 
        return ret; 
    }    

    std::string get_max_score(std::string json_str ){
        std::string ret = "";
        try{    
            json j = json::parse(json_str);

            // probabilities を取得
            const auto& probabilities = j.at("answers").at("document").at("probabilities");
            const auto& legend = j.at("answers").at("document").at("legend");

            std::cout << "--- 最大確率のラベル ---" << std::endl;
            std::string best_key;
            double best_prob = -1.0;
            for (auto it = probabilities.begin(); it != probabilities.end(); ++it) {
                double p = it.value().get<double>();
                if (p > best_prob) {
                    best_prob = p;
                    best_key = it.key();
                }
            }
            std::string outStr = legend.at(best_key).get<std::string>();
            //std::cout << "Best: " << outStr
            //          << " (" << best_prob << ")" << std::endl;
            return outStr;
        } catch (const json::exception& e) {
            std::cerr << "JSON error: " << e.what() << std::endl;
        }
        return ret;
    }

    std::string get_jev_item(
        std::string api_key, std::vector<std::string> vec, std::string query)
    {
        std::string ret = "";
        curl_global_init(CURL_GLOBAL_DEFAULT);
        try {
            json body = {
                {"model", "typesafe/jev-1.13"},
                {"state", {
                    {"document", "似ている文章を探して欲しい。"}
                }},
                {"questions", {
                    {"document", {
                        {"type", "score"},
                        {"instructions", query},
                        {
                        "criteria", vec
                        }
                    }}
                }}
            };
            //std::cout << "body=" << body << std::endl;  
            JevClient jLib("");          
            const std::string resp = jLib.http_post_json(
                "https://openrouter.ai/api/alpha/decisions",
                api_key,
                body);

            // レスポンスをパースして表示
            json parsed = json::parse(resp);
            std::cout << parsed.dump(2) << std::endl;

            std::string outStr = get_max_score(resp);
            std::cout << "outStr=" <<  outStr << std::endl;
            return outStr;
        } catch (const std::exception& e) {
            std::cerr << "get_jev_item Error: " << e.what() << std::endl;
            curl_global_cleanup();
            return ret;
        }
        curl_global_cleanup();    
        return ret;
    }    

    std::string rag_search(std::string query){
        std::string ret = "";
        try{
            // API_KEYを環境変数から取得（または直接設定）
            const char* api_key = std::getenv("OPENROUTER_API_KEY");
            if (api_key != nullptr) {
                //std::cout << "api_key:" << api_key << std::endl;
            }else{
                std::cerr << "Error: OPENROUTER_API_KEY environment variable not set" << std::endl;
                std::cerr << "Please set it with: export OPENROUTER_API_KEY=your_api_key_here" << std::endl;
                return ret;
            }      
            const char* model_name = std::getenv("OPENROUTER_MODEL");
            if (!model_name) {
                std::cerr << "Error: OPENROUTER_MODEL environment variable not set" << std::endl;
                return ret;
            }      

            //std::string dirPath = DATA_PATH;
            auto embeddings = EmbeddingStart(query);
            //std::cout << "vlen=" << embeddings.size() << std::endl;
            auto vec = embeddings;
            std::stringstream ss;
            ss << "[";
            for (size_t i = 0; i < embeddings.size(); ++i) {
                if (i > 0) ss << ",";
                ss << embeddings[i];
            }
            ss << "]";
            std::string emb_str = ss.str();  
            std::string res1 = emb_str.substr(0, 40);      
            std::cout << "res1=" << res1 << std::endl;
            VectorSearchReq req1;
            req1.table = TABLE_NAME;
            req1.limit = 3;
            req1.vector = emb_str;
            json j1 = req1; // 構造体を代入するだけ！
            std::string json_str = j1.dump();
            //std::cout << json_str << std::endl;

            HttpClient htClient(30 /*timeout*/, true /*verify_ssl*/);         
            std::string url = API_URL_BASE + "/api/select";

            auto resp = htClient.post_json(url, json_str);
            json j2 = json::parse(resp.body);
            std::string data = j2.at("data").get<std::string>();
            //std::cout << "data=" << data << "\n";        
            json j3 = json::parse(data);
            std::cout << "j3.size=" << j3.size() << "\n";

            std::string content = "";
            if (j3.size() == 1){
                content = j3[0].at("content").get<std::string>();
            }
            // Jev score
            std::vector<std::string> vecJev;
            if(j3.size() >=2){
                for(int i=0; i < j3.size(); i++) {
                    std::string row = j3[i].at("content").get<std::string>();
                    vecJev.push_back(row);
                }
                content = get_jev_item(api_key, vecJev, query);
            }
            //std::cout << "content=" << content << "\n"; 

            std::string out_str = "日本語で、回答して欲しい。 \n要約して欲しい。\n\n";
            if(content.empty()){
                out_str.append("user query: ");
                out_str.append(query);
                out_str.append(" \n");
            }else{
                out_str.append("context:");
                out_str.append(content);
                out_str.append("\n user query: ");
                out_str.append(query);
                out_str.append(" \n");
            }
            //std::cout << "out_str=" << out_str  << std::endl;
            OpenRouterClient client(api_key);
            auto response = client.sendChatCompletion(
                model_name,
                out_str,
                1.0,
                2000
            );

            if (response.has_value()) {
                //std::cout << "AI: " << response.value() << std::endl;
                ret = response.value();
                return ret;
            } else {
                std::cerr << "Failed to get response from API" << std::endl;
                return ret;
            }            
            return ret;
        } catch (const std::exception& e) {
            std::cout << "Error , main" << std::endl;
        }  
        return ret;        
    }
};
