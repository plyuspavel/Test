//
// Created by plyus.pavel on 21.09.2015.
//



#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

long InputLong(const char message[])
{
    printf("%s",message);

    long num = 0;
    if (scanf("%ld", &num))
        return num;
    else
    {
        errno = EIO;
        return 0;
    }
}

long InputDouble(const char message[])
{
    printf("%s",message);

    double num = 0;
    if (scanf("%lg", &num))
        return num;
    else
    {
        errno = EIO;
        return 0;
    }
}

int InputLongArray(long arr[], long sizeArr)
{
    for (long i = 0; i < sizeArr; i++)
    {
        arr[i] = InputLong("");
        if (arr[i] == 0)
            if (errno)
                return -1;
    }
    return 0;
}

int InputDoubleArray(double arr[], long sizeArr)
{
    for (long i = 0; i < sizeArr; i++)
    {
        arr[i] = InputDouble("");
        if (arr[i] == 0)
            if (errno)
                return -1;
    }
    return 0;
}

long* InputDynamicLongArray(long size)
{
    long* arr = (long*) calloc(size, sizeof(*arr));
    if (!arr)
    {
        errno = ENOMEM;
        return NULL;
    }

    for (long i = 0; i < size; i++)
    {
        if ((arr[i] = InputLong("")) == 0 && errno)
        {
            free(arr);
            return NULL;
        }
    }

    return arr;
}

double* InputDynamicDoubleArray(long size)
{
    double* arr = (double*) calloc(size, sizeof(*arr));
    if (!arr)
    {
        errno = ENOMEM;
        return NULL;
    }

    for (long i = 0; i < size; i++)
    {
        if ((arr[i] = InputDouble("")) == 0 && errno)
        {
            free(arr);
            return NULL;
        }
    }

    return arr;
}


const long long CountStrings(char* buffer, long length)
{
    if (!buffer)
    {
        errno = EIO;
        return -1;
    }

    long long count = 1;
    for (long long i = 0; i < length; i++)
        if ((buffer[i] == '\n'))
            count++;
    if (length > 0)
        return count;
    return 0;
}

char** ReadAllFile(const char address[], size_t* size)
{
    FILE* f = 0;
    f = fopen(address, "rb");
    if (!f)
    {
        errno = ENOFILE;
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    size_t length = 0;
    length = ftell(f);

    if (length == 0)
    {
        errno = EIO;
        fclose(f);
        return NULL;
    }

    rewind(f);

    char* buffer = (char*) calloc(length, sizeof(*buffer));
    if (!buffer)
    {
        errno = ENOMEM;
        fclose(f);
        return NULL;
    }

    fread(buffer, sizeof(*buffer), length, f);

    fclose(f);

    long nStrings = 0;
    nStrings = CountStrings(buffer, length);

    char** text = (char **) calloc(nStrings, sizeof(*text));
    if(!text)
    {
        errno = ENOMEM;
        free(buffer);
        return NULL;
    }

    text[0] = &buffer[0];
    for(long long i = 0, n = 1; i < length; i++)
    {
        if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
            text[n++] = &buffer[i] + 2;
        }
    }

    *size = nStrings;
    return text;
}

int FreeInputDynamic(const char** text)
{
    if (text == NULL)
    {
        return -1;
    }

    free((char*)text[0]);
    free(text);
    return 0;
}

int PrintStringDynamic(const char** text, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n", text[i]);
    }
    return 0;
}

int WriteInFile(FILE* f, const char** text, size_t size)
{
    if (f == NULL || text == NULL)
    {
        errno = EEXIST;
        return -1;
    }

    if (size < 1)
    {
        errno = EIO;
        return -1;
    }

    for (size_t i = 0; i < size; i++)
    {
        fprintf(f, "%s\r\n", text[i]);
        if (errno)
            return -1;
    }
    return 0;
}





