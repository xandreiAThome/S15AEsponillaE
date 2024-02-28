#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "TypingGame.h"

// TODO
// Start on the Manage Data feature

void ManageData();
void Play();
void Menu();

int main()
{
    Menu();
    return 0;
}

void Menu()
{
    // Display the options in the main menu
    int i, nSelected = -1;
    Str10 sOptions[3] = {"Manage Data", "Play", "Exit"};
    for (i = 0; i < 3; i++)
    {
        printf("%d - %s\n", i, sOptions[i]);
    }

    printf("Choose Option: ");
    scanf("%d", &nSelected);
    // prompts the user again if the input is invalid
    if (nSelected != 0 && nSelected != 1 && nSelected != 2)
        while (1)
        {
            if (nSelected == 0 || nSelected == 1 || nSelected == 2)
            {
                break;
            }
            printf("Invalid Option Choose Again: ");
            scanf("%d", &nSelected);
            fflush(stdin);
        }

    // switch cases for the option the user inputted
    switch (nSelected)
    {
    case 0:
        ManageData();
        break;
    case 1:
        Play();
        break;
    case 2:
        system("cls");
        printf("Exited the Game");
        break;
    }
}

void ManageData()
{
    Str10 password;
    int i = 0, nAttempts = 2;
    char ch;
    system("cls");

    printf("Enter password: ");
    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            if (nAttempts == 0) // if user tried to enter password 3 times
            {
                printf("\nTried to enter too many times, try again later");
                return;
            }

            password[i] = '\0';
            if (strcmp(PASSWORD, password) == 0) // if pasword is correct break out of loop
            {
                break;
            }
            else
            {
                nAttempts--; // else try again
                printf("\nIncorrect Password, %d tries remaining\n", nAttempts + 1);
                printf("Enter password: ");
                i = 0;
            }
        }
        else if (ch == '\b')
        { // Backspace key pressed
            if (i > 0)
            {
                printf("\b \b"); // erase the prev asterisk and go back one space
                i--;
            }
        }
        else
        {
            printf("*"); // Display asterisk
            password[i++] = ch;
        }
    }

    if (strcmp(password, PASSWORD) == 0)
    {
        system("cls");
        printf("\nLogged in Succesflly\n");
    }
}
void Play()
{

    return;
}
