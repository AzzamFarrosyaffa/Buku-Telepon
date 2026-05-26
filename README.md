# 📖 Aplikasi Buku Telepon C++

Aplikasi Buku Telepon ini adalah program konsol berbasis C++ yang dirancang untuk manajemen kontak secara efisien. Program ini tidak hanya berfungsi sebagai alat pencatat sederhana, tetapi juga dibangun untuk mengimplementasikan berbagai konsep fundamental hingga menengah dalam ilmu komputer dan pemrograman C++.

Didesain dengan antarmuka teks yang interaktif, aplikasi ini memastikan data kontak kamu tersimpan dengan aman, tertata rapi, dan dapat dicari dalam sekejap!

## ✨ Fitur Unggulan & Implementasi Materi

Program ini mengintegrasikan 7 materi utama pemrograman C++:

* **Struct & Array**: Data setiap kontak (Nama dan Nomor Telepon) dibungkus secara rapi menggunakan `Struct`, lalu ditampung ke dalam struktur data `Array` sebagai penyimpanan memori sementara.
* **Pointer**: Manipulasi dan pembaruan jumlah kontak (pass-by-reference) dilakukan secara efisien menggunakan `Pointer`.
* **Sorting (Bubble Sort)**: Daftar kontak tidak akan pernah berantakan! Setiap kali kontak baru ditambahkan, algoritma *Bubble Sort* akan mengurutkan seluruh data secara alfabetis (A-Z) secara *real-time*.
* **Searching (Binary Search)**: Mencari satu nama dari ratusan kontak terasa instan. Program menggunakan algoritma *Binary Search* dengan kompleksitas waktu $O(\log n)$ yang jauh lebih cepat dari pencarian biasa.
* **Fungsi Rekursif**: Implementasi *Binary Search* dibangun menggunakan metode Rekursif, di mana fungsi akan memanggil dirinya sendiri untuk membelah rentang pencarian hingga kontak ditemukan.
* **File Handling (I/O)**: Data bersifat persisten! Semua kontak disimpan ke dalam file eksternal (`bukutelepon.txt`). Data akan otomatis dimuat ulang (*load*) saat program dibuka, dan disimpan (*save*) saat ada pembaruan.

## 🚀 Cara Menjalankan Program

1.  **Clone / Unduh Repository**: Unduh file `.cpp` ke dalam komputer kamu.
2.  **Siapkan Database Dummy (Opsional)**: 
    * Buat sebuah file bernama `bukutelepon.txt` di dalam folder yang sama dengan file program.
    * Kamu bisa mengisi file tersebut dengan dummy data (Nama di baris ganjil, Nomor di baris genap).
3.  **Kompilasi Program**: Gunakan compiler C++ (seperti g++ atau MinGW) untuk mengkompilasi *source code*.
    ```bash
    g++ bukutelepon.cpp -o bukutelepon
    ```
4.  **Jalankan Aplikasi**: Buka terminal/CMD dan jalankan file yang telah dikompilasi.
    ```bash
    ./bukutelepon
    ```

## 🛠️ Menu Tersedia

1.  **Tambah Kontak**: Masukkan nama dan nomor telepon baru.
2.  **Tampilkan Semua Kontak**: Melihat seluruh database kontak yang sudah terurut abjad.
3.  **Cari Kontak**: Masukkan nama spesifik (Case Sensitive) untuk mencari nomor teleponnya.
4.  **Keluar**: Menutup aplikasi secara aman.

---
*Dibuat untuk keperluan pembelajaran struktur data dan algoritma dasar C++.*

Azzam Farrosyaffa **123250096**
Verrel Ewaldo Bukit **123250100**
*Infromatika UPNYK*
