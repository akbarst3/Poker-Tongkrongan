/*
file               : poker.cpp
author             : Muhammad Dzaki Nurhidayat (231511083)
                     Muhammad Fachry Khairiansyah (231511084)
                     Restu Akbar (231511088)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Games Poker Tongkrongan.
*/

#include "poker.h"

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
int cek_aturan(nodeMeja *dekMeja, nodeMeja *dekTemp)
{
    if (is_it_high_card(dekMeja->kartu))
    {
        return highCard;
    }
    else if (is_it_one_pair(dekMeja->kartu))
    {
        return onePair;
    }
    else if (is_it_two_pair(dekMeja->kartu))
    {
        return twoPair;
    }
    else if (is_it_three_of_a_kind(dekMeja->kartu))
    {
        return threeOfaKind;
    }
    else if (is_it_straight(dekMeja->kartu))
    {
        return straight;
    }
    else if (is_it_flush(dekMeja->kartu))
    {
        return flush;
    }
    else if (is_it_full_house(dekMeja->kartu))
    {
        return fullHouse;
    }
    else if (is_it_four_of_a_kind(dekMeja->kartu))
    {
        return fourOfaKind;
    }
    else if (is_it_straight_flush(dekMeja->kartu))
    {
        return straightFlush;
    }
    else if (is_it_royal_flush(dekMeja->kartu))
    {
        return royalFlush;
    }
    else if (is_it_bomb(dekTemp->kartu, dekMeja->kartu))
    {
        return bomb;
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
        if (head->nilaikartu == head->next->nilaikartu)
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
            if (temp->nilaikartu == temp->next->nilaikartu)
            {
                if (temp->nilaikartu != lastVal)
                {
                    pair++;
                    lastVal = temp->nilaikartu;
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
    else
    {
        return false;
    }
}

bool is_it_three_of_a_kind(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 3)
    {
        nodeKartu *temp = head;
        if (temp->nilaikartu == temp->next->nilaikartu == temp->next->next->nilaikartu)
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool is_it_straight(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 5)
    {
        nodeKartu *temp = head;
        while (temp->next != NULL)
        {
            if (temp->nilaikartu + 1 != temp->next->nilaikartu)
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
            if (temp->TipeKartu != temp->next->TipeKartu)
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
            if (temp->nilaikartu < 2 || temp->nilaikartu > 15)
            {
                return false;
            }
            frekuensi[temp->nilaikartu]++;
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
    else
    {
        return false;
    }
}

bool is_it_four_of_a_kind(nodeKartu *head)
{
    int card = count_card(head);
    if (card == 4)
    {
        int nilai = head->nilaikartu;
        nodeKartu *temp = head;
        while (temp != NULL)
        {
            if (temp->nilaikartu != nilai)
            {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
    else
    {
        return false;
    }
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
        nodeKartu* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        if (temp->nilaikartu == Two)
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool is_it_bomb(nodeKartu *headTemp, nodeKartu *headMeja)
{
    
}