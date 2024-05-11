/*
file               : poker.h
author             : Muhammad Dzaki Nurhidayat (231511083)
                     Muhammad Fachry Khairiansyah (231511084)
                     Restu Akbar (231511088)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Games Poker Tongkrongan.                 
*/

// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi dan Deklarasi
#define Jack 11
#define Queen 12
#define King 13
#define As 14
#define Two 15

typedef struct nodePemain {
    char nama[100];
    int posisi;
    int ronde;
} nodePemain;

typedef struct nodeKartu {
    int nomorKartu;
    int nilaikartu;
    int TipeKartu;
    struct nodeKartu *next;
} nodeKartu;

typedef struct nodeMeja {
    int aturan;
    int nilaiTertinggi;
    struct nodeKartu *kartu;
} nodeMeja;


// Pemain akan dibuat dalam bentuk circular singly linked list
// Meja dan dek akan dibuat dalam bentuk linear singly linked list

// List Modul
/*
A. Tampilan
void welcome();
void winner();
void draw();
void lose();
void help();
void Gambaran di Meja
Void Gambaran di dek pemain
Void Gambaran di dek komputer

B. Modul Prosedur
Kocokan kartu (3 sampai 15) = Langsung kocok dari array yang kita punya secara random, tapi nilai yang sama gak bisa dapet lagi
Mengeluarkan kartu bernilai 3 yang ada di dek pemain, pemain yang memiliki kartu 3 bertipe skop akan memulai permainan (Nilai Kembalian NodePemain yang menang)
Bagi kartu secara rata sebanyak 13 kartu ke semua pemain
Memilih kartu dan memasukkan nya ke dek sementara
mengeluarkan kartu pertama bagi pemain dan komputer
Melawan kartu yang sudah ada di meja dibuat pemain dan komputer

C. Modul Fungsi
Buat masing-masing satu fungsi aturan poker
Buat satu fungsi yang bakal cek satu-satu semua fungsi aturan yang udah dibuat
Buat fungsi pengecekan pemenang
Permainan akan berhenti ketika pemain menang pada posisi 1-3 atau ketika pemain kalah menjadi posisi 4

*/