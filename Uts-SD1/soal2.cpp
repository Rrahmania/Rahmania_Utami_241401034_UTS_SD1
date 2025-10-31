#include <iostream>
#include <string>
using namespace std;

// Struktur untuk node linked list
struct Film {
    string judul;
    int tahun;
    int rating;
    Film* next;
};

// Kelas untuk mengelola linked list film
class DaftarFilm {
private:
    Film* head;

public:
    DaftarFilm() {
        head = nullptr;
    }

    // Tambah film di belakang
    void tambahFilm(string judul, int tahun, int rating) {
        Film* filmBaru = new Film;
        filmBaru->judul = judul;
        filmBaru->tahun = tahun;
        filmBaru->rating = rating;
        filmBaru->next = nullptr; 

        if (head == nullptr) {
            head = filmBaru;
        } else {
            Film* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = filmBaru;
        }
    }

    // Hapus film berdasarkan judul
    void hapusFilm(string judul) {
        if (head == nullptr) {
            cout << "Daftar film kosong!" << endl;
            return;
        }

        // Jika film yang dihapus ada di head
        if (head->judul == judul) {
            Film* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Cari film yang akan dihapus
        Film* temp = head;
        while (temp->next != nullptr && temp->next->judul != judul) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Film '" << judul << "' tidak ditemukan!" << endl;
        } else {
            Film* hapus = temp->next;
            temp->next = temp->next->next;
            delete hapus;
        }
    }

    // Tampilkan semua film
    void tampilkanFilm() {
        if (head == nullptr) {
            cout << "Daftar film kosong!" << endl;
            return;
        }

        Film* temp = head;
        while (temp != nullptr) {
            cout << temp->judul << " (" << temp->tahun << ") - " << temp->rating << endl;
            temp = temp->next;
        }
    }

    // Hitung total film
    int hitungFilm() {
        int count = 0;
        Film* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    DaftarFilm film;
    int jumlahFilm;

    // Input film awal
    cout << "Masukkan jumlah film awal: ";
    cin >> jumlahFilm;

    for (int i = 0; i < jumlahFilm; i++) {
        string judul;
        int tahun, rating;

        cout << "\nFilm " << i + 1 << ":" << endl;
        cout << "Judul: ";
        cin >> judul;
        cout << "Tahun: ";
        cin >> tahun;
        cout << "Rating: ";
        cin >> rating;

        film.tambahFilm(judul, tahun, rating);
    }

    char hapus;
    cout << "\nApakah ingin menghapus film? (y/n): ";
    cin >> hapus;

    if (hapus == 'y' || hapus == 'Y') {
        string judulHapus;
        cout << "Masukkan judul film yang sudah ditonton: ";
        cin >> judulHapus;
        film.hapusFilm(judulHapus);
    }

    cout << "\nDaftar Film:" << endl;
    film.tampilkanFilm();
    cout << "Total film tersisa: " << film.hitungFilm() << endl;

    return 0;
}