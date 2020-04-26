//
// Created by vultu on 4/20/2020.
//

#ifndef EXTRAMULT_MULTIPLICATORV_H
#define EXTRAMULT_MULTIPLICATORV_H

#include "Number.h"
#include <vector>

class Multiplicator
{
public:
    Multiplicator() = default;
    virtual Number multiply(const Number &, const Number &) const = 0;

    virtual ~Multiplicator() = default;
};

class KaratsubaMultiplicator : public Multiplicator
{
public:
    KaratsubaMultiplicator() = default;
    virtual Number multiply(const Number &, const Number &) const override;
};

class SchoolMultiplicator : public Multiplicator
{
public:
    SchoolMultiplicator() = default;
    virtual Number multiply(const Number &, const Number &) const override;
};

class CaesarMultiplicator : public Multiplicator
{
public:
    CaesarMultiplicator() = default;
    virtual Number multiply(const Number &, const Number &) const override;
};

#endif // CONTEST_SOLUTIONS_MULTIPLICATORV_H
