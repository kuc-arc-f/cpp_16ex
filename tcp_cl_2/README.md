# tcp_cl_2

 Version: 0.9.1

 date    : 2026/09/09
 
 update :

***

C++ TCP client , CLI

* gcc

***
* build
```
g++ -std=c++11 tcp_client.cpp -o tcp_client
```

* start
```
./tcp_client 127.0.0.1 8888
```

***
* TestCode
* update
```
{"action_name": "update", "table":"temp","sql":"INSERT INTO temp (title) VALUES ('title1');"}
```
* select
```
{"action_name": "select", "table":"temp","sql":"SELECT * FROM temp;"}
```
***
* TestCode : node - select
* ./test1.js

```
node test1.js
```

***