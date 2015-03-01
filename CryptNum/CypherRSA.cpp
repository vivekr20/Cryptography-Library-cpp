#include "CypherRSA.h"

using namespace std;

RSA::RSA()
{
    p = 0;
    q = 0;
    n = 0;
    phi_n = 0;
    d = 0;
    e = 0;
}
//Requires Debugging pow_mod
RSA::RSA(const CryptNum& pp, const CryptNum& qq, const CryptNum& dd)
{
    p = pp;
    q = qq;
    d = dd;
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    e = CryptNum::inverse_a_mod_m(d, phi_n);
}

RSA::~RSA()
{
}

CryptNum RSA::encrypt_single(const CryptNum& m)
{
    CryptNum c;
    c = CryptNum::pow_mod(m, e, n);
    return c;
}

CryptNum RSA::decrypt_single(const CryptNum& c)
{
    CryptNum m;
    m = CryptNum::pow_mod(c, d, n);
    return m;
}

CryptNum* RSA::encrypt_multiple(CryptNum *m, long long length)
{
    while(length--)
    {
        m[length] = CryptNum::pow_mod(m[length], e, n);
    }
    return m;
}

CryptNum* RSA::decrypt_multiple(CryptNum *c, long long length)
{
    while(length--)
    {
        c[length] = CryptNum::pow_mod(c[length], e, n);
    }
    return c;
}
