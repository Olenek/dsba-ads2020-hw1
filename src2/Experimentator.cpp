//
// Created by vultu on 4/20/2020.
//

#include <fstream>
#include <bits/unique_ptr.h>
#include "Experimentator.h"

void Experimentator::conduct_experiment(size_t k, size_t n, size_t step) {
    std::unordered_map<std::string, std::unique_ptr<MultiplicatorV>> calculators;

    std::unique_ptr<MultiplicatorV> a = std::make_unique<SchoolMultiplicator>();
    std::unique_ptr<MultiplicatorV> b = std::make_unique<KaratsubaMultiplicator>();
    std::unique_ptr<MultiplicatorV> c = std::make_unique<CaesarMultiplicator>();

    std::unordered_map<std::string, double> temp_running_times;
    std::unordered_map<std::string, std::vector<double>> vec_running_times;

    std::vector<double> v;
    for (const std::string &key: tested_algorithms) {
        vec_running_times.emplace(key, v);
    }

    Number r1;
    Number r2;
    for (size_t i = 0; i < k; i += step) {

        r1.generate_random(i + 1, 1); // different "time_seeds" in order to ensure (pseudo)randomness
        r2.generate_random(i + 1, 2);

        calculators.insert(std::make_pair("school", std::move(a)));
        calculators.insert(std::make_pair("karatsuba", std::move(b)));
        calculators.insert(std::make_pair("caesar", std::move(c)));

        for (size_t j = 0; j < n; ++j) {
            for (const std::string &key: tested_algorithms) {
                if (temp_running_times.find(key) != temp_running_times.end())
                    temp_running_times[key] += (measure_time([&](const Number&, const Number&){
                        return calculators.at(key)->multiply(r1, r2); }, r1, r2)) /
                                                       n; //divide by n to get mean value in the end
                else
                    temp_running_times[key] = (measure_time([&](const Number&, const Number&){
                        return calculators.at(key)->multiply(r1, r2); }, r1, r2)) /
                                                      n; //divide by n to get mean value in the end
            }
        }

        std::cout << i << '\n'; // print to see that something is working

        for (const std::string &key: tested_algorithms) {
            vec_running_times.at(key).push_back(
                    temp_running_times.at(key)); // adding times to the respective vectors
        }
    }

    vec_to_csv(step, vec_running_times);
    std::cout << "Done";
}

void Experimentator::vec_to_csv(size_t step, std::unordered_map<std::string, std::vector<double>> vec_running_times) {
    std::ofstream file;
    file.open(output_filename);
    file << ',';
    for (const std::string &key: tested_algorithms) {
        file << key << " (ms)" << ',';
    }
    file << '\n';

    for (size_t i = 0; i < vec_running_times.at(*(tested_algorithms.begin())).size(); i++) {
        file << i * step + 1 << ',';
        for (const std::string &key: tested_algorithms) {
            file << vec_running_times.at(key)[i] << ',';
        }
        file << '\n';

    }
    file.close();
}

double measure_time(const std::function<Number (const Number&, const Number&)>& f, const Number &n1, const Number &n2){
    auto start = std::chrono::high_resolution_clock::now();
    f(n1, n2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration.count();
}
