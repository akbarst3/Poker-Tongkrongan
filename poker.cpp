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

// void randomize_card (nodeKartu *dek) {
    
// }

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

void print_players(nodePemain *head) {
    if (head == NULL) return;
    nodePemain *current = head;
    do {
        printf("Nama Pemain: %s\n", current->nama);
        current = current->pemain;
    } while (current != head);
}

void displayNode (nodeKartu *head) { 
    nodeKartu *temp = head;
    printf("Linked List = ");
    while (temp != NULL) {
        printf("%d | %c | %d -> ", temp->nomorKartu, temp->tipeKartu, temp->nilaiKartu);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insert_last(pointKartu *llKartu, nodeKartu *newNode)
{
    llKartu->tail->next = newNode;
    llKartu->tail = newNode;
    newNode->next = NULL;
}

void insert_order(pointKartu *llKartu, nodeKartu *newNode)
{
    printf("Tes4");
    if (llKartu->head == NULL && llKartu->tail == NULL)
    {
        llKartu->head = newNode;
        llKartu->tail = newNode;
        printf("Tes4");
    }
    else if (llKartu->head == llKartu->tail)
    {
        if (newNode->nilaiKartu > llKartu->head->nilaiKartu)
        {
            insert_last(llKartu, newNode);
        }
        else
        {
            newNode->next = llKartu->head;
            llKartu->head = newNode;
        }
    }
    else if (llKartu->tail->nilaiKartu > newNode->nilaiKartu)
    {
        nodeKartu *temp = llKartu->head;
        while (temp->next != llKartu->tail)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = llKartu->tail;
    }
    else
    {
        insert_last(llKartu, newNode);
    }
}

void fill_deck(nodePemain **aktif, pointKartu *dekLL) {
    nodeKartu *temp;
    int i, totalCard;
    totalCard = 1; 
    i = 1;
    while (i <= 4)
    {
        printf("Tes1");
        while (totalCard <= 13)
        {
            printf("Tes2");
            if (dekLL->head == NULL) {
                printf("Deck is empty!\n");
                return;
            }
            temp = dekLL->head;
            dekLL->head = dekLL->head->next;
            temp->next = NULL;
            insert_order(&((*aktif)->kartu), temp);
            printf("Tes3");
            totalCard++;
        }
        printf("\nPemain %d: %s\n", i, (*aktif)->nama);
        displayNode((*aktif)->kartu.head);
        *aktif = (*aktif)->pemain;
        totalCard = 1;
        i++;
    }
}

int main() {
    pointKartu dekLL = {NULL, NULL};
    nodePemain *aktif = NULL;

    fill_the_card(&dekLL);
    displayNode(dekLL.head);

    create_player(&aktif, "Dzaki");
    print_players(aktif);
    fill_deck(&aktif, &dekLL);
    printf("Tes");
}

int count_card(nodeKartu *head)
{
    nodeKartu *temp = head;
    int count = 0;
    while (temp != head)
    {
        count++;
        temp = temp->next;
    }
    count++;
    return count;
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