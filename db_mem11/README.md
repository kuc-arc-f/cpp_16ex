# db_mem11

 Version: 0.9.1

 date    : 2026/10/05
 
 update :

***

C++ DB Server Rest API , memory Database , Task App

* LLVM CLang
* cpp-httplib
* sqlite3 use

***
### related DB server

https://github.com/kuc-arc-f/cpp_db_mem_rest

***
* LIB add
```
sudo apt update
sudo apt-get install libsqlite3-dev
sudo apt-get install nlohmann-json3-dev
sudo apt install libspdlog-dev libfmt-dev
```

***
* table add
```
sqlite3 ./data/backup.db < table.sql
```

***
* Table: ./task.sql
* create table , sqlite3 use
```
sqlite3 ./data/backup.db
```
***
* build
```
make all
```

* start , localhost:8888

```
./start.sh
```

***
### blog

