# vec_cl_4

 Version: 0.9.1

 date    : 2026/09/25
 
 update :

***

C++ RAG CLI , vector add search Jev

* TypeSafe Jev
* embedding : qwen3-embedding-8b
* OpenRouter 
* LLVM CLang
* make
* Linux

***
### related DB Server

https://github.com/kuc-arc-f/cpp_vec_server_db1

***
* LIB

```
sudo apt update
sudo apt install uuid-dev
sudo apt install nlohmann-json3-dev
sudo apt install libcurl4-openssl-dev
```
***
* embed build
```
clang++ -std=c++17 -I./include -o embed embed.cpp -lcurl
```
* search
```
clang++ -std=c++17 -I./include -o search search.cpp -lcurl
```
***
* .env
```
OPENROUTER_API_KEY=
OPENROUTER_MODEL=deepseek/deepseek-v4-flash
```
***
* vector data add
```
./embed ./data
```
***
* search start
```
./search hello
```
***
### blog

https://zenn.dev/knaka0209/scraps/0530606d0dbeca

