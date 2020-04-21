//
// Created by vultu on 4/20/2020.
//

#ifndef CONTEST_SOLUTIONS_MULTIPLICATORV_H
#define CONTEST_SOLUTIONS_MULTIPLICATORV_H


#include <vector>
#include "Number.h"

class MultiplicatorV {
public:
    MultiplicatorV()= default;
    virtual Number multiply(const Number&, const Number&) const = 0;

    virtual  ~MultiplicatorV() = default;
};

class KaratsubaMultiplicator : public MultiplicatorV{
public:
    KaratsubaMultiplicator()= default;
    virtual Number multiply(const Number&, const Number&) const override;

};

class SchoolMultiplicator : public MultiplicatorV{
public:
    SchoolMultiplicator()= default;
    virtual Number multiply(const Number&, const Number&) const override;

};

class CaesarMultiplicator : public MultiplicatorV{
public:
    CaesarMultiplicator()= default;
    virtual Number multiply(const Number&, const Number&) const override;
};


#endif //CONTEST_SOLUTIONS_MULTIPLICATORV_H
