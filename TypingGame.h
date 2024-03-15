#ifndef TYPINGGAME_H_
#define TYPINGGAME_H_

#define PASSWORD "hi"
#define MAX_RECORDS 100

typedef char Str10[11];
typedef char Str100[101];
typedef char Str20[21];
typedef char Str30[31];
struct recordsTag
{
    int nId; // nId will be the same as their index in the array, so nId must be changed when importing and deleting phrases
    Str10 sLevel;
    int nNumOfChars;
    Str100 sPhrase;
};

struct scoresTag
{
    int nScore;
    Str20 sPlayer;
    Str10 sLevel;
};

struct dataTag
{
    int currId;
    int numPlayers;
    struct recordsTag phraseRecords[MAX_RECORDS];
    struct scoresTag scoresRecord[MAX_RECORDS];
};

#endif