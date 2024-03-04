#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "TypingGame.h"
#include "GeneralFunc.c"

// TODO
// Start on the Manage Data feature

void ManageDataLogin();
void Play();
void MainMenu();
void ManageDataMenu();

struct recordsTag Data[100];

int main()
{
    MainMenu();
    return 0;
}

void MainMenu()
{
    system("cls");
    DisplayAsciiArt("StylisticTexts/title.txt");

    Str20 sOptions[3] = {"Manage Data", "Play", "Exit"};

    // switch cases for the option the user inputted

    switch (DisplayOptions(sOptions, 3))
    {
    case 0:
        ManageDataLogin();
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

void ManageDataLogin()
{
    Str10 password;
    int i = 0, nAttempts = 2, bGoToMenu = 0;
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
                printf("Press ESC to go back to Main Menu\n");
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

        if ((int)ch == 27)
        {
            bGoToMenu = 1; // if user pressed ESC then break out of the loop and make the boolean var true
            break;
        }
    }

    if (strcmp(password, PASSWORD) == 0) // display the manage data menu when logged in
    {
        system("cls");
        printf("\nLogged in Succesflly\n");
        DisplayAsciiArt("StylisticTexts/manageData.txt");
        ManageDataMenu();
    }

    if (bGoToMenu)
    {
        MainMenu();
    }
}

void ManageDataMenu()
{
    Str20 sOptions[6] = {"Add a Record",
                         "Edit a Record",
                         "Delete a Record",
                         "Import Data",
                         "Export Data",
                         "Go to Main Menu"};

    switch (DisplayOptions(sOptions, 6))
    {
    case 5:
        MainMenu();
        break;

    default:
        break;
    }
}

void Play()
{

    return;
}