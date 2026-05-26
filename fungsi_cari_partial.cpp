// ganti fungsi void cariEditHapus() di kode project_algo_prak.cpp agar bisa mencari partial. contoh "Az" menampilkan "Azzam, Azriel, Az..."

void cariEditHapus() {
    string cari;
    string ulang;
    do {
        cout << "\nCari Nama atau No HP (Case Sensitive) : "; getline(cin >> ws, cari);
        
        int matchCount = 0;
        int indices[1000]; // Array sementara untuk menyimpan index asli kontak yang cocok

        cout << "\n[ HASIL PENCARIAN ]\n";
        for (int i = 0; i < jumlahKontak; i++) {
            // Menggunakan .find() untuk mencari substring
            // string::npos artinya "tidak ditemukan"
            bool namaCocok = daftarKontak[i].nama.find(cari) != string::npos;
            bool hpCocok = daftarKontak[i].noTelepon.find(cari) != string::npos;

            if (namaCocok || hpCocok) {
                indices[matchCount] = i; // Simpan posisi index aslinya
                matchCount++;
                
                // Tampilkan daftar yang cocok
                cout << " " << matchCount << ". " << daftarKontak[i].nama 
                     << " | " << daftarKontak[i].noTelepon 
                     << " | " << getNamaKategori(daftarKontak[i].kategori) << endl;
            }
        }

        if (matchCount > 0) {
            int indexKetemu = -1;
            
            // Jika hanya 1 yang ketemu, otomatis pilih itu
            if (matchCount == 1) {
                indexKetemu = indices[0];
            } 
            // Jika lebih dari 1, minta user memilih
            else {
                cout << "\nDitemukan " << matchCount << " kontak. Pilih nomor (1-" << matchCount << ") yang ingin dikelola: ";
                int pilihan;
                cin >> pilihan;
                if (pilihan > 0 && pilihan <= matchCount) {
                    indexKetemu = indices[pilihan - 1];
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
            }

            // Jika ada kontak valid yang dipilih, lanjutkan ke proses edit/hapus
            if (indexKetemu != -1) {
                Kontak* pointerEdit = &daftarKontak[indexKetemu];

                cout << "\n[ DATA DIPILIH ]\n";
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
            }
        } else {
            cout << "[ DATA TIDAK DITEMUKAN ]\n";
        }
        
        cout << "\nUlangi pencarian? (y/n) : "; cin >> ulang;
    } while (ulang == "y" || ulang == "Y");
}
