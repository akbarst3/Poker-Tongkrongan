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