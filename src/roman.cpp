#include "../include/Roman.h"
extern bool is_reduced, normal;

/* Constructors */
RomanFraction::RomanFraction(string frac){
    size_t pos = frac.find('/');

    numerator = frac.substr(0, pos);
    denominator = frac.substr(pos + 1);

    if (numerator[0] == denominator[0] && denominator[0] == '-'){
        numerator = numerator.substr(1);
        denominator = denominator.substr(1);
    }
    else if (numerator[0] != denominator[0] && denominator[0] == '-'){
        denominator = denominator.substr(1);
        numerator = '-' + numerator;
    }
}
RomanFraction::RomanFraction(int n, int d){
    if (d < 0){
        d = -d, n = -n;
    }
    numerator = arabicToRoman(n);
    denominator = arabicToRoman(d);
}

/* Constructors */

/* Math functions */
int gcd (int a, int b) {
    if (a == 0 || b == 0) return 1;
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm (int a, int b) {
    return a / gcd (a, b) * b;
}
/* Math functions */

string RomanFraction::fraction(){
    if (numerator == "") return "NULL";
    else if (abs(romanToArabic(numerator)) > 3999 ||
        abs(romanToArabic(denominator)) > 3999) return "Sorry, but i can't return\nfraction";
    if (normal) {
        string a = to_string(romanToArabic(numerator)), b = to_string(romanToArabic(denominator));
        return a + "/" + b;
    } else {
        return numerator + "/"+ denominator;
    }

}

/* Convert functions */

int getRomanValue(char romanSymbol) {
    switch (romanSymbol) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        }
        return 0;
}

int RomanFraction::romanToArabic(string &roman){
    int arabic = 0, prevValue = 0;
    int currentValue = 0;
    for (int i = roman.length() - 1; i >= 0; i--) {
        if (roman[i] == '-') return -arabic;

        currentValue = getRomanValue(roman[i]);

        if (currentValue < prevValue) {
            arabic -= currentValue;
        } else {
            arabic += currentValue;
        }
        prevValue = currentValue;
    }
    return arabic;
}

string RomanFraction::arabicToRoman(int number) {
    string roman = "";
    int flag = 0, i = 0;
    if (number < 0){
        number *= (-1);
        flag = 1;
    }
    while (number > 0) {
        if (number >= arabicValues[i]) {
            number -= arabicValues[i];
            roman += romanValues[i];
        } else {
            i++;
        }
    }
    if (flag) return '-' + roman;
    return roman;
}
/* Convert functions */

/* Operators */
RomanFraction RomanFraction::operator +(RomanFraction& other){
    int _lcm = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));
    int n_ar = romanToArabic(numerator) * (_lcm / abs(romanToArabic(denominator)))
               + romanToArabic(other.numerator) * (_lcm / abs(romanToArabic(other.denominator)));

    int _gcd = abs(gcd(n_ar, _lcm));
    if (n_ar != 0 && is_reduced)
        return RomanFraction(n_ar / _gcd, _lcm / _gcd);
    return RomanFraction(n_ar, _lcm);
}

RomanFraction RomanFraction::operator -(RomanFraction& other){
    int _lcm = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));

    int num = romanToArabic(numerator) * (_lcm / romanToArabic(denominator)),
    other_num = romanToArabic(other.numerator) * (_lcm / romanToArabic(other.denominator));

    int _gcd = abs(gcd(num - other_num, _lcm));
    if (num - other_num != 0 && is_reduced)
        return RomanFraction((num - other_num) / _gcd, _lcm / _gcd);
    return RomanFraction((num - other_num), _lcm);
}

RomanFraction RomanFraction::operator *(RomanFraction& other){
    int n = romanToArabic(numerator) * romanToArabic(other.numerator),
        d = romanToArabic(other.denominator) * romanToArabic(denominator);

    int _gcd = gcd(abs(n), abs(d));
    if (n != 0 && is_reduced)
        return RomanFraction(n / _gcd, d / _gcd);
    return RomanFraction(n, d);
}

RomanFraction RomanFraction::operator /(RomanFraction& other){
    int n = romanToArabic(numerator) * romanToArabic(other.denominator),
        d = romanToArabic(other.numerator) * romanToArabic(denominator);

    int _gcd = gcd(abs(n), abs(d));
    if (n != 0 && is_reduced)
        return RomanFraction(n / _gcd, d / _gcd);
    return RomanFraction(n, d);
}

bool RomanFraction::operator >(RomanFraction& other){
    int _lcm = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));
    return romanToArabic(numerator) * (_lcm / abs(romanToArabic(denominator))) >
           romanToArabic(other.numerator) * (_lcm / abs(romanToArabic(other.denominator)));
}

bool RomanFraction::operator <(RomanFraction& other){
    int _lcm = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));
    return romanToArabic(numerator) * (_lcm / abs(romanToArabic(denominator))) <
           romanToArabic(other.numerator) * (_lcm / abs(romanToArabic(other.denominator)));
}
/* Operators */
