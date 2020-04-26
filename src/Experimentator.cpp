//
// Created by vultu on 4/20/2020.
//

#include "Experimentator.h"
#include <bits/unique_ptr.h>
#include <fstream>

void Experimentator::conduct_experiment(size_t max_problem_size, size_t n, bool is_precise)
{
    std::ofstream out_file = make_csv();
    std::unordered_map<std::string, std::unique_ptr<Multiplicator>> calculators;

    std::unique_ptr<Multiplicator> a = std::make_unique<SchoolMultiplicator>();
    std::unique_ptr<Multiplicator> b = std::make_unique<KaratsubaMultiplicator>();
    std::unique_ptr<Multiplicator> c = std::make_unique<CaesarMultiplicator>();

    std::unordered_map<std::string, double> running_times;

    Number r1;
    Number r2;
    size_t step;

    for (size_t i = 0; i <= max_problem_size; i += step)
    {
        if (is_precise)
            step = compute_precise_step(i);
        else
            step = compute_step(i);

        // different "time_seeds" as the second parameter in order to ensure (pseudo)randomness
        r1.generate_random(i + 1, 1);
        r2.generate_random(i + 1, 2);

        // setting up list of algorithms in order to systemize the approach
        calculators.insert(std::make_pair("school", std::move(a)));
        calculators.insert(std::make_pair("karatsuba", std::move(b)));
        calculators.insert(std::make_pair("caesar", std::move(c)));

        for (size_t j = 0; j < n; ++j)
        {
            for (const std::string &key : tested_algorithms)
            {
                if (running_times.find(key) != running_times.end())
                    running_times[key] +=
                            (measure_time(
                                    [&](const Number &, const Number &) { return calculators.at(key)->multiply(r1, r2); }, r1,
                                    r2)) /
                            n; // divide by n to get mean value in the end
                else
                    running_times[key] =
                            (measure_time(
                                    [&](const Number &, const Number &) { return calculators.at(key)->multiply(r1, r2); }, r1,
                                    r2)) /
                            n; // divide by n to get mean value in the end
            }
        }
        std::cout << i+1 << '\n'; // print to see that something is working
        write_line(out_file, i+1, running_times);
    }
    out_file.close();
    std::cout << "Done";
}

std::ofstream Experimentator::make_csv()
{
    std::ofstream file;
    file.open(output_filename);
    file << "Problem size" << ',';
    for (const std::string &key : tested_algorithms)
    {
        file << key << " (ms)" << ',';
    }
    file << '\n';

    return file;
}

void Experimentator::write_line(std::ofstream &file, size_t problem_size,
                                std::unordered_map<std::string, double> &running_times)
{
    file << problem_size;
    for (const std::string &key : tested_algorithms)
    {
        file << ',' << running_times.at(key);
    }

    file << "\n";
}

double Experimentator::measure_time(const std::function<Number(const Number &, const Number &)> &f, const Number &n1, const Number &n2)
{
    auto start = std::chrono::high_resolution_clock::now();
    f(n1, n2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration.count();
}

size_t Experimentator::compute_step(size_t problem_size)
{
    size_t cur_step = 1;
    while (problem_size >= 10)
    {
        problem_size /= 10;
        cur_step *= 10;
    }
    // iterate through each order of numbers in 10 steps
    return cur_step;
}

size_t Experimentator::compute_precise_step(size_t problem_size)
{
    if (problem_size < 20)
        return 1;
    else
    {
        if (problem_size > 10000)
            problem_size /= 10;

        size_t cur_step = 1;
        while (problem_size >= 10)
        {
            problem_size /= 10;
            cur_step *= 10;
        }
        // iterate through each order of numbers in 20 steps with some exceptions for precision
        return cur_step / 2;
    }
}