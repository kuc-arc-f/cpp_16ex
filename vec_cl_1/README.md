# vec_cl_1

 Version: 0.9.1

 date    : 2026/09/23
 
 update :

***

C++ , RAG CLI vector add ,search

* embedding : qwen3-embedding-8b
* OpenRouter 
* LLVM CLang
* make
* Linux

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
