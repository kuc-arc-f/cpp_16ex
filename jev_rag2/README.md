# jev_rag2

 Version: 0.9.1

 date    : 2026/09/25
 
 update :

***

C++ TUI , Jev RAG Search

* TypeSafe Jev
* embedding : qwen3-embedding-8b
* OpenRouter 
* LLVM CLang
* make
* Linux

***
## Image

* TUI RAG APP

![img1](/images/jev_rag2.png)


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
* build
```
make all
```

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
