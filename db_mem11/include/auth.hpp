#pragma once
#include <string>
#include <optional>
#include <sodium.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

class Auth {
public:
    explicit Auth(std::string str){}
    ~Auth() {}
   
    bool hashPassword(const std::string& password, std::string& hash) {
        if (sodium_init() < 0) {
            std::cerr << "Failed to initialize libsodium" << std::endl;
            return false;
        }
        
        // ソルトを生成
        unsigned char salt[crypto_pwhash_SALTBYTES];
        randombytes_buf(salt, sizeof(salt));
        
        // ハッシュを生成
        char hashed_password[crypto_pwhash_STRBYTES];
        
        if (crypto_pwhash_str(hashed_password, password.c_str(), password.length(),
                              crypto_pwhash_OPSLIMIT_SENSITIVE,
                              crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
            std::cerr << "Password hashing failed" << std::endl;
            return false;
        }
        
        hash = std::string(reinterpret_cast<char*>(hashed_password));
        return true;
    }

    bool verifyPassword(const std::string& password, const std::string& hash) {
        if (sodium_init() < 0) {
            std::cerr << "Failed to initialize libsodium" << std::endl;
            return false;
        }
        
        return crypto_pwhash_str_verify(hash.c_str(), password.c_str(), password.length()) == 0;
    }    

    std::string generateSalt() {
        unsigned char salt[crypto_pwhash_SALTBYTES];
        randombytes_buf(salt, sizeof(salt));
        
        std::stringstream ss;
        for (size_t i = 0; i < sizeof(salt); ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(salt[i]);
        }
        return ss.str();
    }    
};