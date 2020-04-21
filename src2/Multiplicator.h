//
// Created by vultu on 4/17/2020.
//

#ifndef CONTEST_SOLUTIONS_MULTIPLICATOR_H
#define CONTEST_SOLUTIONS_MULTIPLICATOR_H

#include "Number.h"
#include <chrono>
#include <fstream>
#include <functional>

class Multiplicator
{
private:
    std::vector<double> karatsuba_times;
    std::vector<double> school_times;
    std::vector<double> div_con_times;

public:
    Multiplicator();

    static Number school_mult(const Number&, const Number&);

    static Number div_con_mult(const Number &, const Number&);

    static Number karatsuba_mult(const Number&, const Number&);

    void vec_to_csv(const std::string&, int);

    static double measure_time(const std::function<Number(Number, Number)>&, const Number&, const Number&);

    void conduct_experiment(size_t, size_t, int, const std::string&);
};

#endif  // MULTIPLICATION_WORKSHOP_MULTIPLICATOR_H
