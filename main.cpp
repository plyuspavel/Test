#include <ctype.h>
#include "myHeader.h"

int MLstrcmp(const char string1[], const char string2[]);
char** SortStrings(const char ** text, size_t size);
int CopyTextDynamic(const char** text, char** newText, size_t size);
int MLRstrcmp(const char string1[], const char string2[]);
char** SortRevStrings(const char ** text, size_t size);

const int MAX_ADDRESS = 2500;
int main()
{
    size_t textSize = 0;

    printf("Enter the location of input file>\n");
    char inAddress[MAX_ADDRESS] = {};
    if(!scanf("%s", inAddress))
    {
        errno = EIO;
        perror("Some problems with input happened");
        return 1;
    }


    const char** text = (const char**) ReadAllFile(inAddress, &textSize);
    if (text == NULL) {
        perror("Some problems with input happened");
        return 1;
    }

    char outAdress[MAX_ADDRESS] = {};
    printf("Enter the location of output file\n");
    scanf("%s", outAdress);
    FILE* out = 0;
    out = fopen(outAdress, "wb");
    if (out == NULL)
    {
        perror("Some problems with output happened");
        return 1;
    }

    char**  sortOnegin = {};
    sortOnegin = SortRevStrings(text, textSize);
    //PrintStringDynamic((const char**)sortOnegin, textSize);
    
    WriteInFile(out, (const char**) sortOnegin, textSize);
    fclose(out);

    FreeInputDynamic(text);
    free(sortOnegin);
    return 0;

}

int MLstrcmp(const char string1[], const char string2[])
{
    size_t len1 = 0, len2 = 0, len = 0;
    len1 = strlen(string1);

    for (size_t i = 0; i <= len1; i++)
    {
        if (string1[i] == string2[i])
            continue;
        else if (string1[i] < string2[i])
            return -1;
        else return 1;
    }
    return 0;
}

int MLRstrcmp(const char string1[], const char string2[])
{
    size_t len1 = 0, len2 = 0;
    len1 = strlen(string1);
    len2 = strlen(string2);


    if (len1 <= len2)
    {
        if (len2 == 0)
            return 0;
        for (size_t i = 0; i < len1; i++)
        {
            if (string1[len1 - i] == string2[len2 - i])
                continue;
            else if (string1[len1 - i] < string2[len2 - i])
                return -1;
            else return 1;
        }
        if (len1 == len2)
            return 0;
        return -1;
    }
    else
    {
        for (size_t i = 0; i < len2; i++)
        {
            if (string1[len1 - i] == string2[len2 - i])
                continue;
            else if (string1[len1 - i] < string2[len2 - i])
                return -1;
            else return 1;
        }
        return 1;
    }
}

int CopyTextDynamic(const char** text, char** newText, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        newText[i] = (char *) text[i];
    }
    return 0;
}

char** SortStrings(const char ** text, size_t size)
{
    char** sortText = (char **) calloc(size, sizeof(*sortText));
    if(!sortText)
    {
        errno = ENOMEM;
        return NULL;
    }

    CopyTextDynamic(text, sortText, size);

    int end = 0;
    do
    {
        end = 1;
        for (size_t i = 0; i < size - 1; i++)
        {
            if (strcmp(sortText[i], sortText[i+1]) > 0)
            {
                end = 0;
                char* temp = 0;
                temp = sortText[i];
                sortText[i] = sortText[i+1];
                sortText[i+1] = temp;
            }
        }
    }
    while (!end);

    return sortText;
}

char** SortRevStrings(const char ** text, size_t size)
{
    char** sortText = (char **) calloc(size, sizeof(*sortText));
    if(!sortText)
    {
        errno = ENOMEM;
        return NULL;
    }

    CopyTextDynamic(text, sortText, size);

    int end = 0;
    do
    {
        end = 1;
        for (size_t i = 0; i < size - 1; i++)
        {
            if (MLRstrcmp(sortText[i], sortText[i+1]) > 0)
            {
                end = 0;
                char* temp = 0;
                temp = sortText[i];
                sortText[i] = sortText[i+1];
                sortText[i+1] = temp;
            }
        }
    }
    while (!end);

    return sortText;
}





