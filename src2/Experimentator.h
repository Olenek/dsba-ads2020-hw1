//
// Created by vultu on 4/20/2020.
//

#ifndef EXTRAMULT_EXPERIMENTATOR_H
#define EXTRAMULT_EXPERIMENTATOR_H

#include <chrono>
#include <unordered_map>
#include <functional>
#include <set>
#include <utility>
#include "MultiplicatorV.h"

class Experimentator {
private:
    std::string output_filename;
    std::set<std::string> tested_algorithms;
public:
    Experimentator(){
        tested_algorithms = {
                "karatsuba",
                "caesar",
                "school"};
        output_filename = "";
    }

    void setOutput(std::string s){output_filename = std::move(s);};

    void vec_to_csv(size_t, std::unordered_map<std::string, std::vector<double>>);

    void conduct_experiment(size_t, size_t, size_t);
};

double measure_time(const std::function<Number (const Number&, const Number&)>&, const Number &n1, const Number &n2);

#endif //EXTRAMULT_SOLUTIONS_EXPERIMENTATOR_H
