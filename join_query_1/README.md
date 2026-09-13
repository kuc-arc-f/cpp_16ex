# join_query_1

 Version: 0.9.1

 date    : 2026/09/09
 
 update :

***

C++ DB Server, join query example

* LLVM CLang

***
### related Client TCP

https://github.com/kuc-arc-f/cpp_16ex/tree/main/tcp_cl_2

***
* LIB add
```
sudo apt-get install libsqlite3-dev
sudo apt-get install nlohmann-json3-dev
```
***
* table-add
```
sqlite3 ./data/backup.db < table.sql
```
***
* table :josin_test.sql

***
* build
```
clang++ -std=c++11 -pthread tcp_server.cpp -o tcp_server -lsqlite3 -luuid
```

* start
```
./start.sh
```

***
* tcp-client
* input json data
```
{"action_name": "select_ex2", "sql":"SELECT depts.id, buy_items.name from  depts LEFT OUTER JOIN buy_items  ON depts.id = buy_items.dept_id WHERE depts.id = 1;"}
```
***
### blog

https://zenn.dev/link/comments/66178626aaf17a

