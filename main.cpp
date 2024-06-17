#include <iostream>
#include "apotik.h"
#include <iomanip>

int main() {
    ListApotik LA;
    ListObat LO;
    createListApotik(LA);
    createListObat(LO);
    muatData(LA);
    int pilihan;

    do {
        system("clear");
        displayASCIIArt();
        displayApotikObat(LA);

        cout << "\n";
        setColor(96);
        cout << "==============================================\n";
        setColor(93);
        cout << "\tMenu Manajemen Apotik dan Obat" << endl;
        setColor(96);
        cout << "==============================================\n";
        setColor(93);
        cout << setw(10) << " " << "1. Tambah Apotik" << endl;
        cout << setw(10) << " " << "2. Tambah Obat" << endl;
        cout << setw(10) << " " << "3. Tambah Obat ke Apotik" << endl;
        cout << setw(10) << " " << "4. Hapus Apotik" << endl;
        cout << setw(10) << " " << "5. Hapus Obat" << endl;
        cout << setw(10) << " " << "6. Update Stok Obat" << endl;
        cout << setw(10) << " " << "7. Cari Apotik Berdasarkan ID" << endl;
        cout << setw(10) << " " << "8. Cari Obat berdasarkan ID" << endl;
        cout << setw(10) << " " << "9. Urutan Apotik Dari Stok terbanyak" << endl;
        setColor(91);
        cout << setw(10) << " " << "0. Keluar" << endl;
        setColor(96);
        cout << "==============================================\n";
        setColor(93);
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();
        resetColor(); // Kembali ke warna default

        switch(pilihan) {
            case 1:
                {
                    string id, nama;
                    cout << "Masukkan ID Apotik: ";
                    getline(cin, id);
                    cout << "Masukkan Nama Apotik: ";
                    getline(cin, nama);
                    insertApotik(LA, createElmApotik({id, nama}));
                    cout << "Apotik berhasil ditambahkan." << endl;
                    pressEnterToContinue();
                break;
                }
            case 2:
                {
                    string id, nama;
                    cout << "Masukkan ID Obat: ";
                    getline(cin, id);
                    cout << "Masukkan Nama Obat: ";
                    getline(cin, nama);
                    insertObat(LO, createElmObat({id, nama}));
                    cout << "Obat berhasil ditambahkan." << endl;
                    pressEnterToContinue();
                break;
                }
            case 3:
                {
                    string idApotik, idObat;
                    cout << "Masukkan ID Apotik: ";
                    getline(cin, idApotik);
                    cout << "Masukkan ID Obat: ";
                    getline(cin, idObat);
                    addObat(LO, LA, idObat, idApotik);
                    pressEnterToContinue();
                break;
                }
           case 4: {
                    string id;
                    cout << "Masukkan ID Apotik yang ingin dihapus: ";
                    getline(cin, id);
                    char confirm;
                    cout << "Apakah Anda yakin ingin menghapus apotik ini? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        if (deleteApotik(LA, id)) {
                            cout << "Apotik berhasil dihapus." << endl;
                        } else {
                            cout << "Tidak ditemukan apotik dengan ID " << id << "." << endl;
                        }
                    }
                    cin.ignore(); // Penting untuk mengatasi newline di buffer
                    pressEnterToContinue();
                break;
                }
            case 5: {
                    string id;
                    cout << "Masukkan ID Obat yang ingin dihapus: ";
                    getline(cin, id);
                    char confirm;
                    cout << "Apakah Anda yakin ingin menghapus obat ini? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        if (deleteObat(LO, LA, id)) {
                            cout << "Obat berhasil dihapus." << endl;
                        } else {
                            cout << "Tidak ditemukan obat dengan ID " << id << "." << endl;
                        }
                    }
                    cin.ignore(); // Penting untuk mengatasi newline di buffer
                    pressEnterToContinue();
                    break;
                }
            case 6:
                {
                    string idApotik, idObat;
                    int jumlah;
                    cout << "Masukkan ID Apotik: ";
                    getline(cin, idApotik);
                    cout << "Masukkan ID Obat: ";
                    getline(cin, idObat);
                    cout << "Masukkan jumlah update stok (bisa negatif atau positif): ";
                    cin >> jumlah;
                    cin.ignore();
                    updateStokObat(LA, idApotik, idObat, jumlah);
                    pressEnterToContinue();
                    break;
                }
            case 7: {
                    string namaApotik;
                    cout << "Masukkan ID Apotik yang ingin dicari: ";
                    getline(cin, namaApotik);
                    cariApotik(LA, namaApotik);
                    pressEnterToContinue();
                    break;
                    }
            case 8: {
                    string namaObat;
                    cout << "Masukkan ID Obat yang ingin dicari: ";
                    getline(cin, namaObat);
                    cariObat(LA, namaObat);
                    pressEnterToContinue();
                    break;
                    }
            case 9: {
                    urutkanApotikBerdasarkanStok(LA);
                    pressEnterToContinue();
                    break;
            }
            case 0:
                simpanData(LA);
                system("clear");
                bye();
                setColor(93);
                cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
                resetColor();
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
