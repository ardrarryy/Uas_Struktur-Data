#ifndef LIBRARY_H
#define LIBRARY_H

#include <sqlite3.h>
#include <string>

void createBook(sqlite3* db, const std::string& title, const std::string& author, int year);
void readBooks(sqlite3* db);
void updateBook(sqlite3* db, int bookId, const std::string& title, const std::string& author, int year);
void deleteBook(sqlite3* db, int bookId);
sqlite3* openDatabase(const char* filename);
void closeDatabase(sqlite3* db);

#endif