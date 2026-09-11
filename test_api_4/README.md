# test_api_4

 Version: 0.9.1

 date    : 2026/09/09
 
 update :

***

C++ Crow , API Server

* LLVM CLang
* Crow web
* TCP Client

***
### related DB Server

https://github.com/kuc-arc-f/cpp_db_server_tcp

***
### related

https://github.com/CrowCpp/Crow

https://crowcpp.org/master/

https://crowcpp.org/master/getting_started/setup/linux/

***
* DB SERVER info
* SERVER_IP: 127.0.0.1
* TCP_PORT: 8888

***
* LIB add
```
sudo apt install uuid-dev
sudo apt-get install nlohmann-json3-dev
```

***
* build

```
clang++ -std=c++17 main.cpp -o server -lpthread -luuid

#start
./server
```

***
* Test-code
* update
```
curl -X POST http://localhost:8080/api/update \
  -H "Content-Type: application/json" \
  -d "{\"action_name\":\"update\" , \"table\": \"todos\",\"sql\":\"INSERT INTO todos (title) VALUES ('title_1');\"}"
  
```

* SELECT
```
curl -X POST http://localhost:8080/api/select \
  -H "Content-Type: application/json" \
  -d "{\"action_name\":\"select\" , \"table\": \"todos\",\"sql\":\"SELECT * FROM todos;\"}"

```
***

