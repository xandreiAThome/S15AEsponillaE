#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "TypingGame.h"
#include "GeneralFunc.c"

// TODO
// Start on the Manage Data feature

void ManageDataLogin();
void Play();
void MainMenu();
void ManageDataMenu();
void AddRecord();

struct recordsTag Data[100];
int ID = 0;

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
    DisplayAsciiArt("StylisticTexts/manageData.txt");
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
        ManageDataMenu();
    }

    if (bGoToMenu)
    {
        MainMenu();
    }
}

void ManageDataMenu()
{
    DisplayAsciiArt("StylisticTexts/manageData.txt");
    Str20 sOptions[6] = {"Add a Record",
                         "Edit a Record",
                         "Delete a Record",
                         "Import Data",
                         "Export Data",
                         "Go to Main Menu"};

    switch (DisplayOptions(sOptions, 6))
    {
    case 0:
        AddRecord();
        break;
    case 5:
        MainMenu();
        break;

    default:
        break;
    }
}

void AddRecord()
{
    Str100 sNewPhrase;
    int i, nDup = 0, nPhraseLen;
    system("cls");
    DisplayAsciiArt("StylisticTexts/manageData.txt");

    printf("Add a new phrase: ");
    fflush(stdin);
    scanf("%100[^\n]%*c", sNewPhrase); // ask for input

    for (i = 0; i < 100; i++) // checks in the array of the data if the phrase already exists
    {
        if (strcmp(sNewPhrase, Data[i].sPhrase) == 0)
        {
            nDup = 1;
            break;
        }
    }
    nPhraseLen = strlen(sNewPhrase);

    if (nDup) // if it exists then show the entry
    {
        printf("Phrase already exists\n\n");
        printf("Id: %d\nLevel: %s\nCharacter count: %d\nPhrase: %s\n\n", Data[i].nId, Data[i].sLevel, Data[i].nNumOfChars, Data[i].sPhrase);
        printf("Returning to Menu....");
        Sleep(3000); // after 3 seconds return to main menu
        system("cls");
        ManageDataMenu();
    }
    else // if not, then add the new phrase to the array of struct
    {
        Data[ID].nId = ID;
        Data[ID].nNumOfChars = nPhraseLen;
        strcpy(Data[ID].sPhrase, sNewPhrase);
        if (nPhraseLen <= 33)
        {
            strcpy(Data[ID].sLevel, "easy");
        }
        else if (nPhraseLen < 66)
        {
            strcpy(Data[ID].sLevel, "medium");
        }
        else
        {
            strcpy(Data[ID].sLevel, "hard");
        }
        ID++;
        system("cls");
        printf("Succesfully added\n");
        ManageDataMenu();
    }
}

void Play()
{

    return;
}