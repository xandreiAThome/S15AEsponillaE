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
#include <time.h>

#include "TypingGame.h"
#include "GeneralFunc.c"

// TODO
// MAKE TEST CASES AND REVIEW EACH FUNCTION

// Tentatively Ok for now
// TEST DELETE RECORDS FOR BUGS

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
void PlayLoop(struct dataTag *gameData, char *sLevel, int *life, int playerIndex, struct scoresTag *tempScore);
void ViewScores(struct dataTag *gameData);

int main()
{
    srand(time(NULL));
    struct dataTag gameData;
    gameData.currId = 0;     // init
    gameData.numPlayers = 0; // init
    ImportScores(&gameData, "scores.txt");
    system("cls");
    MainMenu(&gameData);
    ExportScores(&gameData, "scores.txt");
    return 0;
}

/*
    Display Function Only
*/
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

/*
    Display Function Only
*/
void ManageDataLogin(struct dataTag *gameData)
{
    Str10 password;
    int i = 0, nAttempts = 2, bGoToMenu = 0, nContinue = 1;
    char ch;
    DisplayAsciiArt("StylisticTexts/manageData.txt");
    printf("Press ESC to return to Menu\nEnter password: ");
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

/*
    Display Function Only
*/
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
    int index, nDup = 0, nPhraseLen;
    DisplayAsciiArt("StylisticTexts/addRecord.txt");

    if (gameData->currId >= MAX_RECORDS)
    {
        system("cls");
        printf("Records Array is Full\n");
        ManageDataMenu(gameData);
    }

    printf("Enter r to go back to Menu\nAdd a new phrase: ");
    fseek(stdin, 0, SEEK_END);
    scanf("%100[^\n]%*c", sNewPhrase);                                // ask for input
    if (strcmp(sNewPhrase, "r") == 0 || strcmp(sNewPhrase, "R") == 0) // if the user wants to go back to menu
    {
        system("cls");
        ManageDataMenu(gameData);
        return;
    }

    index = StringInArray(gameData, sNewPhrase, 0);
    if (index > -1) // checks if the phrase already exists
    {
        nDup = 1;
    }
    nPhraseLen = strlen(sNewPhrase);

    while (nDup) // if phrase already exists then show the entry and reprompt
    {
        printf("Phrase already exists\n");
        DisplayTable(gameData, index);
        printf("\nAdd a new phrase: ");
        fseek(stdin, 0, SEEK_END);
        scanf("%100[^\n]%*c", sNewPhrase); // ask for input
        nDup = 0;                          // assume that the new input will not be a duplicate

        if (strcmp(sNewPhrase, "r") == 0 || strcmp(sNewPhrase, "R") == 0) // if the user wants to go back to menu
        {
            system("cls");
            ManageDataMenu(gameData);
            return;
        }

        index = StringInArray(gameData, sNewPhrase, 0);
        if (index > -1) // checks if the phrase already exists
        {
            nDup = 1;
        }
        nPhraseLen = strlen(sNewPhrase);
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
    int index, nDup = 0, nPhraseLen;
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
    fseek(stdin, 0, SEEK_END);
    scanf("%100[^\n]%*c", sNewPhrase); // ask for phrase input

    index = StringInArray(gameData, sNewPhrase, 0); // checks if the phrase already exists
    if (index > -1)
    {
        nDup = 1; // there is a duplicate phrase
    }
    nPhraseLen = strlen(sNewPhrase);

    if (nDup) // if it exists then show the entry
    {
        system("cls");
        printf("Phrase already exists\n");
        DisplayTable(gameData, index);
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
            tempRecords[i - 1] = gameData->phraseRecords[i]; // place the phrases ahead the chosen phrase on the previous index
            tempRecords[i - 1].nId--;                        // decrementing the id of the elements ahead of the chosen phrase in the array
        }
        else if (i < nChose)
        {
            tempRecords[i] = gameData->phraseRecords[i]; // phrases before the to be deleted phrase will be just copied
        }
    }

    gameData->currId--; // decrement the current empty index

    for (i = 0; i < gameData->currId; i++)
        gameData->phraseRecords[i] = tempRecords[i]; // transfer contents from tempRecords to game data

    gameData->phraseRecords[gameData->currId].nId = 0;
    gameData->phraseRecords[gameData->currId].nNumOfChars = 0;
    strcpy(gameData->phraseRecords[gameData->currId].sLevel, "");
    strcpy(gameData->phraseRecords[gameData->currId].sPhrase, ""); // empty the currId because of a duplicate record while copying from the tempRecords

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
    if (strcmp(fileName, "r") == 0 || strcmp(fileName, "R") == 0) // if r is entered then go back to menu
    {
        system("cls");
        ManageDataMenu(gameData);
        return;
    }
    inPtr = fopen(fileName, "r"); // open file for reading

    while (inPtr == NULL)
    {
        printf("File does not exist\nEnter file name: "); // reprompt if file does not exist
        scanf("%30s", fileName);
        if (strcmp(fileName, "r") == 0 || strcmp(fileName, "R") == 0) // if r is entered then go back to menu
        {
            system("cls");
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
        if (gameData->currId >= MAX_RECORDS)
        {
            fclose(inPtr);
            system("cls");
            printf("File Partially Imported, Records array is full\n"); // go back to menu
            ManageDataMenu(gameData);
        }
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

    fclose(inPtr);
    system("cls");
    printf("File Imported Succesfully\n"); // go back to menu
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
    if (strcmp(fileName, "r") == 0 || strcmp(fileName, "R") == 0)
    {
        system("cls");
        ManageDataMenu(gameData);
        return;
    }

    while (strcmp(&fileName[strlen(fileName) - 4], ".txt") != 0)
    {
        printf("Invalid filename try again: "); // continue prompting if the file extension is not .txt
        scanf("%30s", fileName);

        if (strcmp(fileName, "r") == 0 || strcmp(fileName, "R") == 0) // go back to menu
        {
            system("cls");
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

    fclose(outPtr);
    system("cls");
    printf("Succesfully Exported\n");
    ManageDataMenu(gameData);
}

/*
    Display Function Only
*/
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
    int life = 3, i, indexPlayer = -1;
    int easyPhr = 0, medPhr = 0, hardPhr = 0;
    char opt;
    struct scoresTag tempScore;
    Str20 playerName;

    for (i = 0; i < gameData->currId; i++) // checks if there is enough phrases in the records
    {
        if (strcmp(gameData->phraseRecords[i].sLevel, "easy") == 0)
            easyPhr++;
        else if (strcmp(gameData->phraseRecords[i].sLevel, "medium") == 0)
            medPhr++;
        else
            hardPhr++;
    }

    if (easyPhr < 3) // goes back to menu if there isnt enough phrases
    {
        system("cls");
        printf("Insufficient Easy Phrases, Go to Manage Data Menu to add more Phrases\n");
        PlayMenu(gameData);
        return;
    }
    else if (medPhr < 2)
    {
        system("cls");
        printf("Insufficient Medium Phrases, Go to Manage Data Menu to add more Phrases\n");
        PlayMenu(gameData);
        return;
    }
    else if (hardPhr == 0)
    {
        system("cls");
        printf("Insufficient Hard Phrases, Go to Manage Data Menu to add more Phrases\n");
        PlayMenu(gameData);
        return;
    }

    DisplayAsciiArt("StylisticTexts/title.txt");
    printf("Enter name: "); // get player name
    fseek(stdin, 0, SEEK_END);
    scanf("%100[^\n]%*c", playerName);
    if (opt == 'r' || opt == 'R') // if the char is r then return to menu
    {
        system("cls");
        PlayMenu(gameData);
        return;
    }

    for (i = 0; i < gameData->numPlayers && indexPlayer == -1; i++) // checks if the player already has a record in the scores
    {
        if (strcmp(playerName, gameData->scoresRecord[i].sPlayer) == 0)
            indexPlayer = i; // get their index in the array
    }
    if (indexPlayer == -1 && gameData->numPlayers < MAX_RECORDS) // if not then add the name of the player to the scores list
    {
        strcpy(gameData->scoresRecord[gameData->numPlayers].sPlayer, playerName); // intialize the players score
        gameData->scoresRecord[gameData->numPlayers].easyScore = 0;
        gameData->scoresRecord[gameData->numPlayers].mediumScore = 0;
        gameData->scoresRecord[gameData->numPlayers].hardScore = 0;
        indexPlayer = gameData->numPlayers; // get the index in the array
        gameData->numPlayers++;             // increment the next available empty index in the scores list
    }
    else
    {
        printf("ERROR, Player List is full");
    }
    strcpy(tempScore.sPlayer, gameData->scoresRecord[indexPlayer].sPlayer); // init the player name to tempScore
    tempScore.easyScore = 0;                                                // init the score to zero
    tempScore.mediumScore = 0;
    tempScore.hardScore = 0;

    system("cls");
    DisplayAsciiArt("StylisticTexts/title.txt");

    PlayLoop(gameData, "easy", &life, indexPlayer, &tempScore); // play loop for each of the level
    PlayLoop(gameData, "medium", &life, indexPlayer, &tempScore);
    PlayLoop(gameData, "hard", &life, indexPlayer, &tempScore);

    DisplayAsciiArt("StylisticTexts/title.txt");

    if (life > 0)
        printf("Game Over, No more phrases to show\n");
    else
        printf("Game Over, No more lives\n");

    if (gameData->scoresRecord[indexPlayer].easyScore +
            gameData->scoresRecord[indexPlayer].mediumScore + gameData->scoresRecord[indexPlayer].hardScore <
        tempScore.easyScore + tempScore.mediumScore + tempScore.hardScore) // if their score for this game is greater than
    {                                                                      // their previous best
        gameData->scoresRecord[indexPlayer] = tempScore;                   // replace their previous best with the current score
        printf("New Personal Best!\n");
    }

    printf("Score: %d\n", tempScore.easyScore + tempScore.mediumScore + tempScore.hardScore);
    printf("Play again? Enter p\nEnter r to return to Menu: ");
    scanf("%c", &opt);

    if (opt == 'r' || opt == 'R') // if the char is r then return to menu
    {
        system("cls");
        PlayMenu(gameData);
        return;
    }
    else if (opt == 'p' || opt == 'P') // play again
    {
        system("cls");
        Play(gameData);
        return;
    }

    while (opt != 'r' || opt != 'R' || opt != 'P' || opt != 'P') // if invalid option then reprompt again
    {
        if (opt == 'r' || opt == 'R') // if the char is r then return to menu
        {
            system("cls");
            PlayMenu(gameData);
            return;
        }
        else if (opt == 'p' || opt == 'P')
        {
            system("cls");
            Play(gameData);
            return;
        }
    }
}

void PlayLoop(struct dataTag *gameData, char *sLevel, int *life, int playerIndex, struct scoresTag *tempScore)
{
    if (*life == 0) // if life is zero dont run
        return;

    int nQuanti = 0, i, randNum, freq;
    int tempArr[MAX_RECORDS];
    Str100 tempPhrase, sAns;

    for (i = 0; i < gameData->currId; i++)
    {
        if (strcmp(gameData->phraseRecords[i].sLevel, sLevel) == 0)
        {
            tempArr[nQuanti] = i; // asign the index of the chosen phrase difficulty to the to tempArr
            nQuanti++;            // keep track of the number of chosen phrase difficulty
        }
    }

    if (strcmp(sLevel, "easy") == 0) // checks what the current level for the stage is
        freq = 3;                    // changes the amount of times the phrases are generated
    else if (strcmp(sLevel, "medium"))

        freq = 2;
    else
        freq = nQuanti;

    for (i = 0; i < freq; i++)
    {
        printf("User: %s\t\t\t\tScore: %d\n", tempScore->sPlayer,
               tempScore->easyScore +
                   tempScore->mediumScore + tempScore->hardScore);

        randNum = randInRange(0, nQuanti - 1);                                 // generate a random index
        strcpy(tempPhrase, gameData->phraseRecords[tempArr[randNum]].sPhrase); // get that easy phrase in the easyArr and copy to temp
        printf("%s Level\t\t\t\tEnter r to abort game and return to menu\nLives: %d\n\n", sLevel, *life);

        removeElemArray(tempArr, randNum, nQuanti); // remove the index if it was already showed
        nQuanti--;                                  // decrement the number of available easy indices

        printf("Phrase: %s\n", tempPhrase);

        fseek(stdin, 0, SEEK_END);
        scanf("%100[^\n]%*c", sAns);
        if (strcmp(sAns, "r") == 0 || strcmp(sAns, "R") == 0) // return to menu
        {
            system("cls");
            PlayMenu(gameData);
            return;
        }

        if (strcmp(tempPhrase, sAns) == 0) // if phrased is typed correctly
        {
            DisplayAsciiArt("StylisticTexts/title.txt");
            printf("Typed Succesfully\n");

            if (strcmp(sLevel, "easy") == 0) // add score
                tempScore->easyScore++;
            else if (strcmp(sLevel, "medium") == 0)

                tempScore->mediumScore += 2;
            else
                tempScore->hardScore += 3;
        }
        else
        {
            DisplayAsciiArt("StylisticTexts/title.txt");
            printf("Typed Incorrectly\n");
            *life += -1; // decrement life
        }

        if (*life == 0)
        {
            return; // gameover
        }
    }
}

/*
    Display Function Only
*/
void ViewScores(struct dataTag *gameData)
{
    int i, longestName = 0;
    char c;
    DisplayAsciiArt("StylisticTexts/viewScores.txt");
    SortScores(gameData);
    char *labelRow = "Total Score\tEasy\t\tMedium\t\tHard\t\tPlayer Name\tRank"; // row for the labels

    for (i = 0; i < gameData->numPlayers; i++)
    {
        if (strlen(gameData->scoresRecord->sPlayer) > longestName)
            longestName = strlen(gameData->scoresRecord->sPlayer); // get the longest player name in the game data
    }

    for (i = 0; i < strlen(labelRow) * 2; i++) // printf "=" equal to the length of the string for the label row and the phrase
        printf("=");
    printf("\n%s\n", labelRow); // print the label row and the border
    for (i = 0; i < strlen(labelRow) * 2; i++)
        printf("=");
    printf("\n");

    for (i = 0; i < gameData->numPlayers; i++) // print the scores of each players in the game data
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%s\t\t%d\n",
               gameData->scoresRecord[i].easyScore + gameData->scoresRecord[i].mediumScore + gameData->scoresRecord[i].hardScore,
               gameData->scoresRecord[i].easyScore, gameData->scoresRecord[i].mediumScore,
               gameData->scoresRecord[i].hardScore, gameData->scoresRecord[i].sPlayer, i + 1);
    }
    do
    {
        printf("Enter r to return to Menu: ");
        fseek(stdin, 0, SEEK_END); // flush to avoid double scanf
        scanf("%c", &c);
    } while (c != 'r');

    if (c == 'r')
    {
        system("cls");
        PlayMenu(gameData);
    }
}