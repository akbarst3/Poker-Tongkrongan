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
        assign_number((*aktif)->kartu.head);
        display_node((*aktif)->kartu.head);
        *aktif = (*aktif)->pemain;
        totalCard = 1;
        i++;
    }
}

nodePemain *first_play(nodePemain *aktif) {
    nodePemain *winner = NULL;
    nodeKartu *temp, *prev;
    int i, totalCard;

    i = 1;
    while (i <= 4) {
        temp = aktif->kartu.head;
        prev = NULL;
        totalCard = 0; 
        while (totalCard <= 13 && temp != NULL) {
            printf("Nilai = %d\n", temp->nilaiKartu); // Debugging line

            if (temp->nilaiKartu == 3) {
                printf("Singa\n"); // Debugging line
                // Menghapus node dari linked list
                if (temp == aktif->kartu.head) {
                    aktif->kartu.head = temp->next;
                    if (aktif->kartu.head == NULL) {
                        aktif->kartu.tail = NULL;
                    }
                } else if (temp == aktif->kartu.tail) {
                    prev->next = NULL;
                    aktif->kartu.tail = prev;
                } else {
                    if (prev != NULL) {
                        prev->next = temp->next;
                    }
                }

                // Menetapkan pemenang jika tipeKartu adalah 'D'
                if (temp->tipeKartu == 'D') {
                    winner = aktif;
                }

                // Deallocasi node
                nodeKartu* nodeToFree = temp;
                temp = temp->next;
                free(nodeToFree);
            }

            prev = temp;
            temp = temp->next;
            totalCard++;
        }
        // Pindah ke pemain berikutnya dalam linked list circular
        aktif = aktif->pemain;
        temp = aktif->kartu.head;
        i++;
    }
    return winner;
}

int main() {
    pointKartu dekLL = {NULL, NULL};
    nodePemain *aktif = NULL;

    fill_the_card(&dekLL);
    printf("Deck sebelum diacak:\n");
    display_node(dekLL.head);

    shuffle_deck(&dekLL);
    printf("Deck setelah diacak:\n");
    display_node(dekLL.head);

    create_player(&aktif, "Dzaki");
    // print_players(aktif);
    fill_deck(&aktif, &dekLL);
    printf("Makan\n");
    aktif = first_play(aktif);
    printf("Ini Main = %s \n", aktif->nama);
    print_players(aktif);
}