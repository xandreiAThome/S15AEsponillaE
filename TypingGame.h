#define PASSWORD "HelloWorld"

typedef char Str10[11];
typedef char Str100[101];
struct recordsTag
{
    int nId;
    Str10 sLevel;
    int nNumOfChars;
    Str100 sPhrase;
};