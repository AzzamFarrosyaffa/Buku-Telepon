# 📖 Aplikasi Buku Telepon C++

Aplikasi Buku Telepon ini adalah program konsol berbasis C++ yang dirancang untuk manajemen kontak secara efisien. Program ini tidak hanya berfungsi sebagai alat pencatat sederhana, tetapi juga dibangun untuk mengimplementasikan berbagai konsep fundamental hingga menengah dalam ilmu komputer dan pemrograman C++.

Didesain dengan antarmuka teks yang interaktif, aplikasi ini memastikan data kontak kamu tersimpan dengan aman, terstruktur, dan memiliki fitur pencarian fleksibel!

## ✨ Fitur Unggulan & Implementasi Materi

Program ini mengintegrasikan materi utama pemrograman C++ secara komprehensif:

* **Struct & Array**: Data setiap kontak (Nama, Nomor Telepon, dan Kategori) dibungkus secara terstruktur menggunakan `Struct`, lalu ditampung ke dalam `Array` berkapasitas besar sebagai penyimpanan memori sementara.
* **Pointer**: Penggunaan *pass-by-reference* dengan pointer diterapkan pada pertukaran data (`tukarKontak`) dan manipulasi data langsung pada memori saat proses pengeditan (*Edit*).
* **Sorting (Quick Sort)**: Menggunakan algoritma *Quick Sort* yang jauh lebih cepat dari *Bubble Sort* ($O(n \log n)$). Pengguna bahkan bisa memilih untuk mengurutkan kontak secara *Ascending* (A-Z) maupun *Descending* (Z-A).
* **Searching (Linear & Partial Match)**: Pencarian kontak tidak lagi kaku! Menggunakan metode *Linear Search* yang dipadukan dengan fungsi `string::find`, kamu bisa mencari kontak hanya dengan mengetikkan sebagian nama atau sebagian angka dari nomor HP (contoh: mengetik "Az" akan memunculkan "Azzam", "Azriel", dst).
* **Fungsi Rekursif**: Pendekatan rekursif (*Divide and Conquer*) digunakan secara unik untuk melakukan rekapitulasi komputasi, yaitu menghitung jumlah kontak berdasarkan kategori (Statistik).
* **File Handling (I/O) Berbasis Delimiter**: Data bersifat persisten dan disimpan menggunakan pemisah/delimiter `|` di dalam file `contact_database.txt` (contoh: `Budi|0812345|3`). Program secara cerdas membedakan metode *Append* (menambah data di akhir) dan *Truncate* (menulis ulang saat ada yang dihapus).
* **Validasi Cctype**: Menggunakan library `<cctype>` untuk memastikan integritas input nomor HP, sehingga program akan menolak otomatis jika nomor diisi dengan huruf.

## 🚀 Cara Menjalankan Program

1.  **Clone / Unduh Repository**: Unduh file `.cpp` utama (misal: `project_algo_prak.cpp`) ke dalam komputer kamu.
2.  **Siapkan Database Dummy (Opsional)**: 
    * Buat sebuah file bernama `contact_database.txt` di dalam folder yang sama dengan file program.
    * Jika ingin membuat data *dummy*, gunakan format `Nama|NomorHP|IDKategori` per baris. 
      *(Catatan ID Kategori: 1=Keluarga, 2=Saudara, 3=Teman, 4=Tetangga)*.
      Contoh isi teks:
      ```text
      Andi Setiawan|081200001111|3
      Bunda|081322223333|1
      ```
3.  **Kompilasi Program**: Gunakan compiler C++ (seperti g++ atau MinGW) untuk mengkompilasi *source code*.
    ```bash
    g++ project_algo_prak.cpp -o project_algo_prak
    ```
4.  **Jalankan Aplikasi**: Buka terminal/CMD dan jalankan file yang telah dikompilasi.
    ```bash
    ./project_algo_prak
    ```

## 🛠️ Menu Tersedia

1.  **Tambah Kontak**: Masukkan nama, nomor telepon (divalidasi hanya angka), dan pilih kategorinya.
2.  **Lihat Daftar Kontak**: Menampilkan seluruh data dalam format tabel yang rapi, dengan opsi pengurutan *Ascending* atau *Descending*.
3.  **Cari/Edit/Hapus**: Modul lengkap untuk mencari potongan nama/nomor, yang dilanjutkan dengan opsi untuk memperbarui atau menghapus data kontak yang dipilih.
4.  **Statistik & Filter Kontak**: Melihat rekapitulasi jumlah orang per kategori secara *real-time*, dengan fitur tambahan untuk memfilter tampilan tabel hanya pada kategori tertentu.
5.  **Keluar**: Menutup aplikasi dan memastikan seluruh *state* memori selesai diproses.

---
*Dibuat untuk keperluan pembelajaran struktur data dan algoritma C++.*

Azzam Farrosyaffa **123250096**
Verrel Ewaldo Bukit **123250100** |
*Infromatika UPNYK*
