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

#define highCard 1
#define onePair 2
#define twoPair 3
#define threeOfaKind 4
#define straight 5
#define flush 6
#define fullHouse 7
#define straightFlush 8
#define royalFlush 9
#define fourOfaKind 10
#define bomb 20

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

typedef struct pointKartu {
    nodeKartu *head;
    nodeKartu *tail;
} pointKartu;

void insert_order(pointKartu *llKartu, nodeKartu *newNode);
int count_card(nodeKartu *dek);
int cek_aturan(nodeMeja *dek);
bool is_it_high_card(nodeKartu *head);
bool is_it_one_pair(nodeKartu *head);
bool is_it_two_pair(nodeKartu *head);
bool is_it_three_of_a_kind(nodeKartu *head);
bool is_it_straight(nodeKartu *head);
bool is_it_flush(nodeKartu *head);
bool is_it_full_house(nodeKartu *head);
bool is_it_four_of_a_kind(nodeKartu *head);
bool is_it_straight_flush(nodeKartu *head);
bool is_it_royal_flush(nodeKartu *head);

int compare_Meja(nodeMeja *asli, nodeMeja *sementara);

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