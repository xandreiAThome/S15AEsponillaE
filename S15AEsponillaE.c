/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
                                                            Ellexandrei A. Esponilla, DLSU ID# 12334634
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "TypingGame.h"
#include "GeneralFunc.c"

// TODO

void ManageDataLogin(struct dataTag *gameData);
void Play(struct dataTag *gameData);
void MainMenu(struct dataTag *gameData);
void ManageDataMenu(struct dataTag *gameData);
void AddRecord(struct dataTag *gameData);
void EditRecord(struct dataTag *gameData);
void DeleteRecord(struct dataTag *gameData);
void ImportData(struct dataTag *gameData);
void ExportData(struct dataTag *gameData);

int main()
{
    struct dataTag gameData;
    gameData.currId = 0; // set current index of first empty index of phraseRecords array
    MainMenu(&gameData);

    return 0;
}

void MainMenu(struct dataTag *gameData)
{
    system("cls");
    DisplayAsciiArt("StylisticTexts/title.txt");

    Str20 sOptions[3] = {"Manage Data", "Play", "Exit"};

    // switch cases for the option the user inputted

    switch (DisplayOptions(sOptions, 3))
    {
    case 0:
        ManageDataLogin(gameData);
        break;
    case 1:
        Play(gameData);
        break;
    case 2:
        system("cls");
        printf("Exited the Game");
        break;
    }
}

void ManageDataLogin(struct dataTag *gameData)
{
    Str10 password;
    int i = 0, nAttempts = 2, bGoToMenu = 0, nContinue = 1;
    char ch;
    system("cls");
    DisplayAsciiArt("StylisticTexts/manageData.txt");
    printf("Enter password: ");
    while (nContinue)
    {

        ch = getch();
        if (ch == '\r')
        {
            if (nAttempts == 0) // if user tried to enter password 3 times
            {
                printf("\nTried to enter too many times, try again later\nReturning to Main Menu...");
                nContinue = 0;
            }

            password[i] = '\0';
            if (strcmp(PASSWORD, password) == 0) // if pasword is correct then make the loop stop
            {
                nContinue = 0;
            }
            else if (nContinue) // only continue to run this if statement if nContinue is still true
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
            nContinue = 0;
        }
    }

    if (nAttempts == 0) // if user tried to enter password too many times
    {
        Sleep(3000);
        MainMenu(gameData);
    }

    if (strcmp(password, PASSWORD) == 0) // display the manage data menu when logged in
    {
        system("cls");
        printf("\nLogged in Succesflly\n");
        ManageDataMenu(gameData);
    }

    if (bGoToMenu)
    {
        MainMenu(gameData);
    }
}

void ManageDataMenu(struct dataTag *gameData)
{
    system("cls");
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
        AddRecord(gameData);
        break;
    case 1:
        EditRecord(gameData);
        break;
    case 2:
        DeleteRecord(gameData);
        break;
    case 3:
        ImportData(gameData);
        break;
    case 4:
        ExportData(gameData);
        break;
    case 5:
        MainMenu(gameData);
        break;

    default:
        break;
    }
}

void AddRecord(struct dataTag *gameData)
{
    Str100 sNewPhrase;
    int i, nDup = 0, nPhraseLen;
    system("cls");
    DisplayAsciiArt("StylisticTexts/manageData.txt");

    printf("Add a new phrase: ");
    fflush(stdin);
    scanf("%100[^\n]%*c", sNewPhrase); // ask for input

    for (i = 0; i < 100 && !nDup; i++) // checks in the array of the data if the phrase already exists
    {
        if (strcmp(sNewPhrase, gameData->phraseRecords[i].sPhrase) == 0)
        {
            nDup = 1; // change to true if it phrase is found
        }
    }
    nPhraseLen = strlen(sNewPhrase);
    i--; // decrement i so that the current index of the matching phrase is correct

    if (nDup) // if it exists then show the entry
    {
        printf("Phrase already exists\n\n");
        printf("Id: %d\nLevel: %s\nCharacter count: %d\nPhrase: %s\n\n", gameData->phraseRecords[i].nId,
               gameData->phraseRecords[i].sLevel, gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
        printf("Returning to Menu....");
        Sleep(3000); // after 3 seconds return to main menu
        system("cls");
        ManageDataMenu(gameData);
    }
    else // if not, then add the new phrase to the array of struct
    {
        gameData->phraseRecords[gameData->currId].nId = gameData->currId;
        gameData->phraseRecords[gameData->currId].nNumOfChars = nPhraseLen;
        strcpy(gameData->phraseRecords[gameData->currId].sPhrase, sNewPhrase);
        if (nPhraseLen <= 33)
        {
            strcpy(gameData->phraseRecords[gameData->currId].sLevel, "easy"); // if num of char is less than or equal to 33 then level is easy
        }
        else if (nPhraseLen < 66)
        {
            strcpy(gameData->phraseRecords[gameData->currId].sLevel, "medium"); // if num of char is less than 66 then level is medium
        }
        else
        {
            strcpy(gameData->phraseRecords[gameData->currId].sLevel, "hard"); // greater than or equal to 66 is hard
        }
        gameData->currId++; // increment the curr ID to point to the next empty index in the phraseRecords array
        system("cls");
        printf("Succesfully added\n");
        ManageDataMenu(gameData);
    }
}

void EditRecord(struct dataTag *gameData)
{
    int nChose;

    system("cls");
    DisplayAsciiArt("StylisticTexts/editRecord.txt");
    DisplayTable(gameData);
    printf("\nEnter -1 to go back to Menu\nEnter the ID of the Phrase to edit: ");
    scanf("%d", &nChose);
    if (nChose == -1)
        ManageDataMenu(gameData);
}

void DeleteRecord(struct dataTag *gameData)
{
}
void ImportData(struct dataTag *gameData)
{
}
void ExportData(struct dataTag *gameData)
{
    char fileName[31];
    int i;
    FILE *outPtr;

    system("cls");
    DisplayAsciiArt("StylisticTexts/exportData.txt");
    printf("Enter Filename: ");

    scanf("%30s", fileName);
    while (strcmp(&fileName[strlen(fileName) - 4], ".txt") != 0)
    {
        printf("Invalid filename try again: "); // continue prompting if the file extension is not .txt
        scanf("%30s", fileName);
    }
    outPtr = fopen(fileName, "w");

    for (i = 0; i < gameData->currId; i++) // iterate over each of the phrase in the records and print it to the file
    {
        fprintf(outPtr, "%d\n%s\n%d\n%s\n\n", gameData->phraseRecords[i].nId, gameData->phraseRecords[i].sLevel,
                gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
        fflush(outPtr);
    }
    printf("Succesfully Exported\nReturning to Menu....");
    Sleep(2500);
    ManageDataMenu(gameData);
}

void Play(struct dataTag *gameData)
{

    return;
}