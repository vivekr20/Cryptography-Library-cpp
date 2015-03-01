#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "CryptNum.h"

using namespace std;

const short divisionByZero = 4;

template <class Type>
int
digitCount(Type number)
{
    if (!number)
        return 1;
    int digit = 0;
    while (number)
    {
        digit++;
        number /= 10;
    }
    return digit;
}

void * CALLOC(unsigned int nElement, unsigned int size)
{
    void *ptr = calloc(nElement, size);
    if (nElement && size && !ptr)
    {
        cerr << "memory allocation failed\n";
        exit(0);
    }
    return ptr;
}

bool lessThan(const char *number1, const char *number2)
{
    unsigned long length1 = strlen(number1), length2 = strlen(number2);
    if (length1 < length2)
        return true;
    else if (length1 > length2)
        return false;
    else
    {
        for (unsigned long i = 0; i < length1; i++)
        {
            if (number1[i] < number2[i])
                return true;
            else if (number1[i] > number2[i])
                return false;
        }
        return false;
    }
}

bool equal(const char *number1, const char *number2)
{
    if (!strcmp(number1, number2))
        return true;
    return false;
}

CryptNum addition(const char *number1, const char *number2)
{
    unsigned int minLength = strlen(number1) <= strlen(number2) ? strlen(number1)
            : strlen(number2),
            maxLength = strlen(number1) >= strlen(number2) ? strlen(number1)
            : strlen(number2), i;
    char *temp1 = (char *) CALLOC(maxLength + 1, sizeof (char)),
            *temp2 = (char *) CALLOC(maxLength + 1, sizeof (char)),
            *result = (char *) CALLOC(maxLength + 2, sizeof (char));
    for (i = 1; i <= maxLength - minLength; i++)
        *(temp1 + i - 1) = '0';
    if (minLength == strlen(number1))
    {
        strcpy(temp1 + i - 1, number1);
        strcpy(temp2, number2);
    }
    else
    {
        strcpy(temp1 + i - 1, number2);
        strcpy(temp2, number1);
    }
    memset(result, '0', maxLength + 1);
    result[maxLength + 1] = '\0';
    for (int i = maxLength - 1; i >= 0; i--)
    {
        result[i + 1] += temp1[i] + temp2[i] - 2 * '0';
        if (result[i + 1] > '9')
        {
            result[i + 1] -= 10;
            result[i] = '1';
        }
    }
    free(temp1);
    free(temp2);
    i = 0;
    while (result[i + 1] != '\0' && result[i] == '0')
        i++;
    CryptNum sum(result + i);
    free(result);
    return sum;
}

CryptNum subtraction(const char *number1, const char *number2)
{
    unsigned int minLength, maxLength;
    minLength = strlen(number1) <= strlen(number2) ? strlen(number1)
            : strlen(number2);
    maxLength = strlen(number1) >= strlen(number2) ? strlen(number1)
            : strlen(number2);
    char *temp1 = (char *) CALLOC(maxLength + 1, sizeof (char)),
            *temp2 = (char *) CALLOC(maxLength + 1, sizeof (char));
    char *result;
    result = (char *) CALLOC(maxLength + 1, sizeof (char));
    unsigned int i;
    if (minLength != maxLength)
    {
        for (i = 1; i <= maxLength - minLength; i++)
            *(temp1 + i - 1) = '0';
        if (minLength == strlen(number1))
        {
            strcpy(temp1 + i - 1, number1);
            strcpy(temp2, number2);
        } else
        {
            strcpy(temp1 + i - 1, number2);
            strcpy(temp2, number1);
        }
    }
    else
    {
        strcpy(temp1, number1);
        strcpy(temp2, number2);
        for (i = 0; i <= maxLength - 1; i++) {
            if (number1[i] < number2[i]) {
                strcpy(temp1, number1);
                strcpy(temp2, number2);
                break;
            } else if (number1[i] > number2[i]) {
                strcpy(temp2, number1);
                strcpy(temp1, number2);
                break;
            }
        }
    }
    for (i = 0; i <= maxLength - 1; i++)
        result[i] = '0';
    result[i] = '\0';
    for (int i = maxLength - 1; i >= 0; i--)
    {
        result[i] += temp2[i] - temp1[i];
        if (result[i] < '0')
        {
            result[i] += 10;
            temp1[i - 1] += 1;
        }
    }
    free(temp1);
    free(temp2);
    i = 0;
    while (result[i + 1] != '\0' && result[i] == '0')
        i++;
    CryptNum subtract(result + i);
    free(result);
    return subtract;
}

CryptNum division(const char *number1, const char *number2)
{
    CryptNum result(0);
    char zero[] = "0";
    CryptNum mulTable[11];
    if (equal(number2, zero))
        throw divisionByZero;
    else if (equal(number1, zero))
        return result;
    else if (lessThan(number1, number2))
        return result;
    else
    {
        for (int i = 0; i < 11; i++)
        {
            CryptNum temp(number2), multiplier(i);
            mulTable[i] = temp * multiplier;
        }
        int minLength = strlen(number2), maxLength = strlen(number1);
        CryptNum ratio(0), multiplier(10);
        char tempDividend[maxLength + 1];
        strncpy(tempDividend, number1, minLength);
        tempDividend[minLength] = '\0';
        CryptNum partialDividend(tempDividend);
        for (int i = minLength + 1; i <= maxLength + 1; i++)
        {
            int count = 0;
            while (mulTable[count] < partialDividend)
                count++;
            if (mulTable[count] != partialDividend)
                count--;
            CryptNum counter(count);
            ratio = (ratio * multiplier) + counter;
            if (!count)
            {
                char ch[2];
                ch[0] = number1[i - 1];
                ch[1] = '\0';
                CryptNum nextDigit(ch);
                partialDividend = (partialDividend * multiplier) + nextDigit;
            }
            else
            {
                partialDividend -= mulTable[count];
                char ch[2];
                ch[0] = number1[i - 1];
                ch[1] = '\0';
                CryptNum nextDigit(ch);
                partialDividend = (partialDividend * multiplier) + nextDigit;
            }
        }
        result = ratio;
    }
    return result;
}

CryptNum::CryptNum()
{
    number = (char *) CALLOC(1, sizeof (char));
    *number = '\0';
}

CryptNum::CryptNum(const CryptNum& original)
{
    number = (char *) CALLOC(strlen(original.number) + 1, sizeof (char));
    strcpy(number, original.number);
    sign = original.sign;
}

CryptNum::CryptNum(int num)
{
    if (num < 0)
    {
        sign = negative;
        num *= -1;
    }
    else if (num > 0)
        sign = positive;
    else
        sign = zero;
    int i = digitCount<int> (num);
    number = (char *) CALLOC(i + 1, sizeof (char));
    *(number + i) = '\0';
    if (!num)
        *number = '0';
    while (num)
    {
        i--;
        *(number + i) = num % 10 + '0';
        num /= 10;
    }
}

CryptNum::CryptNum(long num)
{
    if (num < 0)
    {
        sign = negative;
        num *= -1;
    }
    else if (num > 0)
        sign = positive;
    else
        sign = zero;
    int i = digitCount<long> (num);
    number = (char *) CALLOC(digitCount(num) + 1, sizeof (char));
    *(number + i) = '\0';
    if (!num)
        *number = '0';
    while (num)
    {
        i--;
        *(number + i) = num % 10 + '0';
        num /= 10;
    }
}

CryptNum::CryptNum(long long num)
{
    if (num < 0)
    {
        sign = negative;
        num *= -1;
    }
    else if (num > 0)
        sign = positive;
    else
        sign = zero;
    int i = digitCount<long long> (num);
    number = (char *) CALLOC(digitCount(num) + 1, sizeof (char));
    *(number + i) = '\0';
    if (!num)
        *number = '0';
    while (num)
    {
        i--;
        *(number + i) = num % 10 + '0';
        num /= 10;
    }
}

CryptNum::CryptNum(string str)
{
    sign = positive;
    if (str[0] == '-')
    {
        sign = negative;
        str.erase(0, 1);
    }
    char *temp = (char *) CALLOC(str.length() + 1, sizeof (char));
    strcpy(temp, str.c_str());
    unsigned int i = 0;
    while (temp[i + 1] != '\0' && temp[i] == '0')
        i++;
    number = (char *) CALLOC(strlen(temp + i) + 1, sizeof (char));
    strcpy(number, temp + i);
    if (strlen(number) == 1 && number[0] == '0')
        sign = zero;
    free(temp);
}

CryptNum::~CryptNum()
{
    free(number);
}

void CryptNum::operator=(const CryptNum& num)
{
    free(this->number);
    this->number = (char *) CALLOC(strlen(num.number) + 1, sizeof (char));
    strcpy(this->number, num.number);
    this->sign = num.sign;
    return;
}

CryptNum CryptNum::operator+(const CryptNum& num)
{
    CryptNum sum;
    if (this->sign == zero)
        sum = num;
    if (num.sign == zero)
        sum = *this;
    if (this->sign != zero && num.sign != zero)
    {
        if (this->sign == num.sign)
        {
            sum = addition(this->number, num.number);
            sum.sign = this->sign;
        }
        else
        {
            if (equal(this->number, num.number))
            {
                CryptNum temp(0);
                sum = temp;
            }
            else
            {
                sum = subtraction(this->number, num.number);
                if (lessThan(this->number, num.number))
                    sum.sign = num.sign;
                else
                    sum.sign = this->sign;
            }
        }
    }
    return sum;
}

CryptNum CryptNum::operator*(const CryptNum& num)
{
    unsigned int minLength = strlen(this->number) <= strlen(num.number) ? strlen(this->number)
            : strlen(num.number),
            maxLength = strlen(this->number) >= strlen(num.number) ? strlen(this->number)
            : strlen(num.number);
    char *shortNum = (char *) CALLOC(minLength + 1, sizeof (char)),
            *longNum = (char *) CALLOC(maxLength + 1, sizeof (char)),
            **mulTable = (char **) CALLOC(10, sizeof (char *));
    memset(mulTable, NULL, 10);
    CryptNum result(0);
    SIGN resultSign = positive;
    if (this->sign == zero || num.sign == zero)
        resultSign = zero;
    else if (this->sign != zero && num.sign != zero && this->sign != num.sign)
        resultSign = negative;
    if (minLength == strlen(this->number))
    {
        strcpy(shortNum, this->number);
        strcpy(longNum, num.number);
    }
    else
    {
        strcpy(shortNum, num.number);
        strcpy(longNum, this->number);
    }
    for (int i = minLength - 1, mulFactor = 0; i >= 0; i--, mulFactor++)
    {
        if (shortNum[i] == '0')
            continue;
        if (!mulTable[shortNum[i] - '0'])
        {
            mulTable[shortNum[i] - '0'] = (char *) CALLOC(maxLength + 2, sizeof (char));
            for (unsigned int j = 0; j <= maxLength; j++)
                mulTable[shortNum[i] - '0'][j] = '0';
            mulTable[shortNum[i] - '0'][maxLength + 1] = '\0';
            for (int j = maxLength - 1; j >= 0; j--)
            {
                int temp = (shortNum[i] - '0') * (longNum[j] - '0');
                mulTable[shortNum[i] - '0'][j + 1] += (temp % 10);
                if (mulTable[shortNum[i] - '0'][j + 1] > '9')
                {
                    mulTable[shortNum[i] - '0'][j + 1] -= 10;
                    mulTable[shortNum[i] - '0'][j] = '1';
                }
                mulTable[shortNum[i] - '0'][j] += (temp / 10);
            }
        }
        char tempStr[strlen(mulTable[shortNum[i] - '0']) + 1];
        strcpy(tempStr, mulTable[shortNum[i] - '0']);
        if (mulFactor)
        {
            char zeroStr[mulFactor + 1];
            memset(zeroStr, '0', mulFactor);
            zeroStr[mulFactor] = '\0';
            strcat(tempStr, zeroStr);
        }
        result = addition(result.number, tempStr);
    }
    free(shortNum);
    free(longNum);
    for (int i = 0; i < 10; i++)
        free(mulTable[i]);
    free(mulTable);
    result.sign = resultSign;
    return result;
}

CryptNum CryptNum::operator-(const CryptNum& num)
{
    CryptNum result;
    if (num.sign == zero)
        result = *this;
    if (this->sign == zero && num.sign != zero)
    {
        result = num;
        result.sign = positive;
        if (num.sign == positive)
            result.sign = negative;
    }
    if (this->sign != zero && num.sign != zero)
    {
        if (this->sign != num.sign)
        {
            result = addition(this->number, num.number);
            result.sign = this->sign;
        }
        else
        {
            result = subtraction(this->number, num.number);
            if (equal(this->number, num.number))
                result.sign = zero;
            else if (lessThan(this->number, num.number))
            {
                result.sign = positive;
                if (this->sign == positive)
                    result.sign = negative;
            }
            else
                result.sign = this->sign;
        }
    }
    return result;
}

CryptNum CryptNum::operator/(const CryptNum& num)
{
    CryptNum result(0);
    int i = 0, j = 0;
    if (this->number[0] == '-')
        i++;
    if (num.number[0] == '-')
        j++;
    try
    {
        result = division(this->number + i, num.number + j);
    }
    catch (short unUsed)
    {
        cerr << "Runtime Exception Occurred : Division By Zero in operation ";
        cerr << "\"" << *this << " / " << num << "\"" << endl;
        cout << "Any further advancement may produce erroneous result\n";
        cout << "\tDo you want to continue (y/n) :    ";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
            return *this;
        else
            exit(0);
    }
    result.sign = negative;
    if (this->sign == num.sign)
        result.sign = positive;
    return result;
}

CryptNum CryptNum::operator%(const CryptNum& num)
{
    CryptNum result(0);
    int i = 0, j = 0;
    if (this->number[0] == '-')
        i++;
    if (num.number[0] == '-')
        j++;
    try
    {
        result = division(this->number + i, num.number + j);
    }
    catch (short unUsed)
    {
        cerr << "Runtime Exception Occurred : Division By Zero in operation ";
        cerr << "\"" << *this << " / " << num << "\"" << endl;
        cout << "Any further advancement may produce erroneous result\n";
        cout << "\tDo you want to continue (y/n) :    ";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
            return *this;
        else
            exit(0);
    }
    result.sign = negative;
    if (this->sign == num.sign)
        result.sign = positive;
    result = *this -(result * num);
    return result;
}

CryptNum CryptNum::operator^(CryptNum& num)
{
    if (num.sign == zero)
        return 1;
    else if (num.sign == negative)
        return 0;
    else
    {
        CryptNum result(*this), additionalProduct(1);
        SIGN resultSign = positive;
        if ((num.number[strlen(num.number) - 1] - '0') % 2)
            resultSign = this->sign;
        while (num != 1)
        {
            if (!((num.number[strlen(num.number) - 1] - '0') % 2))
            {
                result *= result;
                num /= 2;
            }
            else
            {
                --num;
                additionalProduct *= result;
            }
        }
        result *= additionalProduct;
        result.sign = resultSign;
        return result;
    }
}

ostream &
operator<<(ostream& out, const CryptNum& num)
{
    if (num.sign == CryptNum::negative)
        out << "-";
    out << num.number;
    return out;
}

void CryptNum::operator+=(const CryptNum& num)
{
    *this = *this + num;
}

void CryptNum::operator-=(const CryptNum& num)
{
    *this = *this - num;
}

void CryptNum::operator*=(const CryptNum& num)
{
    *this = *this * num;
}

void CryptNum::operator/=(const CryptNum& num)
{
    *this = *this / num;
}

void CryptNum::operator%=(const CryptNum& num)
{
    *this = *this % num;
}

CryptNum &
CryptNum::operator++()
{
    *this += 1;
    return *this;
}

CryptNum CryptNum::operator++(int unUsed)
{
    CryptNum temp(*this);
    *this += 1;
    return temp;
}

CryptNum &
CryptNum::operator--()
{
    *this -= 1;
    return *this;
}

CryptNum CryptNum::operator--(int unUsed)
{
    CryptNum temp(*this);
    *this -= 1;
    return temp;
}

bool CryptNum::operator==(const CryptNum& num)
{
    if (this->sign == num.sign && equal(this->number, num.number))
        return true;
    return false;
}

bool CryptNum::operator!=(const CryptNum& num)
{
    if (*this == num)
        return false;
    return true;
}

bool CryptNum::operator<(const CryptNum& num)
{
    if (this->sign == negative && (num.sign == positive || num.sign == zero))
        return true;
    else if (this->sign == zero && num.sign == positive)
        return true;
    else if (this->sign == negative && num.sign == negative &&
            !lessThan(this->number, num.number) && !equal(this->number, num.number))
        return true;
    else if (this->sign == positive && num.sign == positive &&
            lessThan(this->number, num.number))
        return true;
    else return false;
}

bool CryptNum::operator<=(const CryptNum& num)
{
    if (*this < num || *this == num)
        return true;
    return false;
}

bool CryptNum::operator>(const CryptNum& num)
{
    if (*this < num || *this == num)
        return false;
    return true;
}

bool CryptNum::operator>=(const CryptNum& num)
{
    if (*this < num)
        return false;
    return true;
}

CryptNum CryptNum::factorial(const CryptNum& num)
{
    CryptNum result("1");
    if (!strcmp(num.number, "0"))
        return result;
    CryptNum i("1");
    for (; i != num; i++)
        result *= i;
    return result*i;
}

CryptNum CryptNum::abs(const CryptNum& num)
{
    CryptNum abs(num);
    if (num.sign != zero)
        abs.sign = positive;
    return abs;
}

bool CryptNum::is_prime(const CryptNum& num)
{
    CryptNum testPrime(num);
    if (testPrime.sign == zero || testPrime.sign == negative)
        return false;
    CryptNum testNumber(1), zero(0);
    if (testPrime == testNumber)
        return false;
    testNumber++;
    if (testPrime == testNumber)
        return true;
    if (!((testPrime.number[strlen(testPrime.number) - 1] - '0') % 2))
        return false;
    testNumber++;
    if (testPrime == testNumber)
        return true;
    CryptNum testLimit(testPrime);
    do {
        if (testPrime % testNumber == zero)
            return false;
        testLimit = testPrime / testNumber;
        (testNumber++)++;
    } while (testLimit > testNumber);
    return true;
}

bool CryptNum::is_even(const CryptNum& num)
{
    int length = strlen(num.number);
    if (!length)
        return false;
    if (!((num.number[length - 1] - '0') % 2))
        return true;
    return false;
}


long CryptNum::sum_of_digit(const CryptNum& num)
{
    long sum = 0, i = 0;
    while (num.number[i] != '\0')
        sum += num.number[i++] - '0';
    return sum;
}

int CryptNum::number_of_digit(const CryptNum& num)
{
    return strlen(num.number);
}


CryptNum CryptNum::min(const CryptNum& num1, const CryptNum& num2)
{
    CryptNum n1(num1), n2(num2);
    if(n1 > n2)
        return n1;
    else
        return n2;
}

CryptNum CryptNum::GCD(const CryptNum& num1, const CryptNum& num2)
{
    CryptNum a(num1), b(num2), gcd;
    if(a == 0)
        return b;
    if(b == 0)
        return a;
    if(a == b)
        return b;
    while(b != 0)
    {
        gcd = b;
        b = a % b;
        a = gcd;
    }
    return gcd;
}

CryptNum CryptNum::phi(const CryptNum& num)
{
    CryptNum res(num);
    CryptNum i(num);
    CryptNum j(3);
    if(res == 1)
        return res;
    /* Check for divisibility by every prime number below the square root. */
    /* Start with 2. */
    if(i%2 == 0)
    {
        res -= res/2;
        do
            i /= 2;
        while(i%2 == 0);
    }
    /* Since this doesn't use a list of primes, check every odd number. Ideally, skip past composite numbers.*/
    for(;j*j <= i; j += 2)
    {
        if(i%j == 0)
        {
            res -= res/j;
            do
                i /=j;
            while(i%j == 0);
        }
    }
    /* If i>1, then it's the last factor at this point. */
    if (i>1) res-=res/i;
    /* Return the result. */
    return res;
}

CryptNum CryptNum::pow_mod(const CryptNum& a, const CryptNum& n, const CryptNum& m)
{
    CryptNum a1(a), n1(n), m1(m), counter;
    if (n.sign == zero)
        return 1;
    else if (n.sign == negative)
        return 0;

    else
    {
        CryptNum result(a1), addtionalProduct(1);
        while(n1 != 1)
        {
            if(!((n1.number[strlen(n1.number) - 1] - '0') % 2))
            {
                result *= result;
                result %= m1;
                n1 /= 2;
            }
            else
            {
                --n1;
                addtionalProduct *= result;
                addtionalProduct %= m1;
            }
        }
        result *= addtionalProduct;
        result %= m1;
        return result;
    }
}

CryptNum CryptNum::ax_b_mod_m(const CryptNum& a, const CryptNum& b, const CryptNum& m)
{
    //check
    CryptNum gc, chk, ph, zero(0), bb(b), aa(a);
    gc = GCD(a, m);
    chk = bb % gc;
    if(chk != zero)
        return 0;
    //check

    CryptNum x;

    ph = phi(m) - 1;
    x = pow_mod(a, ph, m);
    x *= b;
    x %= m;

    return x;
}

CryptNum CryptNum::inverse_a_mod_m(const CryptNum& a, const CryptNum& m)
{
    CryptNum aa(a), mm(m), x, lastx, y, lasty, quo, temp;
    x = 0;
    y = 1;
    lastx = 1;
    lasty = 0;
    while(mm != 0)
    {
        quo = aa / mm;
        temp = aa;
        aa = mm;
        mm = temp % mm;
        temp = x;
        x = lastx - quo * x;
        lastx = temp;
        temp = y;
        y = lasty - quo * y;
        lasty = temp;
    }

    if(lastx < 0)
        lastx += m;
    return lastx;
}

CryptNum CryptNum::order_a_mod_m(const CryptNum& a, const CryptNum& m)
{
    CryptNum ph = phi(m);
    CryptNum i, one(1), pow1, pow2, zer(0);
    i = 1;
    pow1 = 1;
    while(i <= ph)
    {
        pow1 *= a;
        pow1 %= m;
        if(pow1 == one)
            return i;
        else
            i++;
    }
    return zer;
}

bool CryptNum::is_primitive_root(const CryptNum& a, const CryptNum& m)
{
    CryptNum ord, ph;
    ord = order_a_mod_m(a, m);
    ph = phi(m);
    if(ord == ph)
        return true;
    else
        return false;
}

CryptNum CryptNum::index_g(const CryptNum& a, const CryptNum& p, const CryptNum& g)//g is a primitive root modulo p, a is the number who's index is required, p is prime
{
    CryptNum pow, k, limit(p), aa(a);
    limit -= 2;
    for(k = 0, pow = 1; k <= limit; k += 1)
    {
        if(aa == pow)
            return k;
        else
        {
            pow *= g;
            pow %= p;
        }
    }
    return 0;
}

int CryptNum::jacobi(const CryptNum& a, const CryptNum& n)
{
    CryptNum a1(a), n1(n), zer(0), chk1, chk2, tmp;
    int j = 1;
    while(a1 != zer)
    {
        while(!((a1.number[strlen(a1.number) - 1] - '0') % 2))
        {
            a1 /= 2;
            chk1 = n1 % 8;
            if(chk1 == 3 || chk1 == 5)
                j *= -1;
        }
        tmp = n1;
        n1 = a1;
        a1 = tmp;
        chk1 = a1 % 4;
        chk2 = n1 % 4;
        if(chk1 == 3 && chk2 == 3)
            j *= -1;
        a1 %= n1;
    }
    if(n1 == 1)
        return j;
    else
        return 0;
}

CryptNum CryptNum::rand_num()
{
    static CryptNum seed("5466168415649872"), multiplier("93827937751249284634"), adder("12532463321231215754"), modder("56324545243213434322342345557345431223567545346345233462432534");
    seed *= multiplier;
    seed += adder;
    seed %= modder;
    return seed;
}
