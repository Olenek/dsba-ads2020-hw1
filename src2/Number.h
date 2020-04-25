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


class Number
{
private:
    std::vector<short> digits; // 123 = {3, 2, 1}
public:
    Number();

    Number(size_t);

    Number(std::vector<short>);

    Number &operator+=(const Number&);

    Number operator+(const Number&) const;

    Number &operator-=(const Number&);

    Number operator-(const Number&) const;

    std::pair<Number, Number> split(size_t) const;

    size_t size() const;

    short at(size_t) const;

    void generate_random(size_t, int);

    void print() const;

    void shift(size_t);

};


#endif // MULTIPLICATION_WORKSHOP_NUMBER_H
