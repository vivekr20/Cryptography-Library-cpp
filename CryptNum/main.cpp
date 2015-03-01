#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "CryptNum.h"
#include "Cyphers.h"
#include "CypherRSA.h"
#include "Primality_and_Factorization.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    CryptNum a("-88"), b(7), c;
    c = a * b;


    //cout << endl << a << " * " << b << " = " << c << endl;
    c = a % b;
    //cout << endl << a << " % " << b << " = " << c << endl;
    string s = "1000";
    c = CryptNum::factorial(s);
    c = CryptNum::abs(c);
    //cout << endl << s << " !" << " = " << c << endl<<CryptNum::number_of_digit(c);

    CryptNum n1(99999), n2(99);

    cout<<endl<<"GCD of 99999 and 99 is "<<CryptNum::GCD(n1, n2)<<endl;

    cout<<endl<<endl<<"phi("<<s<<") is "<<CryptNum::phi(s)<<endl;

    CryptNum e(5), f(73), m(109);
    cout<<endl<<"\n\n"<<e<<" ^ "<<f<<" mod "<<m<<" "<<CryptNum::pow_mod(e, f, m)<<endl<<"\n\n"<<endl;


    CryptNum r(5), t(52), g;

    a = 5;

    b = 83;

    m = 26;

    cout<<endl<<endl<<"5 ^ 52 mod "<<s<<" "<<CryptNum::pow_mod(r, t, s)<<endl<<endl;

    //cout<<"\n\n 64x = 83 mod 105, x = "<<CryptNum::ax_b_mod_m(a, b, m)<<"\n\n";

    cout<<"\n\ninverse of 64 mod 107 is "<<CryptNum::inverse_a_mod_m(64, 107)<<"\n\n";

    CryptNum w[100], *q, *ll;

    //q = (CryptNum*)malloc(100*sizeof(CryptNum));

    for(int i = 0;i <100; i++)
    {
        w[i] = i;
    }

    q = shift_cypher(w, 100, a, m);

    //cout<<"\n\n w[6] is "<<q[6]<<endl;

    cout<<"\n\ninverse of  64 mod 59 is : "<<CryptNum::inverse_a_mod_m(64, 59);

    cout<<"\n\nRSA cypher testing:\n\n"<<"p = 47, q = 59, d = 157\n";

    RSA test(47, 59, 157);

    m = 2015;

    c = test.encrypt_single(m);

    cout<<"\n\nencryption of "<<m<<" is : "<<c<<endl;


    q[0] = 920;
    q[1] = 1900;
    q[2] = 112;
    q[3] = 1100;

    cout<<"\n------------------------------------------\nkey  words: "<<q[0]<<","<<q[1]<<","<<q[2]<<","<<q[3]<<"\n------------------------------------------\n";

    ll = test.encrypt_multiple(w, 4);

    cout<<"\n------------------------------------------\nCode words: "<<ll[0]<<","<<ll[1]<<","<<ll[2]<<","<<ll[3]<<"\n------------------------------------------\n";

    cout<<"\n\norder of 5 mod 12 is "<<CryptNum::order_a_mod_m(5, 12)<<"\n\n";

    CryptNum u("45353"), v("4656363");

//prime factors
    //cout<<"\n\n\t"<<brent(u)<<"\n\n";
    //prime_factors(v);

    CryptNum aa(2), pp(54), power(119);

    /*for(int i = 1;i<60; i++)
        cout<<"\njocobi of ("<<i<<"/97) is : "<<CryptNum::jacobi( i, 97)<<endl;
*/

    cout<<"\nA set of randomly generated numbers:\n";

    for(int i = 0; i < 10; i++)
        cout<<"\n"<<CryptNum::rand_num() % m<<endl;
    char *str, *pri = "prime", *npri = "not prime";
    if(miller_rabin(1292927, 10))
        str = pri;
    else
        str = npri;

    cout<<"\n\nprime testing using miller rabin: \t 1292927 is "<<str<<endl;

    prime_factors(1292927);

    aa = 111;
    pp = 64;
    m = 86453;

    aa = aa ^ pp;
    aa %= m;
    cout<<"\n\n\t"<<aa<<endl;

    aa = 111;
    pp = 64;
    CryptNum ppp("4534625245645634634534534534562625325242352351342354");
    m = 86453;

    aa = CryptNum::pow_mod(aa, pp, m);
    cout<<"\n\n\t"<<aa<<endl;

    return 0;
}
