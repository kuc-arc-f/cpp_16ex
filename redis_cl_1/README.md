# redis_cl_1

 Version: 0.9.1

 date    : 2026/09/27
 
 update :

***

C++ RAG CLI , Vector add search Jev

* Redis database
* TypeSafe Jev
* llama-server : Qwen3-Embedding-0.6B
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
* llama-server
```
/usr/local/llama-b8951/llama-server -m /var/lm_data/qwen/Qwen3-Embedding-0.6B-Q8_0.gguf --embedding  -c 1024 --port 8080
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
* PREFIX_KEY: redis data type

```
PREFIX_KEY=doc1:
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
