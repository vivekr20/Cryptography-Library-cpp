#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "CryptNum.h"

using namespace std;

bool miller_rabin(const CryptNum& num, long iterations)
{
    CryptNum n(num), chk, n1, a, b, chk2;
    long r, j, i;
    if(n < 2)
        return false;
    chk = n % 2;
    if(n != 2 && chk == 0)
        return false;

    n1 = n - 1;
    chk = n1 % 2;
    r = 0;
    while(chk == 0)
    {
        r++;
        n1 /= 2;
        chk = n1 % 2;
    }

    for(j = 1; j <=iterations; j++)
    {
        a = CryptNum::rand_num();
        a %= n;
        b = CryptNum::pow_mod(a, n1, n);//check if this mite be an issue
        chk = b % n;
        if(chk != 1)
        {
            i = 0;
            chk = b % n;
            chk2 = n - 1;
            while((i <= r-1 )&&(chk != chk2))
            {
                i++;
                b *= b;
                b %= n;
                chk = b % n;
                if(chk == 1)
                    return false;
            }
            if(chk != chk2)
                return false;
        }
    }
    return true;
}

CryptNum pollard_rho(const CryptNum& n)
{
    CryptNum x, E, r, d, s, c, nn(n), ab;
    x = CryptNum::rand_num();//ideally a random number
    x = x % n;
    r = 1;
    E = x;
    c = CryptNum::rand_num();//ideally a random number
    c = c% n;
    while(1)
    {
        for(s = 1; s <= r; s++)
        {
            x *= x;
            x = x % n;
            x += c;
            x = x % n;
            ab = x - E;
            if(ab < 0)
                ab += n;
            d = CryptNum::GCD(ab, n);

            if(d>1 && d<n)
                return d;
        }
        E = x;
        r *=2;
    }
}

CryptNum brent(const CryptNum& n)
{
    CryptNum nn(n), tmp;
    tmp = nn % 2;
    if(tmp == 0)
        return 2;
    tmp = CryptNum::is_prime(nn);
    if(tmp == 1)
    {
        return nn;
    }
    CryptNum y, c, m, g, r, q, x, i, k, ys;
    y = rand();
    y = y % nn;
    c = rand();
    c = c % nn;
    m = rand();
    m = m % nn;
    g = 1;
    r = 1;
    q = 1;
    while(g == 1)
    {
        x = y;
        for(i = 0; i < r; i++)
        {
            y *= y;
            y = y % nn;
            y += c;
            y = y % nn;
        }
        k = 0;
        while(k < r && g == 1)
        {
            ys = y;
            for(i = 0; i < CryptNum::min(m, (r - k)); i++)
            {
                y *= y;
                y = y % nn;
                y += c;
                y = y % nn;
                q = q * CryptNum::abs(x - y);
                q = q % nn;
            }
            g = CryptNum::GCD(q, nn);
            k += m;
        }
        r *= 2;
    }
    if(g == nn)
    {
        while(1)
        {
            ys *= ys;
            ys = ys % nn;
            ys += c;
            ys = ys % nn;
            g = CryptNum::GCD(CryptNum::abs(x - ys), nn);
            if(g > 1)
                break;
        }
    }
    return g;
}

void prime_factors(const CryptNum& n)
{
    CryptNum i, nn(n);
    cout<<endl;
    while(nn > 1)
    {
        i = brent(nn);
        nn /=i;
        cout<<i<<endl;
    }
}
