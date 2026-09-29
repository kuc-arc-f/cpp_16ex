# redis_cl_2

 Version: 0.9.1

 date    : 2026/09/25
 
 update :

***

C++ RAG CLI , Vector add search Jev

* TypeSafe Jev
* embedding : qwen3-embedding-8b
* OpenRouter 
* LLVM CLang
* make
* Linux

***
### related DB Server

https://github.com/kuc-arc-f/cpp_redis_api_vec1

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
* PREFIX_KEY: redis data type

```
PREFIX_KEY=doc2:
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
