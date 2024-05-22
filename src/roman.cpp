#include "../include/Roman.h"
extern bool is_reduced, normal;

/* Constructors */
RomanFraction::RomanFraction(int n, int d){
    if (d < 0){
        d = -d, n = -n;
    }
    numerator = arabicToRoman(n);
    denominator = arabicToRoman(d);
}

RomanFraction::RomanFraction(string roman_num, string roman_denom){
    numerator = roman_num;
    denominator = roman_denom;
    if (numerator[0] == denominator[0] && denominator[0] == '-'){
        numerator = numerator.substr(1);
        denominator = denominator.substr(1);
    }
    else if (numerator[0] != denominator[0] && denominator[0] == '-'){
        denominator = denominator.substr(1);
        numerator = '-' + numerator;
    }
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
        string sep(max(a.size(), b.size()), '-');
        return a + "\n" + sep + "\n" + b;
    } else {
        string sep(max(numerator.size(), denominator.size()), '-');
        return numerator + "\n" + sep + "\n"+ denominator;
    }

}

/* Convert functions */
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
        number *= (-1);
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
/* Operators */
