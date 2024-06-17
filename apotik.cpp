#include "apotik.h"

// Fungsi untuk mengatur warna
void setColor(int color) {
    cout << "\033[" << color << "m";
}

// Fungsi untuk reset warna
void resetColor() {
    cout << "\033[0m";
}

void createListObat(ListObat &LO) {
    LO.first_Obat = NULL;
}

void createListApotik(ListApotik &LA) {
    LA.first_Apotik = NULL;
}

adr_obat createElmObat(InfoObat info) {
    adr_obat newObat = new ElmObat;
    newObat->info = info;  // Stok sudah termasuk dalam info
    newObat->next_obat = nullptr;
    return newObat;
}

adr_apotik createElmApotik(InfoApotik info) {
    adr_apotik a = new ElmApotik;
    a->info = info;
    a->info.jumlahJenisObat = 0;
    a->info.totalStok = 0;
    a->obat.first_Obat = NULL;
    a->next_apotik = NULL;
    return a;
}


void insertObat(ListObat &LO, adr_obat o) {
    if (LO.first_Obat == nullptr) {
        LO.first_Obat = o;
    } else {
        adr_obat p = LO.first_Obat;
        while (p->next_obat != nullptr) {
            p = p->next_obat;
        }
        p->next_obat = o;
    }
}

void insertApotik(ListApotik &LA, adr_apotik a) {
    if (LA.first_Apotik == NULL) {
        LA.first_Apotik = a;
    } else {
        adr_apotik q = LA.first_Apotik;
        while (q->next_apotik != NULL) {
            q = q->next_apotik;
        }
        q->next_apotik = a;
    }
}

adr_obat searchObat(ListObat LO, string idObat) {
    adr_obat o = LO.first_Obat;
    while (o != NULL && o->info.idObat != idObat) {
        o = o->next_obat;
    }
    return o;
}

// Implementasi fungsi pencarian apotik
adr_apotik searchApotik(ListApotik LA, string idApotik) {
    adr_apotik a = LA.first_Apotik;
    while (a != NULL && a->info.idApotik != idApotik) {
        a = a->next_apotik;
    }
    return a;
}

// Implementasi fungsi menambahkan obat ke apotik
void addObat(ListObat &LO, ListApotik &LA, string idObat, string idApotik) {
    adr_obat o = searchObat(LO, idObat);
    adr_apotik a = searchApotik(LA, idApotik);
    if (o != NULL && a != NULL) {
        adr_obat found = searchObat(a->obat, idObat);
        if (found == NULL) {
            InfoObat newInfo = o->info;  // Salin informasi obat, termasuk stok
            adr_obat newObat = createElmObat(newInfo);
            insertObat(a->obat, newObat);
            a->info.jumlahJenisObat++;  // Perbarui jumlah jenis obat
        } else {
            cout << "Obat sudah ada di apotik ini." << endl;
        }
    } else {
        if (o == NULL) cout << "Obat tidak ditemukan." << endl;
        if (a == NULL) cout << "Apotik tidak ditemukan." << endl;
    }
}



// Implementasi fungsi menampilkan semua apotik
void viewApotik(ListApotik &LA) {
    cout << left << setw(15) << "ID Apotik" << setw(25) << "Nama Apotik" << endl;
    cout << "-------------------------------------" << endl;
    adr_apotik a = LA.first_Apotik;
    while (a != NULL) {
        cout << left << setw(15) << a->info.idApotik << setw(25) << a->info.namaApotik << endl;
        a = a->next_apotik;
    }
}

// Implementasi fungsi menampilkan semua obat
void viewObat(ListObat &LO) {
    cout << left << setw(15) << "ID Obat" << setw(25) << "Nama Obat" << endl;
    cout << "-----------------------------------" << endl;
    adr_obat o = LO.first_Obat;
    while (o != NULL) {
        cout << left << setw(15) << o->info.idObat << setw(25) << o->info.namaObat << endl;
        o = o->next_obat;
    }
}

// Implementasi fungsi menampilkan semua obat dalam apotik tertentu
void viewApotikObat(ListApotik &LA) {
    adr_apotik a = LA.first_Apotik;
    while (a != NULL) {
        cout << "Apotik: " << a->info.idApotik << " - " << a->info.namaApotik << endl;
        viewObat(a->obat);
        cout << endl;
        a = a->next_apotik;
    }
}

void displayApotikObat(ListApotik &LA) {
    adr_apotik a = LA.first_Apotik;
    setColor(96); 
    cout << "=====================================================================================" << endl;
    resetColor();
    setColor(92); 
    cout << "******************************* Daftar Apotik dan Obat ******************************" << endl;
    resetColor();
    setColor(96); 
    cout << "=====================================================================================" << endl;
    resetColor();

    if (a == NULL) {
        setColor(91); // Merah untuk teks "Tidak ada apotik tersedia."
        cout << "Tidak ada apotik tersedia." << endl;
        resetColor();
        return;
    }
    setColor(92);
    cout << left << setw(15) << "ID Apotik" << setw(15) << "Nama Apotik" << setw(20) << "Jumlah Obat" << setw(15) << "ID Obat" << setw(15) << "Nama Obat" << setw(15) << "Stok" << endl;
    setColor(96);
    cout << setfill('=') << setw(85) << "=" << setfill(' ') << endl;
    resetColor(); // Reset warna setelah header

    while (a != NULL) {
        bool first = true;
        adr_obat o = a->obat.first_Obat;
        if (o == NULL) {
            setColor(93);
            cout << left << setw(15) << a->info.idApotik << setw(15) << a->info.namaApotik << setw(20) << "0" << setw(15) << "N/A" << setw(15) << "Tidak ada obat" << setw(15) << "0" << endl;
        } else {
            while (o != NULL) {
                if (first) {
                    setColor(92); // Hijau untuk baris pertama obat
                    cout << left << setw(15) << a->info.idApotik << setw(15) << a->info.namaApotik << setw(20) << a->info.jumlahJenisObat << setw(15) << o->info.idObat << setw(15) << o->info.namaObat << setw(15) << o->info.stok << endl;
                    first = false;
                    resetColor();
                } else {
                    setColor(92); // Hijau untuk baris pertama obat
                    cout << setw(50) << " " << setw(15) << o->info.idObat << setw(15) << o->info.namaObat << setw(15) << o->info.stok << endl;
                    resetColor();
                }
                o = o->next_obat;
            }
        }
        setColor(96);
        cout << setfill('-') << setw(85) << "-" << setfill(' ') << endl; // Garis pemisah tanpa warna
        a = a->next_apotik;
    }
    resetColor();
}


// Implementasi fungsi menghapus apotik
void deleteAfterApotik(ListApotik &LA, string idApotik) {
    adr_apotik a = LA.first_Apotik;
    adr_apotik prev = NULL;
    while (a != NULL && a->info.idApotik != idApotik) {
        prev = a;
        a = a->next_apotik;
    }
    if (a != NULL) {
        if (prev == NULL) {
            LA.first_Apotik = a->next_apotik;
        } else {
            prev->next_apotik = a->next_apotik;
        }
        delete a;
    }
}

bool deleteApotik(ListApotik &LA, string idApotik) {
    adr_apotik prev = nullptr;
    adr_apotik current = LA.first_Apotik;
    while (current != nullptr) {
        if (current->info.idApotik == idApotik) {
            if (prev == nullptr) {
                LA.first_Apotik = current->next_apotik;
            } else {
                prev->next_apotik = current->next_apotik;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next_apotik;
    }
    return false;
}

// Implementasi fungsi menghapus obat dari apotik
void deleteAfterObat(ListObat &LO, string idObat) {
    adr_obat o = LO.first_Obat;
    adr_obat prev = NULL;
    while (o != NULL && o->info.idObat != idObat) {
        prev = o;
        o = o->next_obat;
    }
    if (o != NULL) {
        if (prev == NULL) {
            LO.first_Obat = o->next_obat;
        } else {
            prev->next_obat = o->next_obat;
        }
        delete o;
    }
}

bool deleteObat(ListObat &LO, ListApotik &LA, string idObat) {
    bool found = false;
    adr_obat prev = nullptr;
    adr_obat current = LO.first_Obat;
    int obatStok = 0; // Untuk menyimpan stok obat yang dihapus

    // Temukan dan hapus obat dari list global obat
    while (current != nullptr) {
        if (current->info.idObat == idObat) {
        adr_apotik apotik = LA.first_Apotik;
            obatStok = current->info.stok; // Simpan stok sebelum menghapus
            if (prev == nullptr) {
                LO.first_Obat = current->next_obat;
            } else {
                prev->next_obat = current->next_obat;
            }
            apotik->info.totalStok -= obatStok; // Kurangi total stok apotik
            delete current; // Hapus obat dari memori
            found = true;
            break;
        }
        prev = current;
        current = current->next_obat;
    }

    // Hapus referensi obat dari setiap apotik dan kurangi jumlah jenis obat dan total stok
    if (found) {
        adr_apotik apotik = LA.first_Apotik;
        while (apotik != nullptr) {
            adr_obat o = apotik->obat.first_Obat;
            adr_obat o_prev = nullptr;
            bool isObatFound = false; // Flag jika obat ditemukan dan dihapus

            while (o != nullptr) {
                if (o->info.idObat == idObat) {
                    obatStok = o->info.stok;
                    if (o_prev == nullptr) {
                        apotik->obat.first_Obat = o->next_obat;
                    } else {
                        o_prev->next_obat = o->next_obat;
                    }
                    delete o; // Hapus obat dari memori
                    isObatFound = true;
                    break;
                }
                o_prev = o;
                o = o->next_obat;
            }
            if (isObatFound) {
                apotik->info.jumlahJenisObat--;
                apotik->info.totalStok -= obatStok; // Kurangi total stok apotik
                cout << "Mengurangi stok: " << obatStok << " dari apotik: " << apotik->info.namaApotik << endl;
            }
            apotik = apotik->next_apotik;
        }
    }

    return found;
}



void updateStokObat(ListApotik &LA, string idApotik, string idObat, int jumlah) {
    adr_apotik apotik = searchApotik(LA, idApotik);
    if (apotik != nullptr) {
        adr_obat obat = searchObat(apotik->obat, idObat);
        if (obat != nullptr) {
            obat->info.stok += jumlah; // Update stok obat
            apotik->info.totalStok += jumlah; // Update total stok di apotik
        } else {
            cout << "Obat tidak ditemukan." << endl;
        }
    } else {
        cout << "Apotik tidak ditemukan." << endl;
    }
}

void displayASCIIArt() {
    setColor(93);
    cout << "'||    ||'     |     '|.   '|'     |        '||' '||''''|  '||    ||' '||''''|  '|.   '|'\n";
    cout << " |||  |||     |||     |'|   |     |||        ||   ||  .     |||  |||   ||  .     |'|   | \n";
    cout << " |'|..'||    |  ||    | '|. |    |  ||       ||   ||''|     |'|..'||   ||''|     | '|. | \n";
    cout << " | '|' ||   .''''|.   |   |||   .''''|.      ||   ||        | '|' ||   ||        |   ||| \n";
    cout << ".|. | .||. .|.  .||. .|.   '|  .|.  .||. || .|'  .||.....| .|. | .||. .||.....| .|.   '|\n";
    cout << "                                          '''                                            \n";
    cout << "                                                                                         \n";
    cout << "                   |     '||''|.   ..|''||   |''||''| '||''''|  '||'  |'                 \n";
    cout << "                  |||     ||   || .|'    ||     ||     ||  .     || .'                   \n";
    cout << "                 |  ||    ||...|' ||      ||    ||     ||''|     ||'|.                   \n";
    cout << "                .''''|.   ||      '|.     ||    ||     ||        ||  ||                  \n";
    cout << "               .|.  .||. .||.      ''|...|'    .||.   .||.....| .||.  ||.                \n\n";
    resetColor();
}

void simpanData(ListApotik &LA) {
    ofstream outFile("apotik_data.txt");
    if (!outFile) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    adr_apotik apotik = LA.first_Apotik;
    while (apotik != nullptr) {
        // Simpan ID Apotik, Nama Apotik, Jumlah Jenis Obat, dan Total Stok
        outFile << apotik->info.idApotik << ";" << apotik->info.namaApotik << ";"
                << apotik->info.jumlahJenisObat << ";" << apotik->info.totalStok << endl;
        adr_obat obat = apotik->obat.first_Obat;
        while (obat != nullptr) {
            outFile << obat->info.idObat << ";" << obat->info.namaObat << ";" << obat->info.stok << endl;
            obat = obat->next_obat;
        }
        outFile << "###" << endl;  // Tanda akhir list obat per apotik
        apotik = apotik->next_apotik;
    }

    outFile.close();
}

void muatData(ListApotik &LA) {
    ifstream inFile("apotik_data.txt");
    if (!inFile) {
        cout << "File tidak bisa dibuka" << endl;
        return;
    }

    string line;
    while (getline(inFile, line) && !line.empty()) {
        stringstream ss(line);
        string idApotik, namaApotik, temp;
        int jumlahJenisObat, totalStok;

        getline(ss, idApotik, ';');
        getline(ss, namaApotik, ';');
        getline(ss, temp, ';');
        jumlahJenisObat = stoi(temp);
        getline(ss, temp);
        totalStok = stoi(temp);

        adr_apotik apotik = createElmApotik({idApotik, namaApotik});
        apotik->info.jumlahJenisObat = jumlahJenisObat;
        apotik->info.totalStok = totalStok;  // Set total stok
        insertApotik(LA, apotik);

        while (getline(inFile, line) && line != "###") {
            stringstream ss2(line);
            string idObat, namaObat;
            int stok;
            getline(ss2, idObat, ';');
            getline(ss2, namaObat, ';');
            getline(ss2, temp);
            stok = stoi(temp);

            adr_obat obat = createElmObat({idObat, namaObat});
            obat->info.stok = stok;
            insertObat(apotik->obat, obat);
        }
    }
    inFile.close();
}


void bye() {
    setColor(96);
    cout << " ░▒▓███████▓▒░░▒▓██████▓▒░░▒▓██████████████▓▒░░▒▓███████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░ " << endl;
    cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ " << endl;
    cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ " << endl;
    cout << " ░▒▓██████▓▒░░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓████████▓▒░▒▓█▓▒░ " << endl;
    cout << "       ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ " << endl;
    cout << "       ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ " << endl;
    cout << "░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░ " << endl;
    cout << "                                                                                " << endl;
    cout << "                                                                                " << endl;
    cout << "             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓██████████████▓▒░░▒▓███████▓▒░ ░▒▓██████▓▒░  " << endl;
    cout << "             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ " << endl;
    cout << "             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ " << endl;
    cout << "             ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓████████▓▒░ " << endl;
    cout << "      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ " << endl;
    cout << "      ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ " << endl;
    cout << "       ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ " << endl;
    cout << "                                                                                " << endl;
    cout << "                                                                                " << endl;
    resetColor();
}

void cariApotik(ListApotik &LA, string idApotik) {
    adr_apotik apotik = searchApotik(LA, idApotik);
    if (apotik != nullptr) {
        setColor(92);  // Hijau untuk teks positif
        cout << "Apotik ditemukan:" << endl;
        cout << left << setw(15) << "ID Apotik: " << setw(30) << apotik->info.idApotik
             << "Nama Apotik: " << setw(30) << apotik->info.namaApotik << endl;
        cout << left << setw(15) << "Total Stok: " << setw(10) << apotik->info.totalStok
             << "Jumlah Jenis Obat: " << setw(10) << apotik->info.jumlahJenisObat << endl;
        resetColor();  // Reset warna ke default
    } else {
        setColor(91);  // Merah untuk teks peringatan
        cout << "Apotik dengan ID " << idApotik << " tidak ditemukan." << endl;
        resetColor();
    }
}

void cariObat(ListApotik &LA, string idObat) {
    bool found = false;  // Flag untuk mengecek apakah obat ditemukan di setidaknya satu apotik

    cout << "Hasil pencarian untuk obat dengan ID: " << idObat << endl;

    // Melintasi semua apotik untuk mencari obat
    for (adr_apotik apotik = LA.first_Apotik; apotik != nullptr; apotik = apotik->next_apotik) {
        // Melintasi daftar obat di setiap apotik
        for (adr_obat obat = apotik->obat.first_Obat; obat != nullptr; obat = obat->next_obat) {
            if (obat->info.idObat == idObat) {
                found = true;  // Menandai bahwa obat telah ditemukan
                // Tampilkan informasi obat dan apotik tempat obat itu tersedia
                setColor(92);  // Hijau untuk teks positif
                cout << "Ditemukan di Apotik: " << setw(30) << apotik->info.namaApotik << endl;
                cout << left << setw(15) << "ID Obat: " << setw(25) << obat->info.idObat
                     << "Nama Obat: " << setw(30) << obat->info.namaObat
                     << "Stok: " << obat->info.stok << endl;
                resetColor();  // Reset warna ke default
            }
        }
    }

    if (!found) {
        setColor(91);  // Merah untuk teks peringatan
        cout << "Obat dengan ID " << idObat << " tidak ditemukan di apotik manapun." << endl;
        resetColor();
    }
}

void urutkanApotikBerdasarkanStok(ListApotik &LA) {
    bool swapped;
    adr_apotik current;
    adr_apotik lastPtr = nullptr;

    if (LA.first_Apotik == nullptr) {
        cout << "Tidak ada apotik untuk diurutkan." << endl;
        return;
    }

    do {
        swapped = false;
        current = LA.first_Apotik;

        while (current->next_apotik != lastPtr) {
            if (current->info.totalStok < current->next_apotik->info.totalStok) {
                swap(current, current->next_apotik); // Perhatikan perubahan di sini
                swapped = true;
            }
            current = current->next_apotik;
        }
        lastPtr = current;
    } while (swapped);

    // Menampilkan header dan data dengan format rapi
    cout << "\nDaftar Apotik Berdasarkan Total Stok (Tertinggi ke Terendah):" << endl;
    cout << left << setw(15) << "ID Apotik" << setw(25) << "Nama Apotik" << setw(15) << "Total Stok" << endl;
    cout << string(55, '-') << endl; // Garis pemisah

    current = LA.first_Apotik;
    while (current != nullptr) {
        cout << left << setw(15) << current->info.idApotik
             << setw(25) << current->info.namaApotik
             << setw(15) << current->info.totalStok << endl;
        current = current->next_apotik;
    }
    cout << string(55, '-') << endl; // Garis penutup
}


void swap(InfoApotik &a, InfoApotik &b) {
    InfoApotik temp = a;
    a = b;
    b = temp;
}

void pressEnterToContinue() {
    cout << "Tekan enter untuk melanjutkan...";
    cin.get(); // Menunggu pengguna menekan enter
}