//
// Created by vultu on 4/17/2020.
//
/// NEW CODE ///

#ifndef EXTRAMULT_NUMBER_H
#define EXTRAMULT_NUMBER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

class Number
{
private:
    std::string digits; // 123 = {char(3), char(2), char(1)}
public:
    Number();

    Number(std::string &);

    Number(std::string &&);

    Number &operator+=(const Number &);

    Number operator+(const Number &) const;

    Number &operator-=(const Number &);

    Number operator-(const Number &) const;

    std::pair<Number, Number> split(size_t) const;

    size_t size() const;

    char at(size_t) const;

    void generate_random(size_t, int);

    void print() const;

    void shift(size_t);
};

#endif // MULTIPLICATION_WORKSHOP_NUMBER_H
