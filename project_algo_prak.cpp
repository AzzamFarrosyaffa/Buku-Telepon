#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// struct untuk menyimpan kontak
struct Kontak {
    string nama;
    string noTelepon;
    int kategori; // 1: Keluarga, 2: Saudara, 3: Teman, 4: Tetangga
};

// Global Variables
Kontak daftarKontak[100];
int jumlahKontak = 0;
const string database = "contact_database.txt";

// --- FUNGSI HELPER ---
string getNamaKategori(int k) {
    if (k == 1) return "Keluarga";
    if (k == 2) return "Saudara";
    if (k == 3) return "Teman";
    if (k == 4) return "Tetangga";
    return "Lainnya";
}

// PENERAPAN POINTER 1: Fungsi untuk menukar (swap) data menggunakan parameter pointer
void tukarKontak(Kontak* a, Kontak* b) {
    Kontak temp = *a;
    *a = *b;
    *b = temp;
}

// --- FUNGSI FILE HANDLING ---
void storeDatabase() {
    ofstream file(database);
    for (int i = 0; i < jumlahKontak; i++) {
        file << daftarKontak[i].nama << "|" 
             << daftarKontak[i].noTelepon << "|" 
             << daftarKontak[i].kategori << endl;
    }
    file.close();
}

void loadDatabase() {
    ifstream file(database);
    if (!file) return;

    jumlahKontak = 0;
    string line;
    while (getline(file, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.rfind("|");
        if (p1 != string::npos && p2 != string::npos) {
            daftarKontak[jumlahKontak].nama = line.substr(0, p1);
            daftarKontak[jumlahKontak].noTelepon = line.substr(p1 + 1, p2 - p1 - 1);
            daftarKontak[jumlahKontak].kategori = stoi(line.substr(p2 + 1));
            jumlahKontak++;
        }
    }
    file.close();
}

// fungsi rekursif untuk menampilkan statistik
int hitungPerKategori(int index, int target) {
    if (index >= jumlahKontak) return 0;
    int point = (daftarKontak[index].kategori == target) ? 1 : 0;
    return point + hitungPerKategori(index + 1, target);
}

// fungsi sorting menggunakan bubble sort
void urutkanData(bool asc) {
    for (int i = 0; i < jumlahKontak - 1; i++) {
        for (int j = 0; j < jumlahKontak - i - 1; j++) {
            bool syarat = asc ? (daftarKontak[j].nama > daftarKontak[j+1].nama) 
                              : (daftarKontak[j].nama < daftarKontak[j+1].nama);
            if (syarat) {
                // Memanggil fungsi swap dengan mengirim alamat memori (pointer)
                tukarKontak(&daftarKontak[j], &daftarKontak[j+1]);
            }
        }
    }
}

void tambahKontak() {
    cout << "\n--- TAMBAH KONTAK BARU ---\n";
    cout << "Nama           : "; getline(cin >> ws, daftarKontak[jumlahKontak].nama);
    cout << "Nomor Telepon  : "; cin >> daftarKontak[jumlahKontak].noTelepon;
    cout << "Kategori (1:Keluarga, 2:Saudara, 3:Teman, 4:Tetangga): ";
    cin >> daftarKontak[jumlahKontak].kategori;
    
    jumlahKontak++;
    storeDatabase();
    cout << ">> Kontak berhasil disimpan!\n";
}

void tampilkanTabel(int filterKategori = 0) {
    cout << "\n" << setfill('=') << setw(70) << "=" << endl;
    cout << setfill(' ') << setw(5) << "No" << setw(20) << "Nama" 
         << setw(20) << "Nomor HP" << setw(20) << "Kategori" << endl;
    cout << setfill('=') << setw(70) << "=" << setfill(' ') << endl;

    int counter = 1;
    for (int i = 0; i < jumlahKontak; i++) {
        if (filterKategori == 0 || daftarKontak[i].kategori == filterKategori) {
            cout << setw(5) << counter++ 
                 << setw(20) << daftarKontak[i].nama 
                 << setw(20) << daftarKontak[i].noTelepon 
                 << setw(20) << getNamaKategori(daftarKontak[i].kategori) << endl;
        }
    }
    cout << setfill('-') << setw(70) << "-" << endl;
}

void cariEditHapus() {
    string cari;
    cout << "\nCari Nama atau No HP (Case Sensitive) : "; getline(cin >> ws, cari);
    int indexKetemu = -1;

    for (int i = 0; i < jumlahKontak; i++) {
        if (daftarKontak[i].nama == cari || daftarKontak[i].noTelepon == cari) {
            indexKetemu = i;
            break;
        }
    }

    if (indexKetemu != -1) {
        // pointer struct yang menunjuk ke kontak yang ditemukan
        Kontak* pointerEdit = &daftarKontak[indexKetemu];

        cout << "\n[ DATA DITEMUKAN ]\n";
        // operator arrow (->) untuk mengakses member struct via pointer
        cout << "Nama     : " << pointerEdit->nama << endl;
        cout << "No HP    : " << pointerEdit->noTelepon << endl;
        cout << "Kategori : " << getNamaKategori(pointerEdit->kategori) << endl;

        cout << "\n1. Edit | 2. Hapus | 3. Kembali: ";
        int action; cin >> action;

        if (action == 1) {
            cout << "Nama Baru   : "; getline(cin >> ws, pointerEdit->nama);
            cout << "No HP Baru  : "; cin >> pointerEdit->noTelepon;
            cout << "Kategori Baru (1:Keluarga, 2:Saudara, 3:Teman, 4:Tetangga) : "; cin >> pointerEdit->kategori;
            storeDatabase();
            cout << "\n>> Data diperbarui!\n";
        } else if (action == 2) {
            for (int i = indexKetemu; i < jumlahKontak - 1; i++) {
                daftarKontak[i] = daftarKontak[i+1];
            }
            jumlahKontak--;
            storeDatabase();
            cout << "\n>> Data dihapus!\n";
        }
    } else {
        cout << "\n[ DATA TIDAK DITEMUKAN ]\n\n";
    }
}

int main() {
    loadDatabase();
    int pil;
    do {
        system("cls");
        cout << "\n====== MAIN MENU ======\n";
        cout << "1. Tambah Kontak\n";
        cout << "2. Lihat Daftar\n";
        cout << "3. Cari Kontak\n";
        cout << "4. Statistik & Filter\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: "; cin >> pil;

        switch (pil) {
            case 1:
                system("cls");
                tambahKontak();
                system("pause");
                break;
            case 2:
                system("cls");
                int s;
                cout << "Urutkan Nama [ 1. ASC (A-Z) | 2. DESC (Z-A) ]: "; cin >> s;
                urutkanData(s == 1);
                tampilkanTabel();
                system("pause");
                break;
            case 3:
                system("cls");
                cariEditHapus();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "\n--- STATISTIK KONTAK ---\n";
                cout << "Keluarga : " << hitungPerKategori(0, 1) << endl;
                cout << "Saudara  : " << hitungPerKategori(0, 2) << endl;
                cout << "Teman    : " << hitungPerKategori(0, 3) << endl;
                cout << "Tetangga : " << hitungPerKategori(0, 4) << endl;
                
                cout << "\nIngin tampilkan kategori tertentu?\n(1: Keluarga, 2: Saudara, 3: Teman, 4: Tetangga || 0 untuk tidak): ";
                int f; cin >> f;
                if (f > 0 and f < 5) tampilkanTabel(f);
                system("pause");
                break;
        }
    } while (pil != 5);

    cout << "\nProgram selesai. Sampai jumpa!\n";
    return 0;
}