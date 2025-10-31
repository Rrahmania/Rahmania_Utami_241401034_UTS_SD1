#include <iostream>
#include <string>
using namespace std;

struct Pasien {
    string nama;
    string jenis;
    int umur;
    int darurat;
};

class AntrianHewan {
private:
    Pasien* data;
    int kapasitas;
    int jumlah;

public:
    AntrianHewan() {
        kapasitas = 5;
        data = new Pasien[kapasitas];
        jumlah = 0;
    }

    ~AntrianHewan() {
        delete[] data;
    }

    void tambahPasien(string nama, string jenis, int umur, int darurat) {
        if (jumlah == kapasitas) {
            kapasitas *= 2;
            Pasien* temp = new Pasien[kapasitas];
            
            for (int i = 0; i < jumlah; i++) {
                temp[i] = data[i];
            }
            
            delete[] data;
            data = temp;
        }

        Pasien pasienBaru;
        pasienBaru.nama = nama;
        pasienBaru.jenis = jenis;
        pasienBaru.umur = umur;
        pasienBaru.darurat = darurat;

        // Cari posisi yang tepat berdasarkan tingkat darurat
        int posisi = jumlah;
        for (int i = 0; i < jumlah; i++) {
            if (data[i].darurat < darurat) {
                posisi = i;
                break;
            }
        }

        // Geser elemen untuk membuat ruang
        for (int i = jumlah; i > posisi; i--) {
            data[i] = data[i - 1];
        }

        // Masukkan pasien baru
        data[posisi] = pasienBaru;
        jumlah++;
    }

    void tampilkanAntrian() {
        if (jumlah == 0) {
            cout << "Antrian kosong!" << endl;
            return;
        }

        //Loop melalui semua pasien dan tampilkan informasinya
        cout << "\nDaftar Antrian Pasien:" << endl;
        for (int i = 0; i < jumlah; i++) {
            cout << i + 1 << ". " << data[i].nama 
                 << " (" << data[i].umur << " tahun) - Darurat " 
                 << data[i].darurat << endl;
        }
    }
};

int main() {
    AntrianHewan antrian;
    int jumlahPasien;

    cout << "Masukkan jumlah pasien: ";
    cin >> jumlahPasien;

    for (int i = 0; i < jumlahPasien; i++) {
        string nama, jenis;
        int umur, darurat;

        cout << "\nPasien " << i + 1 << ":" << endl;
        
        cout << "Nama hewan: ";
        cin >> nama;
        
        cout << "Jenis hewan: ";
        cin >> jenis;
        
        cout << "Umur: ";
        cin >> umur;
        
        cout << "Tingkat darurat (1-5): ";
        cin >> darurat;

        if (darurat < 1) darurat = 1;
        if (darurat > 5) darurat = 5;

        antrian.tambahPasien(nama, jenis, umur, darurat);
    }

    antrian.tampilkanAntrian();

    return 0;
}