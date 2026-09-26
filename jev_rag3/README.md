# jev_rag3

 Version: 0.9.1

 date    : 2026/09/25
 
 update :

***

C++ TUI , Jev RAG Search

* TypeSafe Jev
* llama-server (llama.cpp) Qwen3-Embedding-0.6B-Q8_0.gguf
* OpenRouter 
* LLVM CLang
* make
* node 22
* Linux

***
### related DB Server

https://github.com/kuc-arc-f/cpp_vec_server_db1

***
* llama-server

```
/usr/local/llama-b8951/llama-server -m /var/lm_data/qwen/Qwen3-Embedding-0.6B-Q8_0.gguf --embedding  -c 1024 --port 8080
```

***
* LIB

```
sudo apt update
sudo apt install uuid-dev
sudo apt install nlohmann-json3-dev
sudo apt install libcurl4-openssl-dev
```
***
* build
```
make all
```
***
* embed build
```
clang++ -std=c++17 -I./include -o embed embed.cpp -lcurl
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
* node start
```
pnpm i
npm run start
```
***
