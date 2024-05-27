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

int count_card(nodeKartu *head) {
    int count = 0;
    nodeKartu *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
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
        totalCard = 0;
        printf("Distribusi kartu untuk pemain %d: %s\n", i, (*aktif)->nama);
        while (totalCard < 13) {
            if (dekLL->head == NULL) {
                printf("Deck kosong!\n");
                return;
            }
            temp = dekLL->head;
            dekLL->head = dekLL->head->next;
            temp->next = NULL;

            insert_order(&((*aktif)->kartu), temp);
            // printf("Kartu %d: %d | %c\n", totalCard + 1, temp->nilaiKartu, temp->tipeKartu);
            totalCard++;
        }
        printf("Kartu pemain %s setelah distribusi:\n", (*aktif)->nama);
        assign_number((*aktif)->kartu.head);
        display_node((*aktif)->kartu.head);
        *aktif = (*aktif)->pemain;
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
        while (totalCard < 13 && temp != NULL) { 
            // printf("Nilai = %d\n", temp->nilaiKartu);

            if (temp->nilaiKartu == 3) {
                printf("Singa\n");

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
                    temp = temp->next;
                } else if (temp == aktif->kartu.tail) {
                    prev->next = NULL;
                    aktif->kartu.tail = prev;
                    temp = NULL;
                } else {
                    if (prev != NULL) {
                        prev->next = temp->next;
                    }
                    temp = temp->next;
                }
                free(nodeToFree);
            } else {
                prev = temp;
                temp = temp->next;
            }
            totalCard++;
        }
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

void print_game_computers(nodePemain *head) {
    if (head == NULL) return;

    nodePemain *current = head;
    current = head;

    // Print header
    printf("Komputer:\n");
    do {
        printf("-------------\t");
        current = current->pemain;
    } while (current != head && strncmp(current->nama, "Dzaki", 6) != 0);
    printf("\n");

    current = head;
    do {
        printf("| %-9s |\t", current->nama);
        current = current->pemain;
    } while (current != head && strncmp(current->nama, "Dzaki", 6) != 0);
    printf("\n");

    current = head;
    do {
        if (current->kartu.head != NULL) {
            printf("| Sisa: %3d |\t", count_card(current->kartu.head));
        } else {
            printf("| No cards |\t");
        }
        current = current->pemain;
    } while (current != head && strncmp(current->nama, "Dzaki", 6) != 0);
    printf("\n");

    current = head;
    do {
        printf("-------------\t");
        current = current->pemain;
    } while (current != head && strncmp(current->nama, "Dzaki", 6) != 0);
    printf("\n");
}

void print_game_player(nodePemain *head){
    int count, i;
    if (head == NULL) return;

    nodePemain *current = head;
    while (current->pemain != head)
    {
        current = current->pemain;
    }
    nodeKartu *temp = current->kartu.head;
    do {
        printf("-------------\t");
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");

    temp = current->kartu.head;
    do {
        printf("| Nomor: %2d |\t", temp->nomorKartu);
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");

    temp = current->kartu.head;
    do {
        printf("| Tipe: %3c |\t", temp->tipeKartu);
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");

    temp = current->kartu.head;
    do {
        printf("| Nilai: %2d |\t", temp->nilaiKartu);
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");

    temp = current->kartu.head;
    do {
        printf("-------------\t");
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");
}

int cek_aturan(nodeMeja *dek, int *highest)
{
    if (is_it_high_card(dek->llDeck, highest))
    {
        return highCard;
    }
    else if (is_it_pair(dek->llDeck, highest))
    {
        return pair;
    }
    else if (is_it_three_of_a_kind(dek->llDeck, highest))
    {
        return threeOfaKind;
    }
    else if (is_it_straight(dek->llDeck, highest))
    {
        return straight;
    }
    else if (is_it_flush(dek->llDeck, highest))
    {
        return flush;
    }
    else if (is_it_full_house(dek->llDeck, highest))
    {
        return fullHouse;
    }
    else if (is_it_four_of_a_kind(dek->llDeck, highest))
    {
        return fourOfaKind;
    }
    else if (is_it_straight_flush(dek->llDeck, highest))
    {
        return straightFlush;
    }
    else if (is_it_royal_flush(dek->llDeck, highest))
    {
        return royalFlush;
    }
    else
    {
        return 0;
    }
}

bool is_it_high_card(pointKartu *deck, int *highest)
{
    if (deck->head == deck->tail)
    {
        *highest = deck->head->nilaiKartu;
        return true;
    }
    return false;
}

bool is_it_pair(pointKartu *deck, int *highest)
{
    if (deck->head->next == deck->tail && deck->head->nilaiKartu == deck->tail->nilaiKartu)
    {
        *highest = deck->head->nilaiKartu;
        return true;
    }
    return false;
}

bool is_it_three_of_a_kind(pointKartu *deck, int *highest)
{
    int nilai = deck->head->nilaiKartu;
    nodeKartu *temp = deck->head;
    while (temp != deck->tail)
    {
        temp = temp->next;
        if (temp->nilaiKartu != nilai)
        {
            return false;
        }
    }
    *highest = deck->head->nilaiKartu;
    return true;
}

bool is_it_straight(pointKartu *deck, int *highest)
{
    nodeKartu *temp = deck->head;
    while (temp != deck->tail->next)
    {
        if (temp->nilaiKartu + 1 != temp->next->nilaiKartu)
        {
            return false;
        }
        temp = temp->next;
    }
    *highest = deck->tail->nilaiKartu;
    return true;
}

bool is_it_flush(pointKartu *deck, int *highest)
{
    nodeKartu *temp = deck->head;
    while (temp != deck->tail->next)
    {
        if (temp->tipeKartu != temp->next->tipeKartu)
        {
            return false;
        }
        temp = temp->next;
    }
    *highest = deck->tail->nilaiKartu;
    return true;
}

bool is_it_full_house(pointKartu *deck, int *highest)
{
    int frekuensi[16] = {0};

    nodeKartu *temp = deck->head;
    while (temp != deck->tail->next)
    {
        frekuensi[temp->nilaiKartu]++;
        temp = temp->next;
    }
    int hitungTiga = 0;
    int hitungDua = 0;

    for (int i = 3; i <= 15; i++)
    {
        if (frekuensi[i] == 3)
        {
            hitungTiga++;
            *highest = i;
        }
        else if (frekuensi[i] == 2)
        {
            hitungDua++;
        }
    }
    if (hitungTiga == 1 && hitungDua == 1)
    {
        return true;
    }
    return false;
}

bool is_it_four_of_a_kind(pointKartu *deck, int *highest)
{
    int nilai = deck->head->nilaiKartu;
    nodeKartu *temp = deck->head;
    while (temp != deck->tail->next)
    {
        if (temp->nilaiKartu != nilai)
        {
            return false;
        }
        temp = temp->next;
    }
    *highest = deck->tail->nilaiKartu;
    return true;
}

bool is_it_straight_flush(pointKartu *deck, int *highest)
{
    nodeKartu *head = deck->head;
    if (is_it_flush(deck, highest) && is_it_straight(deck, highest))
    {
        *highest = deck->tail->nilaiKartu;
        return true;
    }
    return false;
}

bool is_it_royal_flush(pointKartu *deck, int *highest)
{
    if (is_it_flush(deck, highest) && is_it_straight(deck, highest))
    {
        if (deck->tail->nilaiKartu == As || deck->tail->nilaiKartu == King)
        {
            *highest = deck->tail->nilaiKartu;
            return true;
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
        asli->llDeck = sementara->llDeck;
        cekBreak = 1;
        return cekBreak;
    }

    if (asli->nilaiTertinggi == Two && sementara->aturan == fourOfaKind && asli->aturan == highCard) // pengecekan bom
    {
        asli->aturan = sementara->aturan;
        asli->nilaiTertinggi = sementara->nilaiTertinggi;
        asli->llDeck = sementara->llDeck;
        cekBreak = 2;
        return cekBreak;
    }

    if (asli->nilaiTertinggi < sementara->nilaiTertinggi && asli->aturan == sementara->aturan)
    {

        asli->nilaiTertinggi = sementara->nilaiTertinggi;
        asli->llDeck = sementara->llDeck;
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

bool computer_turn(nodeMeja *dekMeja, nodeMeja *dekTemp, nodePemain *com)
{
    pointKartu *llComb = (pointKartu *)malloc(sizeof(pointKartu));
    reset_ll_comb(llComb, com);
    bool result = 1;

    if (dekMeja->aturan == 0)
    {
        if (five_cards_comb(llComb, dekMeja, dekTemp) ||
            three_cards_comb(llComb, dekMeja, dekTemp) ||
            two_cards_comb(llComb, dekMeja, dekTemp))
        {
            get_llComb(com, llComb, dekMeja);
            dekMeja->aturan = dekTemp->aturan;
            dekMeja->nilaiTertinggi = dekTemp->nilaiTertinggi;
        }
        else
        {
            llComb->head = com->kartu.head;
            llComb->tail = com->kartu.head;
            dekMeja->llDeck = llComb;
        }
    }
    else
    {
        switch (dekMeja->aturan)
        {
        case highCard:
            result = high_card_fight(llComb, dekMeja, dekTemp);
            break;
        case pair:
            result = two_cards_comb(llComb, dekMeja, dekTemp);
            break;
        case threeOfaKind:
            result = three_cards_comb(llComb, dekMeja, dekTemp);
            break;
        default:
            result = five_cards_comb(llComb, dekMeja, dekTemp);
            break;
        }

        if (result)
        {
            get_llComb(com, llComb, dekMeja);
            dekMeja->aturan = dekTemp->aturan;
            dekMeja->nilaiTertinggi = dekTemp->nilaiTertinggi;
        }
        else
        {
            dekTemp->llDeck->head = NULL;
            dekTemp->llDeck->tail = NULL;
        }
    }

    free(llComb);
    return result;
}

void set_tail(pointKartu *llComb, int card)
{
    int jumlah = 0;
    nodeKartu *temp = llComb->head;
    while (jumlah < card && temp != NULL)
    {
        temp = temp->next;
        jumlah++;
    }
    llComb->tail = temp;
}

void reset_ll_comb(pointKartu *llComb, nodePemain *com)
{
    llComb->head = com->kartu.head;
    llComb->tail = NULL;
}

bool five_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    nodeKartu *temp = llComb->head;
    bool result = false;

    if (dekMeja->aturan <= 8 && dekMeja->aturan >= 4)
    {
        set_tail(llComb, 5);
        while (llComb->tail != NULL)
        {
            if (is_it_straight_flush(llComb, &(dekMeja->nilaiTertinggi)) && dekMeja->aturan <= straightFlush)
            {
                if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
                {
                    if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                    {
                        dekTemp->aturan = 8;
                        result = true;
                        break;
                    }
                }
                else if (dekTemp->nilaiTertinggi > dekMeja->nilaiTertinggi)
                {
                    dekTemp->aturan = 8;
                    result = true;
                    break;
                }
            }
            else if (is_it_royal_flush(llComb, &(dekMeja->nilaiTertinggi)) && dekMeja->aturan <= royalFlush)
            {
                if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                {
                    dekTemp->aturan = 9;
                    result = true;
                    break;
                }
            }
            llComb->head = llComb->head->next;
            llComb->tail = llComb->tail->next;
        }
    }

    if (!result)
    {
        llComb->head = temp;
        set_tail(llComb, 5);
        while (llComb->tail != NULL)
        {
            if (dekMeja->aturan <= straight)
            {
                if (is_it_straight(llComb, &(dekTemp->nilaiTertinggi)))
                {
                    if (dekMeja->aturan == 0)
                    {
                        dekTemp->aturan = 4;
                        result = true;
                        break;
                    }
                    else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
                    {
                        if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                        {
                            dekTemp->aturan = 4;
                            result = true;
                            break;
                        }
                    }
                    else if (dekTemp->nilaiTertinggi > dekMeja->nilaiTertinggi)
                    {
                        dekTemp->aturan = 4;
                        result = true;
                        break;
                    }
                }
            }
            if (dekMeja->aturan <= flush)
            {
                if (is_it_flush(llComb, &(dekTemp->nilaiTertinggi)))
                {
                    if (dekMeja->aturan == 0)
                    {
                        dekTemp->aturan = 5;
                        result = true;
                        break;
                    }
                    else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
                    {
                        if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                        {
                            dekTemp->aturan = 5;
                            result = true;
                            break;
                        }
                    }
                    else if (dekTemp->nilaiTertinggi > dekMeja->nilaiTertinggi)
                    {
                        dekTemp->aturan = 5;
                        result = true;
                        break;
                    }
                }
            }
            if (dekMeja->aturan <= fullHouse)
            {
                if (is_it_full_house(llComb, &(dekTemp->nilaiTertinggi)))
                {
                    if (dekMeja->aturan == 0)
                    {
                        dekTemp->aturan = 6;
                        result = true;
                        break;
                    }
                    else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
                    {
                        if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                        {
                            dekTemp->aturan = 6;
                            result = true;
                            break;
                        }
                    }
                    else if (dekTemp->nilaiTertinggi > dekMeja->nilaiTertinggi)
                    {
                        dekTemp->aturan = 6;
                        result = true;
                        break;
                    }
                }
            }
            llComb->head = llComb->head->next;
            llComb->tail = llComb->tail->next;
        }
    }
    return result;
}

bool four_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    set_tail(llComb, 4);
    while (llComb->tail != NULL)
    {
        if (is_it_four_of_a_kind(llComb, &(dekTemp->nilaiTertinggi)))
        {
            dekTemp->aturan = 7;
            return true;
        }
        llComb->head = llComb->head->next;
        llComb->tail = llComb->tail->next;
    }
    return false;
}

bool three_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    set_tail(llComb, 3);
    while (llComb->tail != NULL)
    {
        if (is_it_three_of_a_kind(llComb, &(dekTemp->nilaiTertinggi)))
        {
            if (dekMeja->aturan == 0)
            {
                dekTemp->aturan = 3;
                return true;
            }
            else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
            {
                if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                {
                    dekTemp->aturan = 3;
                    return true;
                }
            }
        }
        llComb->head = llComb->head->next;
        llComb->tail = llComb->tail->next;
    }
    return false;
}

bool two_cards_comb(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    set_tail(llComb, 2);
    while (llComb->tail != NULL)
    {
        if (is_it_pair(llComb, &(dekTemp->nilaiTertinggi)))
        {
            if (dekMeja->aturan == 0)
            {
                dekTemp->aturan = 2;
                return true;
            }
            else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
            {
                if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                {
                    dekTemp->aturan = 2;
                    return true;
                }
            }
        }
        llComb->head = llComb->head->next;
        llComb->tail = llComb->tail->next;
    }
    return false;
}

bool high_card_fight(pointKartu *llComb, nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    set_tail(llComb, 1);
    while (llComb->tail != NULL)
    {
        if (is_it_high_card(llComb, &(dekTemp->nilaiTertinggi)))
        {
            if (dekMeja->aturan == 0)
            {
                dekTemp->aturan = 1;
                return true;
            }
            else if (dekTemp->nilaiTertinggi == dekMeja->nilaiTertinggi)
            {
                if (dekTemp->llDeck->tail->tipeKartu > dekMeja->llDeck->tail->tipeKartu)
                {
                    dekTemp->aturan = 1;
                    return true;
                }
            }
        }
        llComb->head = llComb->head->next;
        llComb->tail = llComb->tail->next;
    }
    return false;
}

void get_llComb(nodePemain *com, pointKartu *llComb, nodeMeja *dekMeja)
{
    nodeKartu *temp = com->kartu.head;
    while (temp->next != llComb->head)
    {
        temp = temp->next;
    }
    temp->next = llComb->tail->next;
    dekMeja->llDeck->head = llComb->head;
    dekMeja->llDeck->tail = llComb->tail;
}
