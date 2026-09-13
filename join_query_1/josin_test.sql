CREATE TABLE depts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE buy_items (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    dept_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

---
INSERT INTO depts(name) VALUES('busyo_1');
INSERT INTO depts(name) VALUES('busyo_2');

INSERT INTO buy_items(dept_id, name)VALUES(1, 'coffee');
INSERT INTO buy_items(dept_id, name)VALUES(2, 'green-tea');
