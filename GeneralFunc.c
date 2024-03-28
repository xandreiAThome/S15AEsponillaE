#include <stdio.h>
#include "TypingGame.h"
#include <math.h>

/*
    Display Function Only
    @param filename: The name of the textFile that contains the ascii art
*/
void DisplayAsciiArt(char fileName[])
{
    FILE *ptr;
    if ((ptr = fopen(fileName, "r")) == NULL)
    { // open file that contains the ascii art for the title
        printf("File does not exist");
        return;
    }

    char c;
    do
    {
        c = fgetc(ptr); // print each character from the file
        printf("%c", c);
    } while (c != EOF); // until it reaches the end of the file
    printf("\n");
    fclose(ptr);
}

/*
    @param sOptions: the array of strings of the available options
    @param size: the size of the array
    @return returns the index that was chosen
*/
int DisplayOptions(Str20 sOptions[], int size)
{
    int nSelected = -1, i;
    for (i = 0; i < size; i++) // Display the options in the main menu
    {
        printf("%d - %s\n", i, sOptions[i]);
    }

    printf("Choose Option: ");
    scanf("%d", &nSelected);
    // prompts the user again if the input is invalid
    if (nSelected < 0 || nSelected > (size - 1))
        while (1)
        {
            if (nSelected >= 0 && nSelected <= size - 1)
            {
                return nSelected; // returns the chosen option
            }
            printf("Invalid Option Choose Again: ");
            scanf("%d", &nSelected);
            fflush(stdin);
        }

    return nSelected; // if the first input is valid then return it
}

/*
    Display Function Only
    @param *gameData: the pointer variable for the gamedata structure in main
    @param nIndex: input a negative if you want to print the whole array, otherwise input the index of the record to print
*/
void DisplayTable(struct dataTag *gameData, int nIndex)
{
    char *labelRow = "ID\t\tLevel\t\tNo. of Chars\t\tPhrase"; // row for the labels
    // put in a variable to be able to take the length of the string

    int longestPhrase = 0, i, nLen;

    if (nIndex < 0)
        for (i = 0; i < gameData->currId; i++)
        {
            if (gameData->phraseRecords[i].nNumOfChars > longestPhrase)
                longestPhrase = gameData->phraseRecords[i].nNumOfChars; // get the longest phrase in the game data
        }

    nLen = (strlen(labelRow) * 2) + abs(strlen("Phrase") - longestPhrase); // get the lenght of the label row

    for (i = 0; i < nLen; i++) // printf "=" equal to the length of the string for the label row and the phrase
        printf("=");
    printf("\n%s\n", labelRow); // print the label row and the border
    for (i = 0; i < nLen; i++)
        printf("=");
    printf("\n");

    if (nIndex < 0)
        for (i = 0; i < gameData->currId; i++) // print each of the records
            printf("%d\t\t%s\t\t%d\t\t\t%s\n", gameData->phraseRecords[i].nId, gameData->phraseRecords[i].sLevel,
                   gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
    else
        // print only the specified record
        printf("%d\t\t%s\t\t%d\t\t\t%s\n", gameData->phraseRecords[nIndex].nId, gameData->phraseRecords[nIndex].sLevel,
               gameData->phraseRecords[nIndex].nNumOfChars, gameData->phraseRecords[nIndex].sPhrase);
}

/*
    @param *gameData: the pointer variable for the gamedata structure in main
*/
void ImportScores(struct dataTag *gameData, char *fileName)
{
    FILE *inPtr;

    if ((inPtr = fopen(fileName, "r")) == NULL) // if file does not exist terminate function
    {
        printf("Scores File Does not exist");
        return;
    }

    while (fscanf(inPtr, "%s", gameData->scoresRecord[gameData->numPlayers].sPlayer) > 0 &&
           fscanf(inPtr, "%d", &gameData->scoresRecord[gameData->numPlayers].easyScore) > 0 &&
           fscanf(inPtr, "%d", &gameData->scoresRecord[gameData->numPlayers].mediumScore) > 0 &&
           fscanf(inPtr, "%d", &gameData->scoresRecord[gameData->numPlayers].hardScore) > 0)
    {
        gameData->numPlayers++; // increase the num of players recorded to have scores
    }

    fclose(inPtr);
}

/*
    @param *gameData: the pointer variable for the gamedata structure in main
*/
void ExportScores(struct dataTag *gameData, char *fileName)
{
    FILE *outPtr;
    int i;

    outPtr = fopen(fileName, "w");

    for (i = 0; i < gameData->numPlayers; i++) // iterate over each of the phrase in the records and print it to the file
    {
        fprintf(outPtr, "%s\n%d\n%d\n%d\n\n", gameData->scoresRecord[i].sPlayer, gameData->scoresRecord[i].easyScore,
                gameData->scoresRecord[i].mediumScore, gameData->scoresRecord[i].hardScore);
        fflush(outPtr);
    }

    fclose(outPtr);
}

/*
    @param *gameData: the pointer variable for the gamedata structure in main
    @param key: the string that will be searched for in the array
    @param mode: 0 - for searching phrases in the phraseRecords, 1 - for searching names in the scoresRecord
    @return returns the index of the matched string, else returns -1
*/
int StringInArray(struct dataTag *gameData, Str20 key, int mode)
{
    int i;
    if (mode == 0) // for searching string in the phraseRecords
    {
        for (i = 0; i < gameData->currId; i++)
        {
            if (strcmp(key, gameData->phraseRecords[i].sPhrase) == 0)
                return i;
        }
    }
    else if (mode == 0) // for searching names in the scoresRecords
    {
        for (i = 0; i < gameData->numPlayers; i++)
        {
            if (strcmp(key, gameData->scoresRecord[i].sPlayer) == 0)
                return i;
        }
    }

    return -1; // if there is no match
}

/*
    Precondition: non negative parameters
    @param nMin: the minimum number that can be generated
    @param nMax: the maximum number that can be generated
    @return random number between min and max
*/
int randInRange(int nMin, int nMax)
{
    return rand() % (nMax + 1 - nMin) + nMin; // returns random numbers between and or the min and max values themselves
}

/*
    Precondition the last element in the array will just be assigned to zero
    @param arr: the array to be modified
    @param key: the index of the element to be removed
    @param size: the size of the array
*/
void removeElemArray(int arr[], int key, int size)
{
    int temp[size], i;

    for (i = 0; i < size; i++) // copy the contents of arr to temp except the element to be removed
    {
        if (i > key)
        {
            temp[i - 1] = arr[i];
        }
        else if (i < key)
        {
            temp[i] = arr[i];
        }
    }
    for (i = 0; i < size - 1; i++) // copy back to the original arr
    {
        arr[i] = temp[i];
    }
    arr[size - 1] = 0; // empty the last index of the arr
}

/*
    Sorts the scores array from highest to lowest
    @param *gameData: the pointer variable for the gamedata structure in main
*/
void SortScores(struct dataTag *gameData)
{
    struct scoresTag tempScore;
    int i, j, maxIndex;

    for (i = 0; i < gameData->numPlayers - 1; i++)
    {
        maxIndex = i;
        for (j = i; j < gameData->numPlayers; j++)
        {
            // if the current j index is greater than the max index, then make j the max index
            if (gameData->scoresRecord[j].easyScore + gameData->scoresRecord[j].mediumScore + gameData->scoresRecord[j].hardScore >
                gameData->scoresRecord[maxIndex].easyScore + gameData->scoresRecord[maxIndex].mediumScore + gameData->scoresRecord[maxIndex].hardScore)
                maxIndex = j;
        }
        if (maxIndex != i)
        {
            // swap the max index and i
            tempScore = gameData->scoresRecord[maxIndex];
            gameData->scoresRecord[maxIndex] = gameData->scoresRecord[i];
            gameData->scoresRecord[i] = tempScore;
        }
    }
}

// void displayData(struct dataTag *gameData)
// {
//     int i;
//     for (i = 0; i < 7; i++) // print each of the records
//         printf("%d\t\t%s\t\t%d\t\t\t%s\n", gameData->phraseRecords[i].nId, gameData->phraseRecords[i].sLevel,
//                gameData->phraseRecords[i].nNumOfChars, gameData->phraseRecords[i].sPhrase);
//     printf("\n");
// }