//
// Created by vultu on 4/20/2020.
//

#include <fstream>
#include <bits/unique_ptr.h>
#include "Experimentator.h"

void Experimentator::conduct_experiment(size_t k, size_t n) {
    std::ofstream out_file = make_csv();
    std::unordered_map<std::string, std::unique_ptr<MultiplicatorV>> calculators;

    std::unique_ptr<MultiplicatorV> a = std::make_unique<SchoolMultiplicator>();
    std::unique_ptr<MultiplicatorV> b = std::make_unique<KaratsubaMultiplicator>();
    std::unique_ptr<MultiplicatorV> c = std::make_unique<CaesarMultiplicator>();

    std::unordered_map<std::string, double> running_times;


    Number r1;
    Number r2;
    size_t step = 1;

    for (size_t i = 0; i < k; i += step) {
        step = compute_step(i);

        r1.generate_random(i + 1, 1); // different "time_seeds" in order to ensure (pseudo)randomness
        r2.generate_random(i + 1, 2);

        calculators.insert(std::make_pair("school", std::move(a))); // done in order to systemize everything
        calculators.insert(std::make_pair("karatsuba", std::move(b)));
        calculators.insert(std::make_pair("caesar", std::move(c)));

        for (size_t j = 0; j < n; ++j) {
            for (const std::string &key: tested_algorithms) {
                if (running_times.find(key) != running_times.end())
                    running_times[key] += (measure_time([&](const Number&, const Number&){
                        return calculators.at(key)->multiply(r1, r2); }, r1, r2)) /
                                                       n; //divide by n to get mean value in the end
                else
                    running_times[key] = (measure_time([&](const Number&, const Number&){
                        return calculators.at(key)->multiply(r1, r2); }, r1, r2)) /
                                                      n; //divide by n to get mean value in the end
            }
        }
        std::cout << i << '\n'; // print to see that something is working
        write_line(out_file, i, running_times);
    }
    out_file.close();
    std::cout << "Done";
}


std::ofstream Experimentator::make_csv() {
    std::ofstream file;
    file.open(output_filename);
    file << ',';
    for (const std::string &key: tested_algorithms) {
        file << key << " (ms)" << ',';
    }
    file << '\n';
    return file;
}


void Experimentator::write_line(std::ofstream& file, size_t k, std::unordered_map<std::string, double>& running_times){
    file << k + 1;
    for (const std::string &key: tested_algorithms) {
        file << ',' << running_times.at(key);
    }
    file <<"\n";
}


double measure_time(const std::function<Number (const Number&, const Number&)>& f, const Number &n1, const Number &n2){
    auto start = std::chrono::high_resolution_clock::now();
    f(n1, n2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration.count();
}

size_t Experimentator::compute_step(size_t k){
    size_t cur_step = 1;
    if(k > 400)
        cur_step = 5;

    while(k > 10){
        k/=100;
        cur_step*=10;
    }
    return cur_step;
}