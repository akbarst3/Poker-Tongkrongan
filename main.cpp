/*
file               : main.cpp
author             : Muhammad Dzaki Nurhidayat (231511083)
                     Muhammad Fachry Khairiansyah (231511084)
                     Restu Akbar (231511088)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Games Poker Tongkrongan.
*/

#include "poker.h"

int main()
{
    int cekBreak, choice = 0, round = 0;
    title();
    system("pause");
    do
    {
        puts("\n\n\n");
        system("cls");
        printf("\n\n\n\t\t\tSELAMAT DATANG DI POKER TONGKRONGAN \n");
        printf("MENU :\n\n");
        printf("1. Start\n\n2. Help Menu\n\n3. History\n\n4. Exit\n\n\nPilih Menu: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char playerName[10];
            int pos = 5;
            pointKartu dekLL = {NULL, NULL};
            nodePemain *aktif = NULL;
            nodePemain *com = NULL;
            pointKartu *dekAktif = NULL;
            nodePemain *player = NULL;
            nodeMeja *dekMeja = NULL;
            nodeMeja *dekTemp = NULL;
            pointKartu llOut = {NULL, NULL};
            /* start */
            system("cls");
            do
            {
                printf("\t\t\tMasukkan Nama Pemain (MAX 9 Huruf): "); // nama player
                scanf("%s", &playerName);
                if (!max_name(playerName))
                {
                    puts("\t\t\tMASUKKAN JUMLAH HURUF SESUAI INSTRUKSI"); // nama player
                }

            } while (!max_name(playerName));
            system("cls");
            fill_the_card(&dekLL);
            shuffle_deck(&dekLL);
            create_player(&aktif, playerName);
            player = aktif;
            com = aktif->next;
            fill_deck(&aktif, &dekLL);
            aktif = first_play(aktif);
            alloc_deck(&dekMeja);
            alloc_deck(&dekTemp);
            nodePemain *winner = aktif;
            printf("PERTAMA MAIN : %s\n\n", aktif->nama);
            bool fight = false;
            do
            {
                print_game_computers(com, playerName);
                puts("\n\nDEK MEJA :");
                if (dekMeja->llDeck != NULL)
                {
                    print_game_card(dekMeja->llDeck);
                    print_rule_table(dekMeja);
                    printf("%s\n", winner->nama);
                    puts("\n");
                }
                else
                {
                    puts("KOSONG\n\n");
                }
                printf("Kartu %s:\n", player->nama);
                print_game_card(&(player)->kartu);
                if (aktif != player)
                {
                    if (aktif->kartu.head != NULL && aktif->kartu.head)
                    {
                        printf("\n%s sedang berpikir...\n", aktif->nama);
                        system("pause\n");
                        fight = computer_turn(dekMeja, dekTemp, aktif);
                        if (fight)
                        {
                            winner = aktif;
                        }
                        else
                        {
                            printf("\n%s skip\n", aktif->nama);
                        }
                    }
                    else
                    {
                        nodePemain *prev = aktif;
                        if (aktif = com)
                        {
                            com = com->next;
                        }
                        while (prev->next != aktif)
                        {
                            prev = prev->next;
                        }
                        prev->next = aktif->next;
                        nodePemain *temp = aktif;
                        aktif = prev;

                        free(temp);
                    }
                }
                else
                {
                    fight = false;
                    do
                    {
                        free_memory_deck(dekTemp);
                        fight = player_turn(player, dekTemp);
                        if (fight)
                        {
                            cekBreak = compare_Meja(dekMeja, dekTemp);
                            if (cekBreak == 0)
                            {
                                return_card(dekTemp->llDeck, &(player)->kartu);
                                printf("KARTU YANG DIPILIH TIDAK BISA MELAWAN, PILIH KARTU LAIN? (y/n): ");
                                scanf(" %c", &choice);
                                if (choice == 'y')
                                {
                                    fight = false;
                                    continue;
                                }
                                else if (choice == 'n')
                                {
                                    break;
                                }
                            }
                            else
                            {
                                free_memory_deck(dekMeja);
                                dekMeja->llDeck = dekTemp->llDeck;
                                dekMeja->aturan = dekTemp->aturan;
                                dekMeja->nilaiTertinggi = dekTemp->nilaiTertinggi;
                                winner = player;
                                if (player->kartu.head == NULL && player->kartu.tail == NULL)
                                {
                                    nodePemain *countPos = player;
                                    do
                                    {
                                        pos--;
                                        countPos = countPos->next;
                                    } while (countPos != player);
                                    system("cls");
                                    print_win(pos);
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    } while (!fight);
                }
                aktif = aktif->next;
                if (aktif == winner)
                {
                    round++;
                    free_memory_deck(dekMeja);
                }
                if (dekMeja->aturan == 7)
                {
                    printf("BOM! PERMAINAN BERAKHIR, %s MENANG\n", winner->nama);
                    system("pause");
                    break;
                }
                system("cls");
            } while ((player->kartu.head && player->next != NULL));
            write_history("history.txt", round, pos, playerName);
            // free_memory_deck(dekMeja);
            // free_memory_deck(dekTemp);
            // free(aktif);
            // free(com);
            // free(dekAktif);
            // free(player);
            break;
        }

        case 2:
        {
            help_combination_card();
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            view_history();
            system("pause");
            system("cls");
            break;
        }
        default:
        {
            break;
        }
        }
    } while (choice != 4);
}