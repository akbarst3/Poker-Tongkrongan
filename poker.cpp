/*
file               : poker.cpp
author             : Muhammad Dzaki Nurhidayat (231511083)
                     Muhammad Fachry Khairiansyah (231511084)
                     Restu Akbar (231511088)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Games Poker Tongkrongan.
*/

#include "poker.h"

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
    nodeKartu *temp = head->next;
    if (head->next != NULL && temp->next == NULL)
    {
        if (head->nilaikartu == temp->nilaikartu)
        {
            return true;
        }
    }
    return false;
}

bool is_it_two_pair(nodeKartu *head)
{
    nodeKartu *temp = head;
    int card = 0;
    while (temp->next != NULL)
    {
        card++;
        temp = temp->next;
    }
    temp = head;
    if (card == 4)
    {
        int pair = 0;
        while (temp->next != NULL)
        {
            if (temp->nilaikartu == temp->next->nilaikartu)
            {
                pair++;
                if (pair == 2)
                {
                    return true;
                }
            }
            temp = temp->next->next;
        }
    }
    else
    {
        return false;
    }
}

bool is_it_three_of_a_kind(nodeKartu *head);
bool is_it_straight(nodeKartu *head);
bool is_it_flush(nodeKartu *head);
bool is_it_full_house(nodeKartu *head);
bool is_it_four_of_a_kind(nodeKartu *head);
bool is_it_straight_flush(nodeKartu *head);
bool is_it_royal_flush(nodeKartu *head);
bool is_it_bomb(nodeKartu *headSementara, nodeKartu *headMeja);
