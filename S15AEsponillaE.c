#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO
// Start on the Manage Data feature

typedef char Str10[11];
typedef char Str100[101];
struct recordsTag
{
    int nId;
    Str10 sLevel;
    int nNumOfChars;
    Str100 sPhrase;
};

void ManageData();
void Play();

int main()
{
    // Display the options in the main menu
    int i, nSelected = -1;
    Str10 sOptions[3] = {"Manage Data", "Play", "Exit"};
    for (i = 0; i < 3; i++)
    {
        printf("%d - %s\n", i, sOptions[i]);
    }

    // prompts the user again if the input is invalid
    while (nSelected != 0 && nSelected != 1 && nSelected != 2)
    {
        printf("Choose Option: ");
        scanf("%d", &nSelected);
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

    return 0;
}

void ManageData()
{

    return;
}
void Play()
{

    return;
}
