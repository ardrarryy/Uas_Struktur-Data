#include "library.h"
#include <iostream>

void createTable(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "title TEXT NOT NULL, "
                      "author TEXT NOT NULL, "
                      "year INTEGER NOT NULL);";
    char* errmsg;
    if (sqlite3_exec(db, sql, 0, 0, &errmsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }
}

void adminMenu(sqlite3* db) {
    while (true) {
        std::cout << "\nAdmin Menu\n";
        std::cout << "1. Tambah Buku\n";
        std::cout << "2. Lihat Buku\n";
        std::cout << "3. Perbarui Buku\n";
        std::cout << "4. Hapus Buku\n";
        std::cout << "5. Keluar\n";
        std::cout << "Masukkan pilihan: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string title, author;
            int year;
            std::cout << "Masukkan judul buku: ";
            std::cin >> title;
            std::cout << "Masukkan penulis buku: ";
            std::cin >> author;
            std::cout << "Masukkan tahun terbit: ";
            std::cin >> year;
            createBook(db, title, author, year);
        } else if (choice == 2) {
            readBooks(db);
        } else if (choice == 3) {
            int bookId;
            std::string title, author;
            int year;
            std::cout << "Masukkan ID buku yang ingin diperbarui: ";
            std::cin >> bookId;
            std::cout << "Masukkan judul buku baru: ";
            std::cin >> title;
            std::cout << "Masukkan penulis buku baru: ";
            std::cin >> author;
            std::cout << "Masukkan tahun terbit baru: ";
            std::cin >> year;
            updateBook(db, bookId, title, author, year);
        } else if (choice == 4) {
            int bookId;
            std::cout << "Masukkan ID buku yang ingin dihapus: ";
            std::cin >> bookId;
            deleteBook(db, bookId);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    }
}

void userMenu(sqlite3* db) {
    while (true) {
        std::cout << "\nUser Menu\n";
        std::cout << "1. Lihat Buku\n";
        std::cout << "2. Keluar\n";
        std::cout << "Masukkan pilihan: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            readBooks(db);
        } else if (choice == 2) {
            break;
        } else {
            std::cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    }
}

void mainMenu(sqlite3* db) {
    while (true) {
        std::cout << "\nMain Menu\n";
        std::cout << "1. Admin\n";
        std::cout << "2. User\n";
        std::cout << "3. Keluar\n";
        std::cout << "Masukkan pilihan: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            adminMenu(db);
        } else if (choice == 2) {
            userMenu(db);
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    }
}

int main() {
    sqlite3* db = openDatabase("library.db");
    if (db) {
        createTable(db);
        mainMenu(db);
        closeDatabase(db);
    }
    return 0;
}