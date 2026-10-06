DROP TABLE IF EXISTS task_item;
CREATE TABLE "task_item" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME,
    "projectId" INTEGER,
    "title" TEXT,
    "content" TEXT,
    "complete" DATETIME,
    "start_date" DATETIME,
    "userId" INTEGER,
    "status" TEXT
);
DROP TABLE IF EXISTS project;
CREATE TABLE "project" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME,
    "name" TEXT,
    "InveiteCode" TEXT,
    "userId" INTEGER
);

-- CreateTable
CREATE TABLE IF NOT EXISTS "Chat" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NULL,
    "name" TEXT,
    "content" TEXT,
    "userId" INTEGER
);

CREATE TABLE IF NOT EXISTS "ChatPost" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NULL,
    "chatId" INTEGER,
    "userId" INTEGER,
    "title" TEXT,
    "body" TEXT
);

CREATE TABLE IF NOT EXISTS "Thread" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NULL,
    "chatId" INTEGER,
    "chatPostId" INTEGER,
    "userId" INTEGER,
    "title" TEXT,
    "body" TEXT
);

CREATE TABLE IF NOT EXISTS "BookMark" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NULL,
    "chatId" INTEGER,
    "chatPostId" INTEGER,
    "userId" INTEGER
);

CREATE TABLE IF NOT EXISTS "User" (
    "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    "createdAt" DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updatedAt" DATETIME NULL,
    "password" TEXT NOT NULL,
    "email" TEXT NOT NULL,
    "name" TEXT
);

-- CreateIndex
CREATE UNIQUE INDEX "User_email_key" ON "User"("email");
