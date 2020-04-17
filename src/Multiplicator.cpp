//
// Created by vultu on 4/17/2020.
//
#include "Multiplicator.h"

Multiplicator::Multiplicator() = default;

Number Multiplicator::school_mult(const Number &n1, const Number &n2)
{
    std::vector<short> d(n1.size() + n2.size(), 0);

    for (int i = 0; i < n1.size(); ++i)
    {
        int carry = 0;
        for (int j = 0; j < n2.size(); ++j)
        {
            d[i + j] += (n2.digit(j) * n1.digit(i) + carry);
            carry = d[i + j] / 10;
            d[i + j] %= 10;
        }
        d[i + n2.size()] = carry;
    }
    Number result = Number(d);
    return result;
}

Number Multiplicator::div_con_mult(const Number &n1, const Number &n2)
{
    const size_t min_value = 1;
    if (n1.size() <= min_value || n2.size() <= min_value) // modify to optimize
    {
        return school_mult(n1, n2);
    }
    size_t m = std::max(n1.size(), n2.size()) / 2;

    std::pair<Number, Number> a = n1.split(m);
    std::pair<Number, Number> b = n2.split(m);

    Number result;

    // A = A1 * t + A2
    // t = 10^m
    // AB = A1B1*t^2 + (A2B1 + A1B2)*t + A2B2 - 4 multiplications

    Number a1_a2 = a.first + a.second;
    Number b1_b2 = b.first + b.second;

    Number a1b1 = div_con_mult(a.first, b.first);
    Number a2b2 = div_con_mult(a.second, b.second);
    Number a1b2 = div_con_mult(a.first, b.second);
    Number a2b1 = div_con_mult(a.second, b.first);

    return a1b1.shift(2 * m) + (a2b1 + a1b2).shift(m) + a2b2;
}

Number Multiplicator::karatsuba_mult(const Number &n1, const Number &n2)
{
    // O(n log2 (3)) = constant * n ^ log2 (3)
    const size_t min_value = 1;
    if (n1.size() <= min_value || n2.size() <= min_value) // modify to optimize
    {
        return school_mult(n1, n2);
    }

    size_t m = std::max(n1.size(), n2.size()) / 2;

    std::pair<Number, Number> a = n1.split(m);
    std::pair<Number, Number> b = n2.split(m);

    // A = A1 * t + A2
    // t = 10^m
    // AB = A1B1*t^2 + ((A1 + A2)(B1 + B2) - A1B1 - A2B2)*t + A2B2  - 3 multiplications
    Number a1_a2 = a.first + a.second;
    Number b1_b2 = b.first + b.second;
    Number a1b1 = karatsuba_mult(a.first, b.first);
    Number a2b2 = karatsuba_mult(a.second, b.second);
    Number a1_a2b1_b2 = karatsuba_mult(a1_a2, b1_b2);
    return a1b1.shift(2 * m) + (a1_a2b1_b2 - (a2b2 + a1b1)).shift(m) + a2b2;
}

void Multiplicator::vec_to_csv(const std::string &filename, int step)
{
    std::ofstream file;
    file.open(filename);
    file << ',' << "karatsuba(ms)" << ',' << "school-grade(ms)" << ',' << "div_con(ms)" << ',' << '\n';
    for (size_t i = 0; i < karatsuba_times.size(); i++)
    {
        file << i * step + 1 << ',' << karatsuba_times[i] << ',' << school_times[i] << ',' << div_con_times[i] << ','
             << '\n';
    }
    file.close();
}

double Multiplicator::measure_time(std::function<Number(Number, Number)> f, const Number &n1, const Number &n2)
{
    auto start = std::chrono::high_resolution_clock::now();
    f(n1, n2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration.count();
}

void Multiplicator::conduct_experiment(size_t k, size_t n, int step, const std::string& filename)
{
    karatsuba_times.clear();
    school_times.clear();
    div_con_times.clear();
    double karatsuba_time = 0;
    double school_time = 0;
    double div_con_time = 0;

    Number r1;
    Number r2;
    for (size_t i = 0; i < k; i += step)
    {
        karatsuba_time = 0; // null times
        school_time = 0;
        div_con_time = 0;
        r1.generate_random(i + 1, 1); // different "time_seeds" in order to ensure (pseudo)randomness
        r2.generate_random(i + 1, 2);

        for (size_t j = 0; j < n; j++)
        {
            karatsuba_time += measure_time(karatsuba_mult, r1, r2);

            school_time += measure_time(school_mult, r1, r2);

            div_con_time += measure_time(div_con_mult, r1, r2);
        }
        std::cout << i << '\n'; // print to see that something is working
        karatsuba_time /= n;    // mean values
        school_time /= n;
        div_con_time /= n;

        karatsuba_times.push_back(karatsuba_time); // adding times to the respective vectors
        school_times.push_back(school_time);
        div_con_times.push_back(div_con_time);
    }

    vec_to_csv(filename, step);
    std::cout << "Done";
}
