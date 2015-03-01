#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "CryptNum.h"

class RSA
{
    public:
        RSA();
        RSA(const CryptNum&, const CryptNum&, const CryptNum&);
        virtual ~RSA();
        CryptNum encrypt_single(const CryptNum&);
        CryptNum decrypt_single(const CryptNum&);
        CryptNum *encrypt_multiple(CryptNum*, long long);
        CryptNum *decrypt_multiple(CryptNum*, long long);

    private:
        CryptNum p, q, d;
        CryptNum n, phi_n, e;
};
