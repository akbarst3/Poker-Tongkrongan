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
#include <time.h>

// Definisi dan Deklarasi
#define Jack 11
#define Queen 12
#define King 13
#define As 14
#define Two 15

#define highCard 1
#define pair 2
#define threeOfaKind 3
#define straight 4
#define flush 5
#define fullHouse 6
#define fourOfaKind 7
#define straightFlush 8
#define royalFlush 9
#define totalKartu 52

typedef struct nodeKartu {
    int nomorKartu;
    int nilaiKartu;
    int tipeKartu;
    struct nodeKartu *next;
} nodeKartu;

typedef struct pointKartu {
    nodeKartu *head;
    nodeKartu *tail;
} pointKartu;

typedef struct nodePemain {
    char nama[100];
    struct pointKartu kartu;
    struct nodePemain *pemain;
} nodePemain;

typedef struct nodeMeja {
    int aturan;
    int nilaiTertinggi;
    struct pointKartu *llDeck;
} nodeMeja;

char type_assign (int jenis);
void alloc_card (int nomor, int nilai, int jenis, nodeKartu **newNode);
void fill_the_card(pointKartu *dekLL);
int count_card(nodeKartu *head);
nodeKartu* get_node_at(nodeKartu *head, int index);
void shuffle_deck(pointKartu *dekLL);
void alloc_player (nodePemain **newNode, char nama[]);
void create_player (nodePemain **temp, char nama[]);
void display_node (nodeKartu *head);
void print_players(nodePemain *head);
void insert_last(pointKartu *llKartu, nodeKartu *newNode);
void insert_order(pointKartu *llKartu, nodeKartu *newNode);
void assign_number (nodeKartu *head);
void fill_deck(nodePemain **aktif, pointKartu *dekLL);
nodePemain *first_play(nodePemain *aktif);
void display_card(nodeKartu *card);
void display_player(nodeKartu *head);
int get_card_count(nodeKartu *head);
void print_players2(nodePemain *head);

int cek_aturan(nodeMeja *dek, int *highest);
bool is_it_high_card(pointKartu *deck, int * highest);
bool is_it_pair(pointKartu *deck, int *highest);
bool is_it_three_of_a_kind(pointKartu *deck, int * highest);
bool is_it_straight(pointKartu *deck, int *highest);
bool is_it_flush(pointKartu *deck, int * highest);
bool is_it_full_house(pointKartu *deck, int *highest);
bool is_it_four_of_a_kind(pointKartu *deck, int * highest);
bool is_it_straight_flush(pointKartu *deck, int * highest);
bool is_it_royal_flush(pointKartu *deck, int * highest);

int compare_Meja(nodeMeja *asli, nodeMeja *sementara);
bool computer_turn(nodeMeja *dekMeja, nodeMeja *dekTemp, nodePemain *com);
void set_tail(pointKartu *llComb, int card);
void reset_ll_comb(pointKartu *llComb, nodePemain *com);
bool five_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp);
bool four_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp);
bool three_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp);
bool two_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp);
bool high_card_fight(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp);
void get_llComb(nodePemain *com, pointKartu *llComb, nodeMeja *dekMeja);


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