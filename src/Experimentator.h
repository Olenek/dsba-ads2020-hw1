//
// Created by vultu on 4/20/2020.
//

#ifndef EXTRAMULT_EXPERIMENTATOR_H
#define EXTRAMULT_EXPERIMENTATOR_H

#include "Multiplicator.h"
#include <chrono>
#include <functional>
#include <set>
#include <unordered_map>
#include <utility>

class Experimentator
{
private:
    std::string output_filename;
    std::set<std::string> tested_algorithms;

public:
    Experimentator()
    {
        tested_algorithms = {"karatsuba", "caesar", "school"};
        output_filename = "";
    }

    void setOutput(std::string path_to_file)
    {
        output_filename = path_to_file;
    }

    void setAlgorithms(std::set<std::string> collection_of_algorithms)
    {
        tested_algorithms = collection_of_algorithms;
    }

    void write_line(std::ofstream &, size_t, std::unordered_map<std::string, double> &);

    std::ofstream make_csv();

    static size_t compute_step(size_t k);

    static size_t compute_precise_step(size_t k);

    void conduct_experiment(size_t, size_t, bool);

    static double measure_time(const std::function<Number(const Number &, const Number &)> &, const Number &n1, const Number &n2);

};


#endif // EXTRAMULT_SOLUTIONS_EXPERIMENTATOR_H
