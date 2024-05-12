#include "Roman.h"

/* Math functions */
int gcd (int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm (int a, int b) {
    return a / gcd (a, b) * b;
}

ostream& operator<<(ostream& os, RomanFraction& fraction){
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}

string RomanFraction::fraction(){
    if (numerator == "") return "NULL";
    return numerator + "/" + denominator;
}

int RomanFraction::romanToArabic(string &roman){
    int arabic = 0, i = 0;
    if (roman[0] == '-') i = 1;
    for (; i < roman.size(); i++) {
        if (i + 1 < roman.size() && romanToArabicMap[roman[i]] < romanToArabicMap[roman[i + 1]]) {
            arabic -= romanToArabicMap[roman[i]];
        } else {
            arabic += romanToArabicMap[roman[i]];
        }
    }
    if (roman[0] == '-') return -arabic;
    return arabic;
}

string RomanFraction::arabicToRoman(int number) {
    string result = "";
    int flag = 0;
    if (number < 0){
        number*=(-1);
        flag = 1;
    }
    for (auto it = arabicToRomanMap.rbegin(); it != arabicToRomanMap.rend(); ++it) {
        while (number >= it->first) {
            result += it->second;
            number -= it->first;
        }
    }
    if (flag) return '-' + result;
    return result;
}

RomanFraction RomanFraction::operator +(RomanFraction& other){
    int um = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));
    int n_ar = romanToArabic(numerator) * (um / abs(romanToArabic(denominator))),
        o_ar = romanToArabic(other.numerator) * (um / abs(romanToArabic(other.denominator)));
    int _gcd = gcd(n_ar + o_ar, um);
    if (n_ar + o_ar != 0) return RomanFraction((n_ar + o_ar) / _gcd, um / _gcd);

    return RomanFraction(n_ar + o_ar, um);
}

RomanFraction RomanFraction::operator -(RomanFraction& other){
    int um = lcm(abs(romanToArabic(denominator)), abs(romanToArabic(other.denominator)));
    int n_ar = romanToArabic(numerator) * (um / abs(romanToArabic(denominator))),
        o_ar = romanToArabic(other.numerator) * (um / abs(romanToArabic(other.denominator)));
    int _gcd = gcd(n_ar - o_ar, um);
    if (n_ar - o_ar != 0) return RomanFraction((n_ar - o_ar) / _gcd, um / _gcd);

    return RomanFraction((n_ar - o_ar), um);
}

RomanFraction RomanFraction::operator *(RomanFraction& other){
    int n_ar = romanToArabic(numerator) * abs(romanToArabic(other.numerator)),
        o_ar = romanToArabic(other.denominator) * abs(romanToArabic(denominator));
    int _gcd = gcd(n_ar, o_ar);
    if (n_ar != 0) return RomanFraction(n_ar / _gcd, o_ar / _gcd);

    return RomanFraction(n_ar, o_ar);
}

RomanFraction RomanFraction::operator /(RomanFraction& other){
    int n_ar = romanToArabic(numerator) * abs(romanToArabic(other.denominator)),
        o_ar = romanToArabic(other.numerator) * abs(romanToArabic(denominator));
    int _gcd = gcd(n_ar, o_ar);
    if (n_ar != 0) return RomanFraction(n_ar / _gcd, o_ar / _gcd);

    return RomanFraction(n_ar, o_ar);
}
