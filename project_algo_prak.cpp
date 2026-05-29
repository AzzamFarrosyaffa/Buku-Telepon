#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

struct Kontak {
    string nama;
    string noTelepon;
    int kategori;
};

// variabel global
Kontak daftarKontak[1000];
int jumlahKontak = 0;
const int MAX_KONTAK = 1000;
const string database = "contact_database.txt";

// fungsi mendapatkan kategori dari angka
string getNamaKategori(int k) {
    if (k == 1) return "Keluarga";
    if (k == 2) return "Saudara";
    if (k == 3) return "Teman";
    if (k == 4) return "Tetangga";
    return "Lainnya";
}

// fungsi swap kontak
void tukarKontak(Kontak* a, Kontak* b) {
    Kontak temp = *a;
    *a = *b;
    *b = temp;
}

// fungsi mengecek apakah nomor ganda?
bool nomorSudahAda(string noHP) {
    for (int i = 0; i < jumlahKontak; i++) {
        if (daftarKontak[i].noTelepon == noHP) {
            return true;
        }
    }
    return false;
}

// fungsi mengecek apakah nomor hanya terdiri dari angka
bool nomorValid(string noHP) {
    for (size_t i = 0; i < noHP.length(); i++) {
        if (!isdigit(noHP[i])) {
            return false;
        }
    }
    return true;
}

// fungsi error handling int fail
void cinFail() {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Input tidak valid!\n";
}

// fungsi menambahkan 1 data kontak baru ke file tanpa menghapus isi lama file
void appendDatabase() {
    ofstream file(database, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file!\n";
        return;
    }

    Kontak& k = daftarKontak[jumlahKontak - 1];
    file << k.nama << "|"
         << k.noTelepon << "|"
         << k.kategori << endl;

    file.close();
}

// fungsi menulis ulang seluruh data kontak ke file (saat edit dan hapus)
void overwriteDatabase() {
    ofstream file(database, ios::trunc);
    if (!file.is_open()) {
        cout << "Gagal membuka file!\n";
        return;
    }
    for (int i = 0; i < jumlahKontak; i++) {
        file << daftarKontak[i].nama << "|"
             << daftarKontak[i].noTelepon << "|"
             << daftarKontak[i].kategori << endl;
    }
    file.close();
}

// fungsi membaca data dari file lalu memasukkannya ke dalam array daftarKontak.
void loadDatabase() {
    ifstream file(database);
    if (!file.is_open()) {
        return;
    }
    jumlahKontak = 0;
    string nama;
    string noHP;
    string kategoriStr;
    while (
        getline(file, nama, '|') &&
        getline(file, noHP, '|') &&
        getline(file, kategoriStr)
    ) {
        daftarKontak[jumlahKontak].nama = nama;
        daftarKontak[jumlahKontak].noTelepon = noHP;
        daftarKontak[jumlahKontak].kategori = stoi(kategoriStr);

        jumlahKontak++;
    }
    file.close();
}

// fungsi REKURSI untuk menghitung kategori
int hitungPerKategori(int index, int target) {
    if (index >= jumlahKontak) {
        return 0;
    }
    int point = (daftarKontak[index].kategori == target) ? 1 : 0;
    return point + hitungPerKategori(index + 1, target);
}

// fungsi QUICK SORT
int partition(int low, int high, bool asc) {
    string pivot = daftarKontak[high].nama;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool kondisi;
        if (asc) {
            kondisi = daftarKontak[j].nama < pivot;
        } else {
            kondisi = daftarKontak[j].nama > pivot;
        }
        if (kondisi) {
            i++;
            tukarKontak(&daftarKontak[i], &daftarKontak[j]);
        }
    }
    tukarKontak(&daftarKontak[i + 1], &daftarKontak[high]);
    return i + 1;
}

void quickSort(int low, int high, bool asc) {
    if (low < high) {
        int pi = partition(low, high, asc);
        quickSort(low, pi - 1, asc);
        quickSort(pi + 1, high, asc);
    }
}

// fugsi BINARY SEARCH
int binarySearch(string target) {
    int left = 0;
    int right = jumlahKontak - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (daftarKontak[mid].nama == target) {
            return mid;
        }
        else if (daftarKontak[mid].nama < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// menu TAMBAH KONTAK
void tambahKontak() {
    if (jumlahKontak >= MAX_KONTAK) {
        cout << "Database penuh!\n";
        return;
    }
    cout << "\n--- TAMBAH KONTAK ---\n";
    cout << "Nama : ";
    getline(cin >> ws, daftarKontak[jumlahKontak].nama);
    do {
        cout << "Nomor HP : ";
        cin >> daftarKontak[jumlahKontak].noTelepon;
        if (!nomorValid(daftarKontak[jumlahKontak].noTelepon)) {
            cout << "Nomor HP hanya boleh angka!\n";
            continue;
        }
        if (nomorSudahAda(daftarKontak[jumlahKontak].noTelepon)) {
            cout << "Nomor HP sudah terdaftar!\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Kategori (1-4): ";
        cin >> daftarKontak[jumlahKontak].kategori;
    } while (
        daftarKontak[jumlahKontak].kategori < 1 ||
        daftarKontak[jumlahKontak].kategori > 4
    );
    jumlahKontak++;
    appendDatabase();
    cout << ">> Kontak berhasil ditambahkan!\n";
}

// menu TAMPILKAN TABEL
void tampilkanTabel(int filterKategori = 0) {
    cout << "\n"
         << setfill('=')
         << setw(70)
         << "=" << endl;

    cout << left
         << setfill(' ')
         << setw(5) << "No"
         << setw(25) << "Nama"
         << setw(20) << "Nomor HP"
         << setw(15) << "Kategori"
         << endl;

    cout << setfill('=')
         << setw(70)
         << "="
         << setfill(' ')
         << endl;

    int no = 1;
    for (int i = 0; i < jumlahKontak; i++) {
        if (
            filterKategori == 0 ||
            daftarKontak[i].kategori == filterKategori
        ) {
            cout << left
                 << setw(5) << no++
                 << setw(25) << daftarKontak[i].nama
                 << setw(20) << daftarKontak[i].noTelepon
                 << setw(15)
                 << getNamaKategori(daftarKontak[i].kategori)
                 << endl;
        }
    }
    cout << setfill('-')
         << setw(70)
         << "-"
         << endl;
}

// menu CARI / EDIT / HAPUS
void cariEditHapus() {
    string cari;
    quickSort(0, jumlahKontak - 1, true);
    cout << "\nCari Nama : ";
    getline(cin >> ws, cari);
    int indexKetemu = binarySearch(cari);
    if (indexKetemu == -1) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    Kontak* p = &daftarKontak[indexKetemu];

    cout << "\n=== DATA DITEMUKAN ===\n";
    cout << "Nama     : " << p->nama << endl;
    cout << "No HP    : " << p->noTelepon << endl;
    cout << "Kategori : "
         << getNamaKategori(p->kategori)
         << endl;

    int action;
    cout << "\n1. Edit\n";
    cout << "2. Hapus\n";
    cout << "3. Kembali\n";
    cout << "Pilih : ";
    cin >> action;
    if (action == 1) {
        cout << "Nama Baru : ";
        getline(cin >> ws, p->nama);
        do {
            cout << "No HP Baru : ";
            cin >> p->noTelepon;
            if (!nomorValid(p->noTelepon)) {
                cout << "Nomor hanya boleh angka!\n";
                continue;
            }
            break;
        } while (true);
        do {
            cout << "Kategori Baru (1-4): ";
            cin >> p->kategori;

        } while (
            p->kategori < 1 ||
            p->kategori > 4
        );
        overwriteDatabase();
        cout << ">> Data berhasil diupdate!\n";
    }
    else if (action == 2) {
        char yakin;
        cout << "Yakin ingin menghapus? (y/n): ";
        cin >> yakin;
        if (yakin == 'y' || yakin == 'Y') {
            for (
                int i = indexKetemu;
                i < jumlahKontak - 1;
                i++
            ) {
                daftarKontak[i] = daftarKontak[i + 1];
            }

            jumlahKontak--;

            overwriteDatabase();

            cout << ">> Data berhasil dihapus!\n";
        }
    }
}

// menu STATISTIK
void menuStatistik() {
    system("cls");
    cout << "\n=== STATISTIK ===\n";
    cout << "Keluarga : "
         << hitungPerKategori(0, 1)
         << endl;

    cout << "Saudara  : "
         << hitungPerKategori(0, 2)
         << endl;

    cout << "Teman    : "
         << hitungPerKategori(0, 3)
         << endl;

    cout << "Tetangga : "
         << hitungPerKategori(0, 4)
         << endl;

    int f;
    cout << "\nFilter kategori (1-4 / 0 tidak): ";
    cin >> f;
    if (f >= 1 && f <= 4) {
        tampilkanTabel(f);
    }
    system("pause");
}

// MAIN
int main() {
    loadDatabase();
    int pil;
    do {
        system("cls");

        cout << "\n====== MAIN MENU ======\n";
        cout << "1. Tambah Kontak\n";
        cout << "2. Lihat Kontak\n";
        cout << "3. Cari/Edit/Hapus\n";
        cout << "4. Statistik\n";
        cout << "5. Keluar\n";

        cout << "Pilihan : ";

        cin >> pil;

        if (cin.fail()) {
            cinFail();
            continue;
        }

        switch (pil) {
        case 1:
            system("cls");
            tambahKontak();
            system("pause");
            break;
        case 2: {
            system("cls");
            int s;
            do {
                cout << "1. ASC\n";
                cout << "2. DESC\n";
                cout << "Pilih : ";
                cin >> s;
            } while (s != 1 && s != 2);
            quickSort(0,jumlahKontak - 1,s == 1);
            tampilkanTabel();
            system("pause");
            break;
        }
        case 3:
            system("cls");
            cariEditHapus();
            system("pause");
            break;
        case 4:
            menuStatistik();
            break;
        case 5:
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Menu tidak valid!\n";
        }
    } while (pil != 5);
    return 0;
}