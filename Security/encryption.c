#include "encryption.h"
#include <string.h>
#include <math.h>
#define xor (int)pow(2, 31) - 1
#define key 5

void stringEncryption(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] += key;
    }
}

void stringDecryption(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] -= key;
    }
}

int numberEncryption(int num)
{
    return num ^ xor;
}

int numberDecryption(int num)
{
    return num ^ xor;
}