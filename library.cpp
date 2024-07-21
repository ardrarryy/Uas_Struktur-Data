#include "library.h"
#include <iostream>

sqlite3* openDatabase(const char* filename) {
    sqlite3* db;
    if (sqlite3_open(filename, &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return db;
}

void closeDatabase(sqlite3* db) {
    sqlite3_close(db);
}

void createBook(sqlite3* db, const std::string& title, const std::string& author, int year) {
    std::string sql = "INSERT INTO books (title, author, year) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, year);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void readBooks(sqlite3* db) {
    std::string sql = "SELECT * FROM books;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* title = sqlite3_column_text(stmt, 1);
        const unsigned char* author = sqlite3_column_text(stmt, 2);
        int year = sqlite3_column_int(stmt, 3);
        std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Year: " << year << std::endl;
    }
    sqlite3_finalize(stmt);
}

void updateBook(sqlite3* db, int bookId, const std::string& title, const std::string& author, int year) {
    std::string sql = "UPDATE books SET title = ?, author = ?, year = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, year);
    sqlite3_bind_int(stmt, 4, bookId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void deleteBook(sqlite3* db, int bookId) {
    std::string sql = "DELETE FROM books WHERE id = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, bookId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}