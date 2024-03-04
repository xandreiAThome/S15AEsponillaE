#include <stdio.h>
#include "TypingGame.h"

/*
@param filename: The name of the textFile that contains the ascii art
*/
void DisplayAsciiArt(char fileName[])
{
    FILE *ptr;
    ptr = fopen(fileName, "r"); // open file that contains the ascii art for the title
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