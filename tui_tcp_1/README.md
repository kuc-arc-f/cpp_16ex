# tui_tcp_1

 Version: 0.9.1

 date    : 2026/09/11
 
 update :

***

C++ , DB client TUI

* gcc
* node 22
* make

***
## Image

![img1](/images/tui_tcp_1.png)

***
### DB TCP Server

https://github.com/kuc-arc-f/cpp_db_server_tcp

***
* Server info
* server_ip: 127.0.0.1
* port: 8888;

**** 
build
```
make all
```

***
* node

```
pnpm i
npm run start
```

***
* TestCode example
* update
```
update:INSERT INTO todos (title) VALUES ('title_11_7');
```
***
* select
```
select:todos
select:todos:SELECT COUNT(*) FROM todos;
select:todos:SELECT * FROM todos ORDER BY id DESC LIMIT 3;
select:todos:SELECT id , title FROM todos ORDER BY id DESC LIMIT 3;
select:todos:SELECT id , title FROM todos WHERE id = 12295;
```
***
### blog

https://zenn.dev/link/comments/b2b12586d23656

***