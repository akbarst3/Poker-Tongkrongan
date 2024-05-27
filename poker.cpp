/*
file               : poker.cpp
author             : Muhammad Dzaki Nurhidayat (231511083)
                     Muhammad Fachry Khairiansyah (231511084)
                     Restu Akbar (231511088)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Games Poker Tongkrongan.
*/

#include "poker.h"

char type_assign (int jenis) {
    char tipe;
    switch (jenis) {
    case 1:
        return tipe = 'A';
    case 2:
        return tipe = 'B';
    case 3:
        return tipe = 'C';
    case 4:
        return tipe = 'D';
    }
}

void alloc_card (int nomor, int nilai, int jenis, nodeKartu **newNode) { 
    char tipe;
    *newNode = (nodeKartu *) malloc(sizeof(nodeKartu));
    if (newNode == NULL)
    {
        printf("Memory Sudah Full");
    }
    else
    {
        tipe = type_assign(jenis);
        (*newNode)->nomorKartu = nomor;
        (*newNode)->nilaiKartu = nilai;
        (*newNode)->tipeKartu = tipe;
        (*newNode)->next = NULL;
    }
}

// void fill_the_card (nodeKartu **firstDek, nodeKartu **lastDek) {
void fill_the_card(pointKartu *dekLL) {
    nodeKartu *newNode;
    int nomor = 1;
    int nilai = 3;
    int jenis = 1;

    while (jenis <= 4) {
        while (nilai <= 15) {
            alloc_card(nomor, nilai, jenis, &newNode);
            if (dekLL->head == NULL) {
                dekLL->head = newNode;
            } else {
                dekLL->tail->next = newNode;
            }
            dekLL->tail = newNode;
            nomor++;
            nilai++;
        }
        nilai = 3;
        jenis++;
    }
}

int count_card(nodeKartu *head)
{
    nodeKartu *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    count++;
    return count;
}

nodeKartu* get_node_at(nodeKartu *head, int index) {
    nodeKartu *current = head;
    int count = 0;
    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }
    return current;
}

void shuffle_deck(pointKartu *dekLL) {
    int count = count_card(dekLL->head);
    if (count < 2) return;
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        if (i != j) {
            // Tukar node ke-i dan node ke-j
            nodeKartu *node_i = get_node_at(dekLL->head, i);
            nodeKartu *node_j = get_node_at(dekLL->head, j);

            int temp_nilai = node_i->nilaiKartu;
            int temp_jenis = node_i->tipeKartu;
            node_i->nilaiKartu = node_j->nilaiKartu;
            node_i->tipeKartu = node_j->tipeKartu;
            node_j->nilaiKartu = temp_nilai;
            node_j->tipeKartu = temp_jenis;
        }
    }
}

void alloc_player (nodePemain **newNode, char nama[]) { 
    *newNode = (nodePemain *) malloc(sizeof(nodePemain));
    if (newNode == NULL)
    {
        printf("Memory Sudah Full");
    }
    else
    {
        strcpy((*newNode)->nama, nama);
        (*newNode)->kartu = {NULL, NULL};
        (*newNode)->pemain = NULL;
    }
}

void create_player (nodePemain **temp, char nama[]) {
    char *computer_names[] = {"Com1", "Com2", "Com3"};
    nodePemain *newNode, *ujung;
    ujung = *temp;

    // Untuk Player
    alloc_player(&newNode, nama);
    *temp = newNode;
    ujung = newNode;

    // Untuk Computer
    for (int i = 0; i < 3; i++) {
        alloc_player(&newNode, computer_names[i]);
        (*temp)->pemain = newNode;
        *temp = newNode;
    }

    (*temp)->pemain = ujung;
    *temp = ujung;
}

void display_node (nodeKartu *head) { 
    nodeKartu *temp = head;
    printf("Linked List = ");
    while (temp != NULL) {
        printf("%d | %c | %d -> ", temp->nomorKartu, temp->tipeKartu, temp->nilaiKartu);
        temp = temp->next;
    }
    printf("NULL\n");
}

void print_players(nodePemain *head) {
    if (head == NULL) return;
    nodePemain *current = head;
    do {
        printf("\nPemain : %s\n", current->nama);
        display_node((current)->kartu.head);
        current = current->pemain;
    } while (current != head);
}

void insert_last(pointKartu *llKartu, nodeKartu *newNode) {
    if (llKartu->tail != NULL) {
        llKartu->tail->next = newNode;
    }
    llKartu->tail = newNode;
    newNode->next = NULL;

    if (llKartu->head == NULL) {
        llKartu->head = newNode;
    }
}

void insert_order(pointKartu *llKartu, nodeKartu *newNode) {
    if (llKartu->head == NULL) {
        // Linked list kosong
        llKartu->head = newNode;
        llKartu->tail = newNode;
        newNode->next = NULL;
    } else if (newNode->nilaiKartu <= llKartu->head->nilaiKartu) {
        // Insert di depan
        newNode->next = llKartu->head;
        llKartu->head = newNode;
    } else {
        // Insert di tengah atau belakang
        nodeKartu *current = llKartu->head;
        while (current->next != NULL && current->next->nilaiKartu < newNode->nilaiKartu) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;

        // Update tail jika newNode dimasukkan di belakang
        if (newNode->next == NULL) {
            llKartu->tail = newNode;
        }
    }
}

void assign_number (nodeKartu *head) { 
    nodeKartu *temp = head;
    int count = 1;
    while (temp != NULL) {
        temp->nomorKartu = count;
        count++;
        temp = temp->next;
    }
}

void fill_deck(nodePemain **aktif, pointKartu *dekLL) {
    nodeKartu *temp;
    int i, totalCard;

    for (i = 1; i <= 4; i++) {
        totalCard = 0; // Inisialisasi totalCard dengan 0
        printf("Distribusi kartu untuk pemain %d: %s\n", i, (*aktif)->nama);
        while (totalCard < 13) { // Kondisi loop berubah ke < 13
            if (dekLL->head == NULL) {
                printf("Deck kosong!\n");
                return;
            }
            // Ambil kartu dari deck
            temp = dekLL->head;
            dekLL->head = dekLL->head->next;
            temp->next = NULL;

            // Masukkan kartu ke pemain
            insert_order(&((*aktif)->kartu), temp);

            printf("Kartu %d: %d | %c\n", totalCard + 1, temp->nilaiKartu, temp->tipeKartu); // Debugging line
            totalCard++;
        }
        printf("Kartu pemain %s setelah distribusi:\n", (*aktif)->nama);
        assign_number((*aktif)->kartu.head);
        display_node((*aktif)->kartu.head); // Pastikan nama fungsi benar, display_node atau displayNode
        *aktif = (*aktif)->pemain;  // Pindah ke pemain berikutnya
    }
}

nodePemain *first_play(nodePemain *aktif) {
    nodePemain *winner = NULL;
    nodeKartu *temp, *prev;
    int i, totalCard;

    for (i = 1; i <= 4; i++) {
        temp = aktif->kartu.head;
        prev = NULL;
        totalCard = 0; 
        while (totalCard < 13 && temp != NULL) {  // Corrected condition: < 13 instead of <= 13
            printf("Nilai = %d\n", temp->nilaiKartu); // Debugging line

            if (temp->nilaiKartu == 3) {
                printf("Singa\n"); // Debugging line
                // Menetapkan pemenang jika tipeKartu adalah 'D'
                if (temp->tipeKartu == 'D') {
                    winner = aktif;
                }

                // Menghapus node dari linked list
                nodeKartu* nodeToFree = temp;
                if (temp == aktif->kartu.head) {
                    aktif->kartu.head = temp->next;
                    if (aktif->kartu.head == NULL) {
                        aktif->kartu.tail = NULL;
                    }
                    temp = temp->next; // Move to the next node
                } else if (temp == aktif->kartu.tail) {
                    prev->next = NULL;
                    aktif->kartu.tail = prev;
                    temp = NULL; // End the loop
                } else {
                    if (prev != NULL) {
                        prev->next = temp->next;
                    }
                    temp = temp->next; // Move to the next node
                }
                free(nodeToFree);
            } else {
                prev = temp;
                temp = temp->next;
            }
            totalCard++;
        }
        // Pindah ke pemain berikutnya dalam linked list circular
        aktif = aktif->pemain;
    }
    return winner;
}

void display_card(nodeKartu *card) {
    printf("----------\n");
    printf("|%6d |\n", card->nomorKartu);
    printf("|%-8s|\n", card->tipeKartu);
    printf("|%6d |\n", card->nilaiKartu);
    printf("----------\n");
}

void display_player(nodeKartu *head) {
    nodeKartu *current = head;
    int count = 0;
    while (current != NULL && count < 13) {
        display_card(current);
        current = current->next;
        count++;
    }
}

int get_card_count(nodeKartu *head) {
    int count = 0;
    nodeKartu *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void print_players2(nodePemain *head) {
    if (head == NULL) return;
    
    nodePemain *current = head;

    // Bagian Atas - Komputer
    printf("\nKomputer:\n");
    do {
        printf("----------\n");
        printf("| %-6s |\n", current->nama);
        if (current->kartu.head != NULL) {
            printf("| Total: %2d |\n", get_card_count(current->kartu.head));
        } else {
            printf("| No cards |\n");
        }
        printf("----------\n");
        current = current->pemain;
    } while (current != head && strncmp(current->nama, "player", 6) != 0);
    
    // // Bagian Tengah - Table (Kosong untuk saat ini)
    // printf("\nTable:\n");
    // printf("----------\n");
    // printf("|        |\n");
    // printf("|        |\n");
    // printf("|        |\n");
    // printf("----------\n");

    // // Bagian Bawah - Pemain
    // printf("\nPlayer:\n");
    // current = head;
    // do {
    //     if (strncmp(current->nama, "Dzaki", 6) == 0) {
    //         printf("Nama: %s\n", current->nama);
    //         display_node(current->kartu.head);
    //     }
    //     current = current->pemain;
    // } while (current != head);
}

int cek_aturan(nodeMeja *dek)
{
    if (is_it_high_card(dek->kartu))
    {
        return highCard;
    }
    else if (is_it_one_pair(dek->kartu))
    {
        return onePair;
    }
    else if (is_it_two_pair(dek->kartu))
    {
        return twoPair;
    }
    else if (is_it_three_of_a_kind(dek->kartu))
    {
        return threeOfaKind;
    }
    else if (is_it_straight(dek->kartu))
    {
        return straight;
    }
    else if (is_it_flush(dek->kartu))
    {
        return flush;
    }
    else if (is_it_full_house(dek->kartu))
    {
        return fullHouse;
    }
    else if (is_it_four_of_a_kind(dek->kartu))
    {
        return fourOfaKind;
    }
    else if (is_it_straight_flush(dek->kartu))
    {
        return straightFlush;
    }
    else if (is_it_royal_flush(dek->kartu))
    {
        return royalFlush;
    }
    else
    {
        return 0;
    }
}

bool is_it_high_card(nodeKartu *head)
{
    if (head->next == NULL)
    {
        return true;
    }
    return false;
}

bool is_it_one_pair(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 2)
    {
        if (head->nilaiKartu == head->next->nilaiKartu)
        {
            return true;
        }
    }
    return false;
}

bool is_it_two_pair(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 4)
    {
        nodeKartu *temp = head;
        int pair = 0;
        int lastVal = 1; // Nilai yang tidak mungkin untuk kartu
        while (temp != NULL && temp->next != NULL)
        {
            if (temp->nilaiKartu == temp->next->nilaiKartu)
            {
                if (temp->nilaiKartu != lastVal)
                {
                    pair++;
                    lastVal = temp->nilaiKartu;
                    if (pair == 2)
                    {
                        return true;
                    }
                    temp = temp->next;
                }
            }
            temp = temp->next;
        }
    }
    return false;
}

bool is_it_three_of_a_kind(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 3)
    {
        nodeKartu *temp = head;
        if (temp->nilaiKartu == temp->next->nilaiKartu == temp->next->next->nilaiKartu)
        {
            return true;
        }
    }

    return false;
}

bool is_it_straight(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 5)
    {
        nodeKartu *temp = head;
        while (temp->next != NULL)
        {
            if (temp->nilaiKartu + 1 != temp->next->nilaiKartu)
            {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
    return false;
}

bool is_it_flush(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 5)
    {
        nodeKartu *temp = head;
        while (temp->next != NULL)
        {
            if (temp->tipeKartu != temp->next->tipeKartu)
            {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
    return false;
}

bool is_it_full_house(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 5)
    {
        int frekuensi[16] = {0};

        nodeKartu *temp = head;
        while (temp != NULL)
        {
            if (temp->nilaiKartu < 2 || temp->nilaiKartu > 15)
            {
                return false;
            }
            frekuensi[temp->nilaiKartu]++;
            temp = temp->next;
        }

        int hitungTiga = 0;
        int hitungDua = 0;

        for (int i = 1; i <= 15; i++)
        {
            if (frekuensi[i] == 3)
            {
                hitungTiga++;
            }
            else if (frekuensi[i] == 2)
            {
                hitungDua++;
            }
        }
        return (hitungTiga == 1 && hitungDua == 1);
    }
    return false;
}

bool is_it_four_of_a_kind(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 4)
    {
        int nilai = head->nilaiKartu;
        nodeKartu *temp = head;
        while (temp != NULL)
        {
            if (temp->nilaiKartu != nilai)
            {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    return false;
}
bool is_it_straight_flush(nodeKartu *head)
{
    if (is_it_flush(head) && is_it_straight(head))
    {
        return true;
    }
    return false;
}

bool is_it_royal_flush(nodeKartu *head)
{
    if (is_it_flush(head))
    {
        nodeKartu *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        if (temp->nilaiKartu == Two)
        {
            return true;
        }
    }
    return false;
}

bool is_it_bomb(nodeKartu *headTemp, nodeKartu *headMeja)
{
    if (is_it_high_card(headMeja))
    {
        if (headMeja->nilaiKartu == Two)
        {
            if (is_it_four_of_a_kind(headTemp))
            {
                return true;
            }
        }
    }
    return false;
}

int compare_Meja(nodeMeja *asli, nodeMeja *sementara)
{
    int cekBreak = 0;
    // Jika cekBreak = 2, maka game akan selesai (bom)
    // Jika cekBreak = 1, maka akan terjadi perpindahan dari dek meja sementara menjadi dek meja asli
    // Jika cekBreak = 0, maka tidak akan terjadi perpindahan 
    if (asli->aturan == 0)
    {
        asli->aturan = sementara->aturan;
        asli->nilaiTertinggi = sementara->nilaiTertinggi;
        asli->kartu = sementara->kartu;
        cekBreak = 1;
        return cekBreak;
    }

    if (asli->nilaiTertinggi == Two && sementara->aturan == fourOfaKind && asli->aturan == highCard) // pengecekan bom
    {
        asli->aturan = sementara->aturan;
        asli->nilaiTertinggi = sementara->nilaiTertinggi;
        asli->kartu = sementara->kartu;
        cekBreak = 2;
        return cekBreak;
    }

    if (asli->nilaiTertinggi < sementara->nilaiTertinggi && asli->aturan == sementara->aturan)
    {
        
        asli->nilaiTertinggi = sementara->nilaiTertinggi;
        asli->kartu = sementara->kartu;
        cekBreak = 1;
        return cekBreak;
    }

    if (asli->nilaiTertinggi > sementara->nilaiTertinggi && asli->aturan == sementara->aturan)
    {
        cekBreak = 0;
        return cekBreak;
    }
    return cekBreak;
}