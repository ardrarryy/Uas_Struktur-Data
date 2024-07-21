#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Buku {
public:
    int id;
    string judul;
    string penulis;
    bool dipinjam;

    Buku(int id, string judul, string penulis) 
        : id(id), judul(judul), penulis(penulis), dipinjam(false) {}
};

class Perpustakaan {
private:
    vector<Buku> buku;
    int nextId = 1;

public:
    void tambahBuku(string judul, string penulis) {
        buku.push_back(Buku(nextId++, judul, penulis));
        cout << "Buku berhasil ditambahkan." << endl;
    }

    void lihatBuku() {
        cout << "+-----+------------------------------+--------------------+---------------+" << endl;
        cout << "| No  |" << setw(30) << center("Judul", 30) 
             << "|" << setw(20) << center("Penulis", 20) 
             << "|" << setw(14) << center("Status", 14) 
             << " |" << endl;
        cout << "+-----+------------------------------+--------------------+---------------+" << endl;
        for (const auto &b : buku) {
            cout << "| " << setw(3) << center(to_string(b.id), 3) 
                 << " | " << setw(28) << center(b.judul, 28) 
                 << " | " << setw(18) << center(b.penulis, 18) 
                 << " | " << setw(13) << center(b.dipinjam ? "Dipinjam" : "Tersedia", 13) 
                 << " |" << endl;
        }
        cout << "+-----+------------------------------+--------------------+---------------+" << endl;
    }

    void ubahBuku(int id, string judulBaru, string penulisBaru) {
        for (auto &b : buku) {
            if (b.id == id) {
                b.judul = judulBaru;
                b.penulis = penulisBaru;
                cout << "Buku berhasil diubah." << endl;
                return;
            }
        }
        cout << "Buku tidak ditemukan." << endl;
    }

    void hapusBuku(int id) {
        for (auto it = buku.begin(); it != buku.end(); ++it) {
            if (it->id == id) {
                buku.erase(it);
                cout << "Buku berhasil dihapus." << endl;
                return;
            }
        }
        cout << "Buku tidak ditemukan." << endl;
    }

    void pinjamBuku(int id) {
        for (auto &b : buku) {
            if (b.id == id && !b.dipinjam) {
                b.dipinjam = true;
                cout << "Buku berhasil dipinjam." << endl;
                return;
            }
        }
        cout << "Buku tidak tersedia atau tidak ditemukan." << endl;
    }

    void kembalikanBuku(int id) {
        for (auto &b : buku) {
            if (b.id == id && b.dipinjam) {
                b.dipinjam = false;
                cout << "Buku berhasil dikembalikan." << endl;
                return;
            }
        }
        cout << "Buku tidak ditemukan atau belum dipinjam." << endl;
    }

    string center(const string &str, int width) {
        int len = str.length();
        if (width <= len) {
            return str;
        }
        int pad_left = (width - len) / 2;
        int pad_right = width - len - pad_left;
        return string(pad_left, ' ') + str + string(pad_right, ' ');
    }
};

bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    // Contoh sederhana username dan password hardcoded
    if (username == "ardra" && password == "ardra123") {
        return true;
    } else {
        cout << "Username atau password salah." << endl;
        return false;
    }
}

void menuAdmin(Perpustakaan &perpustakaan) {
    int pilihan;
    do {
        cout << "+-----------------+" << endl;
        cout << "|    Menu Admin   |" << endl;
        cout << "+-----------------+" << endl;
        cout << "| 1. Tambah Buku  |" << endl;
        cout << "| 2. Lihat Buku   |" << endl;
        cout << "| 3. Ubah Buku    |" << endl;
        cout << "| 4. Hapus Buku   |" << endl;
        cout << "| 5. Keluar       |" << endl;
        cout << "+-----------------+" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            string judul, penulis;
            cout << "Masukkan judul: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan penulis: ";
            getline(cin, penulis);
            perpustakaan.tambahBuku(judul, penulis);
            break;
        }
        case 2:
            perpustakaan.lihatBuku();
            break;
        case 3: {
            int id;
            string judulBaru, penulisBaru;
            cout << "Masukkan ID buku yang akan diubah: ";
            cin >> id;
            cout << "Masukkan judul baru: ";
            cin.ignore();
            getline(cin, judulBaru);
            cout << "Masukkan penulis baru: ";
            getline(cin, penulisBaru);
            perpustakaan.ubahBuku(id, judulBaru, penulisBaru);
            break;
        }
        case 4: {
            int id;
            cout << "Masukkan ID buku yang akan dihapus: ";
            cin >> id;
            perpustakaan.hapusBuku(id);
            break;
        }
        case 5:
            cout << "Keluar dari Menu Admin.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 5);
}

void menuUser(Perpustakaan &perpustakaan) {
    int pilihan;
    do {
        cout << "+--------------------+" << endl;
        cout << "|   Menu Pengguna    |" << endl;
        cout << "+--------------------+" << endl;
        cout << "| 1. Lihat Buku      |" << endl;
        cout << "| 2. Pinjam Buku     |" << endl;
        cout << "| 3. Kembalikan Buku |" << endl;
        cout << "| 4. Keluar          |" << endl;
        cout << "+--------------------+" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            perpustakaan.lihatBuku();
            break;
        case 2: {
            int id;
            cout << "Masukkan ID buku yang akan dipinjam: ";
            cin >> id;
            perpustakaan.pinjamBuku(id);
            break;
        }
        case 3: {
            int id;
            cout << "Masukkan ID buku yang akan dikembalikan: ";
            cin >> id;
            perpustakaan.kembalikanBuku(id);
            break;
        }
        case 4:
            cout << "Keluar dari Menu Pengguna.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 4);
}

int main() {
    cout << "===========================================" << endl;
    cout << "|       Perpustakaan Ardra Rianisa        |" << endl;
    cout << "===========================================" << endl;

    Perpustakaan perpustakaan;
    int role;

    do {
        cout << "+--------------------------+" << endl;
        cout << "|   Sistem Perpustakaan    |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "| 1. Admin                 |" << endl;
        cout << "| 2. Pengguna              |" << endl;
        cout << "| 3. Keluar                |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "Masukkan pilihan: ";
        cin >> role;

        switch (role) {
        case 1:
            if (loginAdmin()) {
                menuAdmin(perpustakaan);
            }
            break;
        case 2:
            menuUser(perpustakaan);
            break;
        case 3:
            cout << "Keluar dari Sistem Perpustakaan.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (role != 3);

    return 0;
}