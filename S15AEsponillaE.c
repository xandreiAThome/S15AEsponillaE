#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "TypingGame.h"

// TODO
// Start on the Manage Data feature

void ManageDataLogin();
void Play();
void Menu();
void ManageDataMenu();
int DisplayOptions(Str20 sOptions[], int size);

struct recordsTag Data[100];

int main()
{
    Menu();
    return 0;
}

void Menu()
{
    system("cls");
    FILE *titlePtr;
    titlePtr = fopen("StylisticTexts/title.txt", "r"); // open file that contains the ascii art for the title
    char c;
    do
    {
        c = fgetc(titlePtr); // print each character from the file
        printf("%c", c);
    } while (c != EOF);
    printf("\n");

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

    fclose(titlePtr);
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

    if (strcmp(password, PASSWORD) == 0)
    {
        system("cls");
        printf("\nLogged in Succesflly\n");

        FILE *titlePtr = fopen("StylisticTexts/manageData.txt", "r");
        char c;
        while (c != EOF)
        {
            c = getc(titlePtr); // print Manage Data in the ascii art text
            printf("%c", c);
        }
        printf("\n");
        fclose(titlePtr);
        ManageDataMenu();
    }

    if (bGoToMenu)
    {
        Menu();
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
        Menu();
        break;

    default:
        break;
    }
}

void Play()
{

    return;
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