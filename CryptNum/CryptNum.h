#ifndef CRYPTNUM_H
    #define	CRYPTNUM_H

    #include <string>
    #include <iostream>

using namespace std;

class CryptNum
{

public:
    CryptNum();
    CryptNum(const CryptNum&);
    CryptNum(int);
    CryptNum(long long);
    CryptNum(long);
    CryptNum(string);
    virtual ~CryptNum();
    CryptNum operator +(const CryptNum&);
    CryptNum operator -(const CryptNum&);
    CryptNum operator *(const CryptNum&);
    CryptNum operator /(const CryptNum&);
    CryptNum operator %(const CryptNum&);
    CryptNum operator ^(CryptNum&);
    void operator +=(const CryptNum&);
    void operator -=(const CryptNum&);
    void operator *=(const CryptNum&);
    void operator /=(const CryptNum&);
    void operator %=(const CryptNum&);
    CryptNum & operator ++();
    CryptNum operator ++(int);
    CryptNum & operator --();
    CryptNum operator --(int);
    void operator =(const CryptNum&);
    bool operator ==(const CryptNum&);
    bool operator !=(const CryptNum&);
    bool operator<(const CryptNum&);
    bool operator <=(const CryptNum&);
    bool operator>(const CryptNum&);
    bool operator >=(const CryptNum&);
    friend ostream & operator <<(ostream&, const CryptNum&);
    static CryptNum factorial(const CryptNum&);
    static bool is_prime(const CryptNum&);
    static bool is_even(const CryptNum&);
    static long sum_of_digit(const CryptNum&);
    static int number_of_digit(const CryptNum&);
    //mine
    static CryptNum abs(const CryptNum&);
    static CryptNum min(const CryptNum&, const CryptNum&);
    static CryptNum GCD(const CryptNum&, const CryptNum&);
    static CryptNum phi(const CryptNum&);
    static CryptNum pow_mod(const CryptNum&, const CryptNum&, const CryptNum&);
    static CryptNum ax_b_mod_m(const CryptNum&, const CryptNum&, const CryptNum&);
    static CryptNum inverse_a_mod_m(const CryptNum&, const CryptNum&);
    static CryptNum order_a_mod_m(const CryptNum&, const CryptNum&);
    static bool is_primitive_root(const CryptNum&, const CryptNum&);
    static CryptNum index_g(const CryptNum&, const CryptNum&, const CryptNum&);
    static int jacobi(const CryptNum&, const CryptNum&);
    static CryptNum rand_num();

private:
    char *number;

    enum SIGN {
        negative = -1,
        zero,
        positive
    };
    SIGN sign;
};

#endif        /* CRYPTNUM_H */
