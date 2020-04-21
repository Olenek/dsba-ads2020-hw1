//
// Created by vultu on 4/20/2020.
//

#ifndef EXTRAMULT_EXPERIMENTATOR_H
#define EXTRAMULT_EXPERIMENTATOR_H

#include <chrono>
#include <unordered_map>
#include <functional>
#include "MultiplicatorV.h"

class Experimentator {
private:
    std::string output_filename;
    std::unordered_map<size_t, std::string> order_of_computations;
public:
    Experimentator(){
        order_of_computations = {
                {0, "karatsuba"},
                {1, "caesar"},
                {2, "school"}};
        output_filename = "";
    }

    void setOutput(std::string s){output_filename = s;};

    void vec_to_csv(size_t, std::unordered_map<std::string, std::vector<double>>);

    void conduct_experiment(size_t, size_t, size_t);
};

double measure_time(const std::function<Number (const Number&, const Number&)>&, const Number &n1, const Number &n2);

#endif //EXTRAMULT_SOLUTIONS_EXPERIMENTATOR_H
