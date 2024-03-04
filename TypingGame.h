#ifndef TYPINGGAME_H_
#define TYPINGGAME_H_

#define PASSWORD "hi"

typedef char Str10[11];
typedef char Str100[101];
typedef char Str20[21];
struct recordsTag
{
    int nId;
    Str10 sLevel;
    int nNumOfChars;
    Str100 sPhrase;
};

#endif