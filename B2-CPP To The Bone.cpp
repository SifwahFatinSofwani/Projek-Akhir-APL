#include <iostream>
#include <iomanip>
#include <limits> // diperlukan untuk numeric_limits
#include <ctime>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

#define max_merch 50

// kamus global ꒰✿´ ꒳ ` ꒱♡
string username, password, choice;
int panjang_array_merch_akun = 6; // jumlah akun awal termasuk admin dan pengguna bawaan

Table tabellogin, tabeluser, tabeladmin;

void cls() {
    system("cls");
}

// Add struct untuk riwayat pesanan ꒰✿´ ꒳ ` ꒱♡
struct RiwayatPesanan {
    string nama_merch;
    int jumlah;
    int total_harga;
    time_t tanggal; // Menggunakan time_t untuk menyimpan waktu
};

// struct rincian ꒰✿´ ꒳ ` ꒱♡
struct Rincian {
    int harga_merch;
    int stok_merch;
};

// nested struct ꒰✿´ ꒳ ` ꒱♡
struct Merchandise {
    string nama_merch;
    Rincian rincian;
    int edisi_merch;
};

// Modify struct Akun to include riwayat pesanan ꒰✿´ ꒳ ` ꒱♡
struct Akun {
    struct isiakun {
        int saldo;
    } isiakun;
    string username;
    string password;
    string role;
    RiwayatPesanan riwayat[100]; // Array riwayat untuk setiap user
    int jumlah_riwayat;       // Jumlah riwayat untuk setiap user
};

// array of struct ꒰✿´ ꒳ ` ꒱♡
Merchandise katalog[max_merch] = {
    {"MCLAREN TEAM LANDO NORRIS GRAPHIC T-SHIRT", {245000, 24}, 2025},
    {"MCLAREN TEAM OSCAR PIASTRI CUFF BEANIE", {567000, 33}, 2025},
    {"MCLAREN F1 TEAM CHAMPIONS T-SHIRT", {423000, 35}, 2024},
    {"MCLAREN F1 TEAM SET-UP T-SHIRT", {5250000, 87}, 2025}, // Harga diperbaiki dari 5250000 menjadi 525000 jika itu typo
    {"MCLAREN F1 TEAM HOODIE", {987000, 65}, 2025},
    {"MCLAREN TEAM OSCAR PIASTRI SNAP CAP", {476000, 23}, 2024},
};

// Initialize jumlah_riwayat for each user in the user array
Akun user[30] = {
    {{0}, "admin", "admin", "admin", {}, 0},
    {{0}, "user", "user", "user", {}, 0},
    {{0}, "Dzaki", "user", "user", {}, 0},
    {{0}, "Riva", "user", "user", {}, 0},
    {{0}, "Ridwan", "user", "user", {}, 0},
    {{0}, "Wahyu", "user", "user", {}, 0}, 
};

int panjang_array_merch = 6; // Iinisiasi awal panjang array merchandise

// fungsi overloading ꒰✿´ ꒳ ` ꒱♡
int tambah(int a, int b) {
    return a + b;
}
double tambah(double a, double b) {
    return a + b;
}

// kurangi stok ꒰✿´ ꒳ ` ꒱♡
int kurang(int a, int b) {
    return a - b;
}

// fungsi login admin ꒰✿´ ꒳ ` ꒱♡
bool validasilogin(string username_input, string password_input) {
    for (int i = 0; i < panjang_array_merch_akun; i++) {
        if (user[i].username == username_input && user[i].password == password_input) {
            return true;
        }
    }
    return false;
}

// Fungsi error handling sederhana
void showError(const string& pesan) {
    cout << "----------------------------------------------" << endl;
    cout << "Error: " << pesan << endl;
    cout << "----------------------------------------------" << endl;
}

// Tabel katalog merchandise dengan tabulate
void katalog_merchandise(Merchandise katalog_display[], int panjang_array_merch_display) { 
    Table tabelKatalog;
    tabelKatalog.add_row({"No", "Nama Merchandise", "Harga", "Stok", "Edisi"});
    tabelKatalog[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);
    for (int i = 0; i < panjang_array_merch_display; i++) {
        tabelKatalog.add_row({
            to_string(i + 1),
            katalog_display[i].nama_merch,
            to_string(katalog_display[i].rincian.harga_merch),
            to_string(katalog_display[i].rincian.stok_merch),
            to_string(katalog_display[i].edisi_merch)
        });
    }
    tabelKatalog.format().font_align(FontAlign::center);
    cout << tabelKatalog << endl;
    cout << "----------------------------------------------" << endl; 
    system("pause"); 
}


bool isDuplicateName(const Merchandise katalog_check[], int panjang_array, const string& nama, int skip_index = -1) {
    for (int i = 0; i < panjang_array; i++) {
        if (i != skip_index && katalog_check[i].nama_merch == nama) {
            return true;
        }
    }
    return false;
}

void tambah_merchandise(Merchandise katalog_add[], int *panjang_array_ptr) {
    cls();
    katalog_merchandise(katalog_add, *panjang_array_ptr); // menampilkan katalog terlebih dahulu

    try {
        if (*panjang_array_ptr < max_merch) {
            cout << "==============================================" << endl;
            cout << "               Merchandise Baru               " << endl;
            cout << "==============================================" << endl;
            
            string nama_baru;
            cout << "Masukan nama merchandise: ";
            getline(cin, nama_baru);
            // mengubah nama ke uppercase
            transform(nama_baru.begin(), nama_baru.end(), nama_baru.begin(), ::toupper);

            if (nama_baru.empty()) {
                throw runtime_error("Nama merchandise tidak boleh kosong!");
                 system("pause");
            }
            if (isDuplicateName(katalog_add, *panjang_array_ptr, nama_baru)) {
                throw runtime_error("Nama merchandise sudah ada dalam katalog!");
                 system("pause");
            }

            katalog_add[*panjang_array_ptr].nama_merch = nama_baru;

            cout << "Masukan harga merchandise: ";
            if (!(cin >> katalog_add[*panjang_array_ptr].rincian.harga_merch)) {
                throw runtime_error("Input harga harus berupa angka!");
                 system("pause");
            }
            if (katalog_add[*panjang_array_ptr].rincian.harga_merch < 0 or katalog_add[*panjang_array_ptr].rincian.harga_merch == 0) {
                 throw runtime_error("Harga tidak boleh negatif! atau nol");
                  system("pause");
            }

            cout << "Masukan stok merchandise: ";
            if (!(cin >> katalog_add[*panjang_array_ptr].rincian.stok_merch)) {
                throw runtime_error("Input stok harus berupa angka!");
                 system("pause");
            }
             if (katalog_add[*panjang_array_ptr].rincian.stok_merch < 0) {
                 throw runtime_error("Stok tidak boleh negatif!");
                  system("pause");
            }

            cout << "Masukan edisi merchandise (2000-2025): ";
            int edisi;
            if (!(cin >> edisi)) {
                throw runtime_error("Input edisi harus berupa angka!");
                 system("pause");
            }
            if (edisi < 2000 || edisi > 2025) {
                throw invalid_argument("Edisi harus antara tahun 2000-2025!");
                 system("pause");
            }
            katalog_add[*panjang_array_ptr].edisi_merch = edisi;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // sebagai penghapus newline setelah input
            (*panjang_array_ptr)++;
            cls();
            cout << "Yay! Merchandise berhasil ditambahkan!" << endl;
            cout << "--------------------------------------" << endl;
        } else {
            throw runtime_error("Oh naww! Kapasitas penuh! Tidak bisa menambah merchandise lagi!");
        }
    } catch (const exception& e) {
        if (cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        showError(e.what());
       
    }
    system("pause"); // jeda untuk melihat pesan berhasil
}

// update merchandise ꒰✿´ ꒳ ` ꒱♡
void update_merchandise(Merchandise katalog_update[], int *panjang_array_ptr, int *index_ptr) {
    cls();
    katalog_merchandise(katalog_update, *panjang_array_ptr);

    try {
        cout << "==============================================" << endl;
        cout << "              Update Merchandise              " << endl;
        cout << "==============================================" << endl;
        cout << "Masukan nomor merchandise yang ingin di ubah: ";
        if (!(cin >> *index_ptr)) {
            throw runtime_error("Input nomor harus berupa angka!");
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        if (*index_ptr > 0 && *index_ptr <= *panjang_array_ptr) {
            int current_idx = *index_ptr - 1;
            int stok_lama = katalog_update[current_idx].rincian.stok_merch;
            cout << fixed << setprecision(0);
            cout << "Nama Barang   : " << katalog_update[current_idx].nama_merch << endl;
            cout << "Stok          : " << stok_lama << endl;
            cout << "Harga         : " << katalog_update[current_idx].rincian.harga_merch << endl;
            cout << "Edisi         : " << katalog_update[current_idx].edisi_merch << endl;
            cout << "----------------------------------------------" << endl;
            cout << "Pilih: " << endl;
            cout << "1. Update Nama Merchandise" << endl;
            cout << "2. Tambah Stok Merchandise" << endl;
            cout << "3. Kurangi Stok Merchandise" << endl;
            cout << "4. Update Harga Merchandise" << endl;
            cout << "5. Update Edisi Merchandise" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "Masukkan pilihan: ";

            string pilihan_update;
            getline(cin, pilihan_update);

            if (pilihan_update == "1") {

                cout << "Masukkan nama baru: ";
                string nama_baru;
                getline(cin, nama_baru);
                // Convert nama ke uppercase
                transform(nama_baru.begin(), nama_baru.end(), nama_baru.begin(), ::toupper);
                
                if (nama_baru.empty()) {
                    throw runtime_error("Nama merchandise tidak boleh kosong!");
                    system("pause");
                }

                if (nama_baru == katalog_update[current_idx].nama_merch) {
                    throw runtime_error("Nama baru tidak boleh sama dengan nama sebelumnya!");
                    system("pause");
                }
                
                if (isDuplicateName(katalog_update, *panjang_array_ptr, nama_baru, current_idx)) {
                    throw runtime_error("Nama merchandise sudah ada dalam katalog!");
                    system("pause");
                }
                katalog_update[current_idx].nama_merch = nama_baru;
                cout << "Yay! Nama Merchandise berhasil diperbaharui!" << endl;

            } else if (pilihan_update == "2") {

                int jumlah;
                cout << "Masukan jumlah tambahan stok: ";
                if (!(cin >> jumlah)) {
                    throw runtime_error("Input jumlah harus berupa angka!");
                    system("pause");
                }
                
                 if (jumlah < 0) {
                    throw runtime_error("Jumlah tambahan stok tidak boleh negatif!");
                    system("pause");
                 }
                 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                katalog_update[current_idx].rincian.stok_merch = tambah(stok_lama, jumlah);
                cout << "Yay! Stok Merchandise berhasil diperbaharui!" << endl;

            } else if (pilihan_update == "3") {

                int jumlah;
                cout << "Masukan jumlah stok yang dikurangi: ";
                if (!(cin >> jumlah)) {
                    throw runtime_error("Input jumlah harus berupa angka!");
                system("pause");
                }

                if (jumlah < 0) {
                    throw runtime_error("Jumlah pengurangan stok tidak boleh negatif!");
                system("pause");
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (jumlah > stok_lama) {
                    throw runtime_error("Stok tidak mencukupi untuk dikurangi!");
                    system("pause");
                }
                katalog_update[current_idx].rincian.stok_merch = kurang(stok_lama, jumlah);
                cout << "Yay! Stok Merchandise berhasil diperbaharui!" << endl;
                system("pause");

            } else if (pilihan_update == "4") {

                cout << "Masukan harga baru: ";
                if (!(cin >> katalog_update[current_idx].rincian.harga_merch)) {
                    throw runtime_error("Input harga harus berupa angka!");
                    system("pause");
                }
                    
                if (katalog_update[current_idx].rincian.harga_merch < 0){
                    throw runtime_error("Harga tidak boleh negatif!");
                    system("pause");
                }
                    
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Yay! Harga Merchandise berhasil diperbaharui!" << endl;
                system("pause");

            } else if (pilihan_update == "5") {

                cout << "Masukan edisi baru (2000-2025): ";
                int edisi;
                if (!(cin >> edisi)) {
                    throw runtime_error("Input edisi harus berupa angka!");
                    system("pause");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (edisi < 2000 || edisi > 2025) {
                    throw runtime_error("Edisi harus antara tahun 2000-2025!");
                    system("pause");
                }
                katalog_update[current_idx].edisi_merch = edisi;
                cout << "Yay! Edisi Merchandise berhasil diperbaharui!" << endl;
                system("pause");
                
            } else {
                throw runtime_error("Pilihan update tidak valid!");
                system("pause");
            }
        } else {
            throw runtime_error("Nomor merchandise tidak valid!");
            system("pause");
        }
    } catch (const exception& e) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        showError(e.what());
    }
    system("pause"); // jeda untuk melihat pesan berhasil
}

// hapus merchandise ꒰✿´ ꒳ ` ꒱♡
void hapus_merchandise(Merchandise katalog_delete[], int *panjang_array_ptr, int *index_ptr) { 
    cls();
    katalog_merchandise(katalog_delete, *panjang_array_ptr);
    try {
        cout << "==============================================" << endl;
        cout << "              Hapus Merchandise               " << endl;
        cout << "==============================================" << endl;
        cout << "Masukan nomor merchandise yang ingin dihapus: ";
        if (!(cin >> *index_ptr)) {
             throw runtime_error("Input nomor harus berupa angka!");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (*index_ptr > 0 && *index_ptr <= *panjang_array_ptr) {
            for (int i = *index_ptr - 1; i < *panjang_array_ptr - 1; i++) {
                katalog_delete[i] = katalog_delete[i + 1];
            }
            (*panjang_array_ptr)--;
            cout << "Yay! Merchandise berhasil dihapus!" << endl;

        } else {
            showError("Nomor merchandise ga valid nih!");
        }
        cout << "----------------------------------------------" << endl;
    } catch (const exception& e) {
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        showError(e.what());
    }
    system("pause");
}

// sorting nama merchandise - descending - bubble sort꒰✿´ ꒳ ` ꒱♡
void bubbleSort_nama_merch(Merchandise katalog_sort[], int panjang_array_sort) { 
    for (int i = 0; i < panjang_array_sort - 1; i++) {
        for (int j = 0; j < panjang_array_sort - i - 1; j++) {
            if (katalog_sort[j].nama_merch < katalog_sort[j + 1].nama_merch) {
                swap(katalog_sort[j], katalog_sort[j + 1]);
            }
        }
    }
}

// sorting harga merchandise - ascending - bubble sort ꒰✿´ ꒳ ` ꒱♡
void bubbleSort_harga_merch(Merchandise katalog_sort[], int panjang_array_sort) {
    for (int i = 0; i < panjang_array_sort - 1; i++) {
        for (int j = 0; j < panjang_array_sort - i - 1; j++) {
            if (katalog_sort[j].rincian.harga_merch > katalog_sort[j + 1].rincian.harga_merch) {
                swap(katalog_sort[j], katalog_sort[j + 1]);
            }
        }
    }
}

// sorting stok merchandise - ascending - bubble sort ꒰✿´ ꒳ ` ꒱♡
void bubbleSort_stok_merch(Merchandise katalog_sort[], int panjang_array_sort) {
    for (int i = 0; i < panjang_array_sort - 1; i++) {
        for (int j = 0; j < panjang_array_sort - i - 1; j++) {
            if (katalog_sort[j].rincian.stok_merch > katalog_sort[j + 1].rincian.stok_merch) {
                swap(katalog_sort[j], katalog_sort[j + 1]);
            }
        }
    }
}

void search_nama_merch(Merchandise katalog_search[], int panjang_array_search) { 
    string cari;
    bool found = false;
    int count = 0;
    cls();
    cout << "==============================================" << endl;
    cout << "       Cari Merchandise berdasarkan Nama      " << endl;
    cout << "==============================================" << endl;
    cout << "Masukkan nama merchandise (minimal 3 huruf): ";
    getline(cin, cari);

    if (cari.length() < 3) {
        cout << "Minimal 3 huruf untuk mencari!" << endl;
        cout << "----------------------------------------------" << endl;
        system("pause");
        return;
    }

    string cari_lower = cari;
    for (char& c : cari_lower) {
        c = tolower(c);
    }

    cout << "\nHasil Pencarian:" << endl;
    cout << "----------------------------------------------" << endl;

    Table hasilCari;
    hasilCari.add_row({"No.", "Nama Merchandise", "Harga", "Stok", "Edisi"});
     hasilCari[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);


    for (int i = 0; i < panjang_array_search; i++) {
        string nama_lower = katalog_search[i].nama_merch;
        for (char& c : nama_lower) {
            c = tolower(c);
        }

        if (nama_lower.find(cari_lower) != string::npos) {
            found = true;
            count++;
            hasilCari.add_row({
                to_string(count),
                katalog_search[i].nama_merch,
                "Rp" + to_string(katalog_search[i].rincian.harga_merch),
                to_string(katalog_search[i].rincian.stok_merch),
                to_string(katalog_search[i].edisi_merch)
            });
        }
    }
    
    if (!found) {
        cout << "Merchandise tidak ditemukan!" << endl;
    } else {
        hasilCari.format().font_align(FontAlign::center);
        cout << hasilCari << endl;
        cout << "Ditemukan " << count << " merchandise" << endl;
    }
    cout << "----------------------------------------------" << endl;
    system("pause");
}

// menu sorting merchandise ꒰✿´ ꒳ ` ꒱♡
void menu_sorting_merch(Merchandise katalog_sort_menu[], int panjang_array_sort_menu) { 
    cls();
    try {
        int pilih_sort_merch;
        cout << "==============================================" << endl;
        cout << "           Menu Sorting Merchandise           " << endl;
        cout << "==============================================" << endl;
        cout << "1. Nama Merchandise (Z ke A) " << endl;
        cout << "2. Harga Merchandise (Termurah ke Termahal)" << endl;
        cout << "3. Stok Merchandise (Sedikit ke Terbanyak)" << endl;
        cout << "Masukan pilihan: ";

        if (!(cin >> pilih_sort_merch)) {
            throw runtime_error("Input pilihan harus berupa angka!");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (pilih_sort_merch < 1 || pilih_sort_merch > 3) {
            throw runtime_error("Pilihan sorting tidak valid!");
        }

        cout << "----------------------------------------------" << endl;
        
        switch (pilih_sort_merch) {
        case 1:
            cls();
          
            cout << "===========================================================================" << endl;
            cout << "             Berikut Sorting Merchandise Berdasarkan Nama (Z-A)                  " << endl;
            cout << "===========================================================================" << endl;
            bubbleSort_nama_merch(katalog_sort_menu, panjang_array_sort_menu);
            break;
        case 2:
            cls();
            
            cout << "===========================================================================" << endl;
            cout << "             Berikut Sorting Merchandise Berdasarkan Harga                       " << endl;
            cout << "===========================================================================" << endl;
            bubbleSort_harga_merch(katalog_sort_menu, panjang_array_sort_menu);
            break;  
        case 3:
            cls();
            
            cout << "===========================================================================" << endl;
            cout << "             Berikut Sorting Merchandise Berdasarkan Stok                        " << endl;
            cout << "===========================================================================" << endl;
            bubbleSort_stok_merch(katalog_sort_menu, panjang_array_sort_menu);
            
            break;
        }
        katalog_merchandise(katalog_sort_menu, panjang_array_sort_menu); 
    } catch (const exception& e) {
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        showError(e.what());
        system("pause");
    }
}

void menu_admin(Table& tabeladmin_ref) { 
    tabeladmin_ref = Table();
    tabeladmin_ref.add_row({"Menu Admin - Manajemen Merchandise"});
    tabeladmin_ref.add_row({"1. Merchandise Baru"});
    tabeladmin_ref.add_row({"2. Katalog Merchandise"});
    tabeladmin_ref.add_row({"3. Update Merchandise"});
    tabeladmin_ref.add_row({"4. Hapus dari Katalog Merchandise"});
    tabeladmin_ref.add_row({"5. Sorting Merchandise"});
    tabeladmin_ref.add_row({"6. Cari Merchandise"});
    tabeladmin_ref.add_row({"7. Logout"});

    tabeladmin_ref[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::red);
    for (size_t i = 1; i < tabeladmin_ref.size(); ++i) {
        tabeladmin_ref[i].format().font_align(FontAlign::left); 
    }
    tabeladmin_ref.format()
        .corner("=")
        .border_color(Color::red);
}

// menu utama admin dengan error handling
void menu_utama_admin(Merchandise katalog_admin[], int *panjang_array_admin_ptr) { 
    string pilihan_menu_merch_admin;
    int index_admin;
    
    do {
        cls();
        try {
            menu_admin(tabeladmin);
            cout << tabeladmin << endl;
            cout << "Masukan pilihan: ";
            getline(cin, pilihan_menu_merch_admin);
            cout << "----------------------------------------------" << endl;

            if (pilihan_menu_merch_admin == "1") {
                if (*panjang_array_admin_ptr >= max_merch) {
                    throw runtime_error("Kapasitas merchandise sudah penuh!");
                }
                tambah_merchandise(katalog_admin, panjang_array_admin_ptr);
            } else if (pilihan_menu_merch_admin == "2") {
                if (*panjang_array_admin_ptr == 0) {
                    throw runtime_error("Katalog merchandise masih kosong!");
                }
                cls();
                katalog_merchandise(katalog_admin, *panjang_array_admin_ptr);
            } else if (pilihan_menu_merch_admin == "3") {
                if (*panjang_array_admin_ptr == 0) {
                    throw runtime_error("Tidak ada merchandise yang bisa diupdate!");
                }
                update_merchandise(katalog_admin, panjang_array_admin_ptr, &index_admin);
            } else if (pilihan_menu_merch_admin == "4") {
                if (*panjang_array_admin_ptr == 0) {
                    throw runtime_error("Tidak ada merchandise yang bisa dihapus!");
                }
                hapus_merchandise(katalog_admin, panjang_array_admin_ptr, &index_admin);
            } else if (pilihan_menu_merch_admin == "5") {
                if (*panjang_array_admin_ptr == 0) {
                    throw runtime_error("Tidak ada merchandise yang bisa disorting!");
                }
                menu_sorting_merch(katalog_admin, *panjang_array_admin_ptr);
            } else if (pilihan_menu_merch_admin == "6") {
                if (*panjang_array_admin_ptr == 0) {
                    throw runtime_error("Tidak ada merchandise yang bisa dicari!");
                }
                search_nama_merch(katalog_admin, *panjang_array_admin_ptr);
            } else if (pilihan_menu_merch_admin == "7") {
                cls();
                cout << "Yippie! Logout berhasil!" << endl;
                cout << "----------------------------------------------" << endl;
                system("pause"); 
            } else {
                throw runtime_error("Pilihan menu admin tidak valid!");
                system("pause");
            }
        } catch (const exception& e) {
            cls(); 
            showError(e.what());
        }
    } while (pilihan_menu_merch_admin != "7");
}

void menu_user_display(Table& tabeluser_ref) {
    tabeluser_ref = Table();
    tabeluser_ref.add_row({"Menu User"});
    tabeluser_ref.add_row({"1. Lihat Katalog Merchandise"});
    tabeluser_ref.add_row({"2. Cari Merchandise"});
    tabeluser_ref.add_row({"3. Melakukan Pembelian"});
    tabeluser_ref.add_row({"4. Melihat Riwayat Pembelian"});
    tabeluser_ref.add_row({"5. Melihat Saldo"});
    tabeluser_ref.add_row({"6. Top Up Saldo"});
    tabeluser_ref.add_row({"7. Logout"});

    tabeluser_ref[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::green);
    for (size_t i = 1; i < tabeluser_ref.size(); ++i) {
        tabeluser_ref[i].format().font_align(FontAlign::left);
    }
    tabeluser_ref.format()
        .corner("=")
        .border_color(Color::green); 
}

void beli_merchandise(Merchandise katalog_beli[], int panjang_array_beli, int index_user_beli) {
    cls();
    katalog_merchandise(katalog_beli, panjang_array_beli); 
    try {
        int nomor_merch;
        int jumlah_beli;
        cout << "Masukkan nomor merchandise: ";
        if (!(cin >> nomor_merch)) {
             throw runtime_error("Input nomor harus berupa angka!");
             system("pause");
        }

        if (nomor_merch > 0 && nomor_merch <= panjang_array_beli) {
            cout << "Masukkan jumlah yang ingin dibeli: ";
            if (!(cin >> jumlah_beli)) {
                throw runtime_error("Input jumlah harus berupa angka!");
                system("pause");
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            if (jumlah_beli <= 0) {
                throw runtime_error("Jumlah pembelian harus positif!");
                system("pause");
            }

            if (jumlah_beli <= katalog_beli[nomor_merch - 1].rincian.stok_merch) {
                int total_harga = katalog_beli[nomor_merch - 1].rincian.harga_merch * jumlah_beli;
                if (user[index_user_beli].isiakun.saldo >= total_harga) {
                    user[index_user_beli].isiakun.saldo -= total_harga;
                    katalog_beli[nomor_merch - 1].rincian.stok_merch -= jumlah_beli;
                    
                    if(user[index_user_beli].jumlah_riwayat < 100) { 
                        user[index_user_beli].riwayat[user[index_user_beli].jumlah_riwayat].nama_merch = katalog_beli[nomor_merch - 1].nama_merch;
                        user[index_user_beli].riwayat[user[index_user_beli].jumlah_riwayat].jumlah = jumlah_beli;
                        user[index_user_beli].riwayat[user[index_user_beli].jumlah_riwayat].total_harga = total_harga;
                        user[index_user_beli].riwayat[user[index_user_beli].jumlah_riwayat].tanggal = time(0);
                        user[index_user_beli].jumlah_riwayat++;
                        cout << "Yippie! Pembelian berhasil!" << endl;
                        cout << "Sisa saldo: Rp " << user[index_user_beli].isiakun.saldo << endl;
                        system("pause");
                    } else {
                        cout << "Oopsie! Riwayat pembelian penuh." << endl;
                        system("pause");
                    }
                } else {
                    cout << "Oopsie! Saldo tidak mencukupi!" << endl;
                    system("pause");
                }
            } else {
                cout << "Oopsie! Jumlah tidak valid atau stok tidak mencukupi!" << endl;
                system("pause");
            }
        } else {
            cout << "Oopsie! Nomor merchandise tidak valid!" << endl;
        }
        cout << "----------------------------------------------" << endl;
    } catch (const exception& e) {
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        showError(e.what());
        system("pause");
    }
}

void lihat_saldo(int index_user_saldo) {
    cls();
    cout << "==============================================" << endl;
    cout << "                   Saldo Anda                 " << endl;
    cout << "==============================================" << endl;
    cout << "Saldo saat ini: Rp " << user[index_user_saldo].isiakun.saldo << endl;
    cout << "----------------------------------------------" << endl;
    system("pause");
}

void topup_saldo(int index_user_topup) {
    cls();
    int nominal;
    cout << "==============================================" << endl;
    cout << "                  Top Up Saldo                " << endl;
    cout << "==============================================" << endl;
    cout << "Saldo saat ini: Rp " << user[index_user_topup].isiakun.saldo << endl;
    cout << "Masukkan nominal top up: Rp ";
    
    if (!(cin >> nominal)) {
        cin.clear();
        showError("Nominal harus berupa angka!");
        system("pause");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        if (nominal > 0) {
            user[index_user_topup].isiakun.saldo = tambah(user[index_user_topup].isiakun.saldo, nominal); 
            cout << "Yippie! Top up berhasil!" << endl;
            cout << "Saldo sekarang: Rp " << user[index_user_topup].isiakun.saldo << endl;
            system("pause");
        } else {
            cout << "Oopsie! Nominal tidak valid (harus lebih dari 0)!" << endl;
            system("pause");
        }
    }
    cout << "----------------------------------------------" << endl;
}

void lihat_riwayat(int index_user_riwayat) {
    cls();
    Table tabelRiwayat;
    tabelRiwayat.add_row({"No", "Nama Merchandise", "Jumlah", "Total Harga", "Tanggal"});
    tabelRiwayat[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);

    if (user[index_user_riwayat].jumlah_riwayat == 0) {
        cout << "Belum ada riwayat pembelian." << endl;
    } else {
        for (int i = 0; i < user[index_user_riwayat].jumlah_riwayat; i++) {
            time_t waktu = user[index_user_riwayat].riwayat[i].tanggal;
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&waktu)); // Format tanggal
            string str_waktu(buffer);

            tabelRiwayat.add_row({
                to_string(i + 1),
                user[index_user_riwayat].riwayat[i].nama_merch,
                to_string(user[index_user_riwayat].riwayat[i].jumlah),
                "Rp" + to_string(user[index_user_riwayat].riwayat[i].total_harga),
                str_waktu
            });
        }
        for (size_t i = 1; i < tabelRiwayat.size(); ++i) {
            tabelRiwayat[i].format().font_align(FontAlign::center);
        }
        cout << tabelRiwayat << endl;
    }
    cout << "----------------------------------------------" << endl;
    system("pause");
}

bool login() {
    cls();
    int batas_percobaan_login = 1;
    string input_username, input_password;

    while (batas_percobaan_login > 0) {
        cout << "==============================================" << endl;
        cout << "       Selamat Datang di Halaman Login!       " << endl;
        cout << "==============================================" << endl;
        
        do {
            cout << "Username: ";
            getline(cin, input_username);
            if (input_username.empty()) {
                showError("Username tidak boleh kosong!");
                system("pause");
                continue;
            }
            break;
        } while (true);

        if (input_username.length() > 20) {
            cls();
            showError("Username maksimal 20 karakter!");
            system("pause");
            cls();
            continue;
        }

        do {
            cout << "Password: ";
            getline(cin, input_password);
            if (input_password.empty()) {
                showError("Password tidak boleh kosong!");
                system("pause");
                continue;
            }
            break;
        } while (true);

        if (input_password.length() > 20) {
            cls();
            showError("Password maksimal 20 karakter!");
            system("pause"); 
            cls();
            continue;
        }

        if (validasilogin(input_username, input_password)) {
            string user_role_loggedin;
            int index_user_aktif = -1;
            for (int i = 0; i < panjang_array_merch_akun; i++) {
                if (user[i].username == input_username) {
                    user_role_loggedin = user[i].role;
                    index_user_aktif = i;
                    break;
                }
            }

            cls();
            cout << "Yippie! Login berhasil sebagai " << user_role_loggedin << "!" << endl;
            cout << "----------------------------------------------" << endl;
            system("pause");


            if (user_role_loggedin == "admin") {
                menu_utama_admin(katalog, &panjang_array_merch);
            } else { // Regular user
                string pilihan_user_menu;
                do {
                    cls();
                    menu_user_display(tabeluser);
                    cout << tabeluser << endl;
                    cout << "Masukkan pilihan: ";
                    getline(cin, pilihan_user_menu);
                    cout << "----------------------------------------------" << endl;

                    if (pilihan_user_menu == "1") {
                        cls();
                        katalog_merchandise(katalog, panjang_array_merch);
                    } else if (pilihan_user_menu == "2") {
                        search_nama_merch(katalog, panjang_array_merch);
                    } else if (pilihan_user_menu == "3") {
                        if (panjang_array_merch == 0) {
                            cls();
                            showError("Maaf, tidak ada merchandise yang tersedia saat ini.");
                            system("pause");
                        } else {
                            beli_merchandise(katalog, panjang_array_merch, index_user_aktif);
                        }
                    } else if (pilihan_user_menu == "4") {
                        lihat_riwayat(index_user_aktif);
                    } else if (pilihan_user_menu == "5") {
                        lihat_saldo(index_user_aktif);
                    } else if (pilihan_user_menu == "6") {
                        topup_saldo(index_user_aktif);
                    } else if (pilihan_user_menu == "7") {
                        cls();
                        cout << "Yippie! Logout berhasil!" << endl;
                        cout << "----------------------------------------------" << endl;
                        system("pause");
                    } else {
                        cls();
                        showError("Pilihan gak valid nih! Coba lagi okai!");
                        system("pause");
                    }
                } while (pilihan_user_menu != "7");
            }
            return true; 
        } else {
            batas_percobaan_login--;
            cls();
            showError("Login gagal! Username atau Password salah.\nKesempatan login habis!");
            system("pause");
            if (batas_percobaan_login > 0) {
                 system("pause"); 
                 cls();
            } else {
            }
        }
    }
    return false;
}

bool registerUser() {
    cls();
    string new_username, new_password;
    cout << "==============================================" << endl;
    cout << "                Halaman Register              " << endl;
    cout << "==============================================" << endl;

    do {
        cout << "Masukkan username (maks 20 karakter, tanpa spasi): ";
        getline(cin, new_username);
        
        // Cek apakah username kosong
        if (new_username.empty()) {
            showError("Username tidak boleh kosong!");
            continue;
        }

        // Cek apakah username mengandung spasi
        if (new_username.find(' ') != string::npos) {
            showError("Username tidak boleh mengandung spasi!");
            continue;
        }

        break;
    } while (true);

    if (new_username.length() > 20) {
        cls(); 
        showError("Username maksimal 20 karakter!"); 
        system("pause"); 
        return false;
    }

    // Check existing username
    for (int i = 0; i < panjang_array_merch_akun; i++) {
        if (user[i].username == new_username) {
            cls();
            showError("Username sudah digunakan!");
            system("pause");
            return false;
        }
    }

    do {
        cout << "Masukkan password (maks 20 karakter, tanpa spasi): ";
        getline(cin, new_password);
        
        // Cek apakah password kosong
        if (new_password.empty()) {
            cls();
            showError("Password tidak boleh kosong!");
            system("pause");
            continue;
        }

        // Cek apakah password mengandung spasi
        if (new_password.find(' ') != string::npos) {
            showError("Password tidak boleh mengandung spasi!");
            continue;
        }

        break;
    } while (true);

    if (new_password.length() > 20) {
        cls();
        showError("Password maksimal 20 karakter!");
        system("pause");
        return false;
    }

    if (panjang_array_merch_akun < 30) { 
        user[panjang_array_merch_akun].username = new_username;
        user[panjang_array_merch_akun].password = new_password;
        user[panjang_array_merch_akun].role = "user";
        user[panjang_array_merch_akun].isiakun.saldo = 0;    
        user[panjang_array_merch_akun].jumlah_riwayat = 0; 
        panjang_array_merch_akun++;
        cls();
        cout << "==============================================" << endl;
        cout << "              Registrasi Berhasil!            " << endl;
        cout << "==============================================" << endl;
        cout << "Silakan login dengan akun baru Anda." << endl;
        system("pause");
        return true;
    } else {
        cls(); 
        showError("Kapasitas user penuh!"); 
        system("pause"); 
        return false;
    }
}

void tampilkanMenuUtamaLogin(Table& tabellogin_ref) { 
    tabellogin_ref = Table();
    tabellogin_ref.add_row({"MANAJEMEN MERCHANDISE MCLAREN"});
    tabellogin_ref.add_row({"1. Login"});
    tabellogin_ref.add_row({"2. Register"});
    tabellogin_ref.add_row({"3. Keluar Program"});

    tabellogin_ref[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::blue)
        .corner("=")
        .border_color(Color::magenta) 
        .corner_color(Color::magenta); 

    tabellogin_ref.format()
        .corner("=")
        .corner_color(Color::magenta)
        .border_color(Color::magenta)
        .font_align(FontAlign::center); 
}

void menuAwalRecursive() {
    cls();
    try {
        string main_choice;
        tampilkanMenuUtamaLogin(tabellogin);
        cout << tabellogin << endl;
        cout << "Pilihan: ";
        getline(cin, main_choice);

        if (main_choice.length() > 1 && main_choice != "1" && main_choice != "2" && main_choice != "3") {
            throw runtime_error("Input pilihan tidak valid (cukup 1 digit).");
        }

        if (main_choice == "1") {
            if (!login()) {
                menuAwalRecursive(); // Rekursif jika login gagal
            }
        } else if (main_choice == "2") {
            if (!registerUser()) {
                menuAwalRecursive(); // Rekursif jika registrasi gagal
            }
        } else if (main_choice == "3") {
            cls();
            cout << "==================================================" << endl;
            cout << " Terima kasih telah menggunakan program ini! Ciao! " << endl;
            cout << "==================================================" << endl;
            return; // Base case - keluar dari rekursi
        } else {
            throw runtime_error("Pilihan tidak valid!");
        }
    } catch (const exception& error) {
        cls();
        showError(error.what());
        system("pause");
        menuAwalRecursive(); // Rekursif jika terjadi error
    }
}

int main() {
    cout << "Selamat datang di Manajemen Merchandise McLaren!" << endl;
    cout << "----------------------------------------------" << endl;
    system("pause");
    
    // Memulai menu rekursif
    menuAwalRecursive();
    cls();
    cout << "\nProgram selesai." << endl;
    return 0;
}