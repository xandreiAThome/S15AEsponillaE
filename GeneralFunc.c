#include <stdio.h>
#include "TypingGame.h"
#include <math.h>

/*
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
Precondition for positive integers only
@param n: the integer that will be measured
@return returns the number of digits in the integer
*/
int NumLen(int n)
{
    int nLen = 0;
    while (n > 0) // cut off one digit from the left and increment nLen as long as n is still greater than zero
    {
        n /= 10;
        nLen++;
    }

    return nLen;
}

/*
    @param *gameData: the pointer variable for the gamedata structure in main
    @param nIndex: input a negative if you want to print the whole array, otherwise input the index of the record to print
*/
void DisplayTable(struct dataTag *gameData, int nIndex)
{
    char *labelRow = "ID\t\tLevel\t\tNo. of Chars\t\tPhrase"; // row for the labels
    // put in a variable to be able to take the length of the string

    int longestPhrase = 0, i;

    if (nIndex < 0)
        for (i = 0; i < gameData->currId; i++)
        {
            if (gameData->phraseRecords[i].nNumOfChars > longestPhrase)
                longestPhrase = gameData->phraseRecords[i].nNumOfChars; // get the longest phrase in the game data
        }

    int nLen = (strlen(labelRow) * 2) + abs(strlen("Phrase") - longestPhrase); // get the lenght of the label row

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