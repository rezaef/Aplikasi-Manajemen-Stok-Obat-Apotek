#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// Deklarasi forward untuk pointer
typedef struct ElmObat *adr_obat;
typedef struct ElmApotik *adr_apotik;

// Struktur informasi untuk obat
struct InfoObat {
    string idObat;
    string namaObat;
    int stok;
};

// Struktur informasi untuk apotik
struct InfoApotik {
    string idApotik;
    string namaApotik;
    int jumlahJenisObat;
    int totalStok;
};

// List untuk menampung obat
struct ListObat {
    adr_obat first_Obat;
};

// List untuk menampung apotik
struct ListApotik {
    adr_apotik first_Apotik;
};

// Elemen untuk obat
struct ElmObat {
    InfoObat info;
    adr_obat next_obat;
};

// Elemen untuk apotik
struct ElmApotik {
    InfoApotik info;
    ListObat obat;
    adr_apotik next_apotik;
};


// Prototipe fungsi-fungsi yang akan diimplementasikan di apotik.cpp
void createListObat(ListObat &LO);
void createListApotik(ListApotik &LA);
adr_obat createElmObat(InfoObat info);
adr_apotik createElmApotik(InfoApotik info);
void insertObat(ListObat &LO, adr_obat o);
void insertApotik(ListApotik &LA, adr_apotik a);
adr_obat searchObat(ListObat LO, string idObat);
adr_apotik searchApotik(ListApotik LA, string idApotik);
void addObat(ListObat &LO, ListApotik &LA, string idObat, string idApotik);
void viewApotik(ListApotik &LA);
void viewObat(ListObat &LO);
void viewApotikObat(ListApotik &LA);
void displayApotikObat(ListApotik &LA);
void deleteAfterApotik(ListApotik &LA, string idApotik);
bool deleteApotik(ListApotik &LA, string idApotik);
void deleteAfterObat(ListObat &LO, string idObat);
bool deleteObat(ListObat &LO, ListApotik &LA, string idObat);
void updateStokObat(ListApotik &LA, string idApotik, string idObat, int jumlah);
void cariApotik(ListApotik &LA, string namaApotik);
void cariObat(ListApotik &LA, string namaObat);
void urutkanApotikBerdasarkanStok(ListApotik &LA);
void swap(InfoApotik &a, InfoApotik &b);
void setColor(int color);
void resetColor();
void displayASCIIArt();
void simpanData(ListApotik &LA);
void muatData(ListApotik &LA);
void bye();
void pressEnterToContinue();