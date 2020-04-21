//
// Created by vultu on 4/17/2020.
//
///NEW CODE ///

#ifndef EXTRAMULT_NUMBER_H
#define EXTRAMULT_NUMBER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

typedef std::vector<short> DigitVec;

class Number
{
private:
    DigitVec digits; // 123 = {3, 2, 1}
public:
    Number();

    Number(DigitVec);

    Number &operator+=(const Number&);

    Number operator+(const Number&) const;

    Number &operator-=(const Number&);

    Number operator-(const Number&) const;

    std::pair<Number, Number> split(size_t) const;

    size_t size() const;

    short digit(size_t) const;

    void generate_random(size_t, int);

    void print() const;

    Number shift(size_t) const;
};

Number one_digit_multiplication(const Number&, const Number&);

Number strip_zeroes(const Number&);

#endif // MULTIPLICATION_WORKSHOP_NUMBER_H
