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

#include "TypingGame.h"
#include "GeneralFunc.c"

// TODO
// TEST DELETE RECORDS FOR BUGS
// COMPLETE VIEWSCORES FUNC
// COMPLETE PLAY LOOP
// Check if there are multiple preexisting phrases in the game data and you import same phrases if the id is still consistent

void ManageDataLogin(struct dataTag *gameData);
void PlayMenu(struct dataTag *gameData);
void MainMenu(struct dataTag *gameData);
void ManageDataMenu(struct dataTag *gameData);
void AddRecord(struct dataTag *gameData);
void EditRecord(struct dataTag *gameData);
void DeleteRecord(struct dataTag *gameData);
void ImportData(struct dataTag *gameData);
void ExportData(struct dataTag *gameData);
void Play(struct dataTag *gameData);
void ViewScores(struct dataTag *gameData);

int main()
{
    struct dataTag gameData;
    InitializeEmptyRecord(&gameData);
    gameData.currId = 0;     // set current index of first empty index of phraseRecords array
    gameData.numPlayers = 0; // set the number of players that played the game to initially zero;
    ImportScores(&gameData);
    system("cls");
    MainMenu(&gameData);

    return 0;
}

void MainMenu(struct dataTag *gameData)
{
    DisplayAsciiArt("StylisticTexts/mainMenu.txt");

    Str20 sOptions[3] = {"Manage Data", "Play Menu", "Exit"};

    // switch cases for the option the user inputted

    switch (DisplayOptions(sOptions, 3))
    {
    case 0:
        system("cls");
        ManageDataLogin(gameData);
        break;
    case 1:
        system("cls");
        PlayMenu(gameData);
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
    DisplayAsciiArt("StylisticTexts/manageData.txt");
    printf("Enter password: ");
    while (nContinue)
    {

        ch = getch();
        if (ch == '\r')
        {
            if (nAttempts == 0) // if user tried to enter password 3 times
            {
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
        system("cls");
        printf("Tried to enter too many times\n");
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
        system("cls");
        MainMenu(gameData);
    }
}

void ManageDataMenu(struct dataTag *gameData)
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
        system("cls");
        AddRecord(gameData);
        break;
    case 1:
        system("cls");
        EditRecord(gameData);
        break;
    case 2:
        system("cls");
        DeleteRecord(gameData);
        break;
    case 3:
        system("cls");
        ImportData(gameData);
        break;
    case 4:
        system("cls");
        ExportData(gameData);
        break;
    case 5:
        system("cls");
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
    DisplayAsciiArt("StylisticTexts/addRecord.txt");

    printf("Enter r to go back to Menu\nAdd a new phrase: ");
    fflush(stdin);
    scanf("%100[^\n]%*c", sNewPhrase); // ask for input
    if (strcmp(sNewPhrase, "r") == 0)
    {
        ManageDataMenu(gameData);
        return;
    }

    for (i = 0; i < 100 && !nDup; i++) // checks in the array of the data if the phrase already exists
    {
        if (strcmp(sNewPhrase, gameData->phraseRecords[i].sPhrase) == 0)
        {
            nDup = 1; // change to true if it phrase is found
        }
    }
    nPhraseLen = strlen(sNewPhrase);
    i--; // decrement i so that the current index of the matching phrase is correct

    while (nDup) // if phrase already exists then show the entry and reprompt
    {
        printf("Phrase already exists\n");
        DisplayTable(gameData, i);
        printf("\nAdd a new phrase: ");
        fflush(stdin);
        scanf("%100[^\n]%*c", sNewPhrase); // ask for input
        nDup = 0;                          // assume that the new input will not be a duplicate

        for (i = 0; i < 100 && !nDup; i++) // checks in the array of the data if the phrase already exists
        {
            if (strcmp(sNewPhrase, gameData->phraseRecords[i].sPhrase) == 0)
                nDup = 1; // change to true if phrase is found
        }
        nPhraseLen = strlen(sNewPhrase);
        i--; // decrement i so that the current index of the matching phrase is correct
    }

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

    printf("Succesfully added phrase\n");
    ManageDataMenu(gameData);
}

void EditRecord(struct dataTag *gameData)
{
    int nChose = -1;
    int i, nDup = 0, nPhraseLen;
    char goToMenu;
    Str100 sNewPhrase;

    DisplayAsciiArt("StylisticTexts/editRecord.txt");
    DisplayTable(gameData, -1);
    printf("\nEnter r to go back to Menu\nEnter the ID of the Phrase to edit: ");
    if (scanf("%d", &nChose) == 0)          // if scanf did not scan any integer input
        scanf("%c", &goToMenu);             // then scan it to a char var
    if (goToMenu == 'r' || goToMenu == 'R') // if the char is r then return to menu
    {
        system("cls");
        ManageDataMenu(gameData);
        return;
    }

    while (nChose < 0 || nChose >= gameData->currId) // if invalid ID then reprompt again
    {
        printf("Invalid ID, Choose Again: "); // if scanf did not scan any integer input
        if (scanf("%d", &nChose) == 0)        // then scan it to a char var
            scanf("%c", &goToMenu);
        if (goToMenu == 'r' || goToMenu == 'R') // if the char is r then return to menu
        {
            system("cls");
            ManageDataMenu(gameData);
            return;
        }
    }

    printf("\nPhrase: %s\n", gameData->phraseRecords[nChose].sPhrase);
    printf("Edit Phrase: ");
    fflush(stdin);
    scanf("%100[^\n]%*c", sNewPhrase); // ask for phrase input

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
        system("cls");
        printf("Phrase already exists\n\n");
        printf("Id: %d\nLevel: %s\nCharacter count: %d\nPhrase: %s\n\n", gameData->phraseRecords[i].nId,
               gameData->phraseRecords[i].sLevel, gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
        EditRecord(gameData); // reprompt by calling editrecord again
        return;
    }
    else // if not, then add the edited phrase to the array of struct
    {
        gameData->phraseRecords[nChose].nNumOfChars = nPhraseLen;
        strcpy(gameData->phraseRecords[nChose].sPhrase, sNewPhrase);
        if (nPhraseLen <= 33)
        {
            strcpy(gameData->phraseRecords[nChose].sLevel, "easy"); // if num of char is less than or equal to 33 then level is easy
        }
        else if (nPhraseLen < 66)
        {
            strcpy(gameData->phraseRecords[nChose].sLevel, "medium"); // if num of char is less than 66 then level is medium
        }
        else
        {
            strcpy(gameData->phraseRecords[nChose].sLevel, "hard"); // greater than or equal to 66 is hard
        }
        system("cls");
        printf("Succesfully Edited Phrase\n");
        EditRecord(gameData); // call edit record again for the user if they want to edit other phrases
        return;
    }
}

void DeleteRecord(struct dataTag *gameData)
{
    int nChose = -1, i;
    struct recordsTag tempRecords[MAX_RECORDS];
    char goToMenu;
    DisplayAsciiArt("StylisticTexts/deleteRecord.txt");
    DisplayTable(gameData, -1);

    printf("\nEnter r to go back to Menu\nEnter the ID of the Phrase to Delete: ");
    if (scanf("%d", &nChose) == 0)          // if scanf did not scan any integer input
        scanf("%c", &goToMenu);             // then scan it to a char var
    if (goToMenu == 'r' || goToMenu == 'R') // if the char is r then return to menu
    {
        system("cls");
        ManageDataMenu(gameData);
        return;
    }

    while (nChose < 0 || nChose >= gameData->currId) // if invalid ID then reprompt again
    {
        printf("Invalid ID, Choose Again: "); // if scanf did not scan any integer input
        if (scanf("%d", &nChose) == 0)        // then scan it to a char var
            scanf("%c", &goToMenu);
        if (goToMenu == 'r' || goToMenu == 'R') // if the char is r then return to menu
        {
            system("cls");
            ManageDataMenu(gameData);
            return;
        }
    }

    for (i = 0; i < gameData->currId; i++) // add all the phrase into a temp array except the chosen phrase to be deleted
    {

        if (i > nChose)
        {
            tempRecords[i - 1] = gameData->phraseRecords[i]; // while decrementing all the other elements ahead of the chosen phrase in the array
            tempRecords[i - 1].nId--;
        }
        else if (i < nChose)
        {
            tempRecords[i] = gameData->phraseRecords[i]; // phrases before the to be deleted phrase will be just copied
        }
    }
    gameData->currId--; // decrement the current empty index

    InitializeEmptyRecord(gameData); // empty game data records to remove garbage value

    for (i = 0; i < gameData->currId; i++)
        gameData->phraseRecords[i] = tempRecords[i]; // transfer contents from tempRecords to game data

    system("cls");
    printf("Succesfully Deleted Phrase\n");
    DeleteRecord(gameData);
    return;
}

void ImportData(struct dataTag *gameData)
{
    Str30 fileName;
    FILE *inPtr;
    int initCurrId = gameData->currId, tempId, tempNumChars, dupPhrase = 0;
    Str10 tempLevel;
    Str100 tempPhrase;

    DisplayAsciiArt("StylisticTexts/importData.txt");
    printf("Enter r to go back to Menu\nEnter file name: "); // ask for file name
    scanf("%30s", fileName);
    if (strcmp(fileName, "r") == 0) // if r is entered then go back to menu
    {
        ManageDataMenu(gameData);
        return;
    }
    inPtr = fopen(fileName, "r"); // open file for reading

    while (inPtr == NULL)
    {
        printf("File does not exist\nEnter file name: "); // reprompt if file does not exist
        scanf("%30s", fileName);
        if (strcmp(fileName, "r") == 0) // if r is entered then go back to menu
        {
            ManageDataMenu(gameData);
            return;
        }
        inPtr = fopen(fileName, "r");
    }

    // scan the values in the file into the gameData while fscanf still reads values
    while (fscanf(inPtr, "%d", &tempId) > 0 &&
           fscanf(inPtr, "%s", tempLevel) > 0 &&
           fscanf(inPtr, "%d", &tempNumChars) > 0 &&
           fscanf(inPtr, "%*c%[^\n]", tempPhrase) > 0)
    {
        if (StringInArray(gameData, tempPhrase, 0) == -1) // if the phrase still doesnt exist in the game data
        {
            gameData->phraseRecords[gameData->currId].nId = initCurrId + tempId - dupPhrase;
            // add the initial currId to the id of the phrase so that the id still corresponds to their index in the array
            // subtract the number of dupPhrases so that the id of the phrases doesnt skip a number
            gameData->phraseRecords[gameData->currId].nNumOfChars = tempNumChars;
            strcpy(gameData->phraseRecords[gameData->currId].sLevel, tempLevel);
            strcpy(gameData->phraseRecords[gameData->currId].sPhrase, tempPhrase);

            gameData->currId++; // increment the currId to indicate the next empty index
        }
        else
        {
            dupPhrase++; // increment the dupPhrase if the phrase is a duplicate, so that the Id of the phrases are still in order
        }
    }

    system("cls");
    printf("File Imported Succesfully"); // go back to menu
    ManageDataMenu(gameData);
}

void ExportData(struct dataTag *gameData)
{
    Str30 fileName;
    int i;
    FILE *outPtr;

    system("cls");
    DisplayAsciiArt("StylisticTexts/exportData.txt");
    printf("Enter r to go back to Menu\nEnter Filename: ");

    scanf("%30s", fileName);
    if (strcmp(fileName, "r") == 0)
    {
        ManageDataMenu(gameData);
        return;
    }

    while (strcmp(&fileName[strlen(fileName) - 4], ".txt") != 0)
    {
        printf("Invalid filename try again: "); // continue prompting if the file extension is not .txt
        scanf("%30s", fileName);

        if (strcmp(fileName, "r") == 0) // go back to menu
        {
            ManageDataMenu(gameData);
            return;
        }
    }
    outPtr = fopen(fileName, "w");

    for (i = 0; i < gameData->currId; i++) // iterate over each of the phrase in the records and print it to the file
    {
        fprintf(outPtr, "%d\n%s\n%d\n%s\n\n", gameData->phraseRecords[i].nId, gameData->phraseRecords[i].sLevel,
                gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
        fflush(outPtr);
    }
    printf("Succesfully Exported\n");
    fclose(outPtr);
    ManageDataMenu(gameData);
}

void PlayMenu(struct dataTag *gameData)
{
    Str20 options[3] = {"Play Game", "View Scores", "Return to Main Menu"};
    DisplayAsciiArt("StylisticTexts/playMenu.txt");

    switch (DisplayOptions(options, 3))
    {
    case 0:
        system("cls");
        Play(gameData);
        break;
    case 1:
        system("cls");
        ViewScores(gameData);
        break;
    case 2:
        system("cls");
        MainMenu(gameData);
    }

    return;
}

void Play(struct dataTag *gameData)
{
    DisplayAsciiArt("StylisticTexts/title.txt");
}

void ViewScores(struct dataTag *gameData)
{
    int i, longestName = 0, nLen;
    DisplayAsciiArt("StylisticTexts/viewScores.txt");
    char *labelRow = "Total Score\tEasy\t\tMedium\t\tHard\t\tPlayer Name"; // row for the labels

    for (i = 0; i < gameData->numPlayers; i++)
    {
        if (strlen(gameData->scoresRecord->sPlayer) > longestName)
            longestName = strlen(gameData->scoresRecord->sPlayer); // get the longest player name in the game data
    }

    nLen = strlen(labelRow) * 2 + abs(strlen("Player Name") - longestName); // get the lenght of the label row

    for (i = 0; i < nLen; i++) // printf "=" equal to the length of the string for the label row and the phrase
        printf("=");
    printf("\n%s\n", labelRow); // print the label row and the border
    for (i = 0; i < nLen; i++)
        printf("=");
    printf("\n");

    for (i = 0; i < gameData->numPlayers; i++) // print the scores of each players in the game data
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%s\n",
               gameData->scoresRecord[i].easyScore + gameData->scoresRecord[i].mediumScore + gameData->scoresRecord[i].hardScore,
               gameData->scoresRecord[i].easyScore, gameData->scoresRecord[i].mediumScore,
               gameData->scoresRecord[i].hardScore, gameData->scoresRecord[i].sPlayer);
    }
}