#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "CryptNum.h"

//Simple Cyphers
CryptNum *shift_cypher(CryptNum *message, long length, CryptNum k, CryptNum m)
{
    long i;
    for(i=0;i<length;i++)
    {
        message[i] += k;
        message[i]  = message[i] % m;
    }
    return message;
}

CryptNum *affine_cypher(CryptNum *message, long length, CryptNum a, CryptNum h, CryptNum m)
{
    long i;
    for(i=0;i<length;i++)
    {
        message[i] *= a;
        message[i] += h;
        message[i]  = message[i] % m;
    }
    return message;
}
