//
// Created by vultu on 4/20/2020.
//

#include <chrono>
#include <memory>
#include "MultiplicatorV.h"

Number SchoolMultiplicator::multiply(const Number &n1, const Number &n2) const {
    std::vector<short> result(n1.size() + n2.size()+1, 0);

    for (size_t i = 0; i < n1.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < n2.size(); ++j) {
            result[i + j] += (n2.digit(j) * n1.digit(i) + carry);
            carry = result[i + j] / 10;
            result[i + j] %= 10;
        }
        result[i + n2.size()] = carry;
    }
    Number product = Number(result);
    return product;
}

Number CaesarMultiplicator::multiply(const Number &n1, const Number &n2) const {
    std::cout<<n1.size()<<" "<<n2.size()<<std::endl;
    const size_t min_value = 1;
    int k = n1.size();
    if (n1.size() <= min_value || n2.size() <= min_value) // modify to optimize
    {
        std::unique_ptr<MultiplicatorV> fallback = std::make_unique<SchoolMultiplicator>();
        return fallback->multiply(n1, n2);
    }
    size_t m = std::min(n1.size(), n2.size()) / 2;
    std::cout<<n1.size()<<" "<<n2.size()<<" "<<m  <<std::endl;

    std::pair<Number, Number> a = n1.split(m);
    std::pair<Number, Number> b = n2.split(m);
    std::cout<<a.first.size()<<" "<<a.second.size();
    Number result;

    // A = A1 * t + A2
    // t = 10^m
    // AB = A1B1*t^2 + (A2B1 + A1B2)*t + A2B2 - 4 multiplications

    Number a1_a2 = a.first + a.second;
    Number b1_b2 = b.first + b.second;

    Number a1b1 = this->multiply(a.first, b.first);
    Number a2b2 = this->multiply(a.second, b.second);
    Number a1b2 = this->multiply(a.first, b.second);
    Number a2b1 = this->multiply(a.second, b.first);

    return a1b1.shift(2 * m) + (a2b1 + a1b2).shift(m) + a2b2;
}

Number KaratsubaMultiplicator::multiply(const Number &n1, const Number &n2) const {
    // O(n log2 (3)) = constant * n ^ log2 (3)
    const size_t min_value = 1;
    if (n1.size() <= min_value || n2.size() <= min_value) // modify to optimize
    {
        std::unique_ptr<MultiplicatorV> fallback = std::make_unique<SchoolMultiplicator>();
        return fallback->multiply(n1, n2);
    }

    size_t m = std::min(n1.size(), n2.size()) / 2;

    std::pair<Number, Number> a = n1.split(m);
    std::pair<Number, Number> b = n2.split(m);

    // A = A1 * t + A2
    // t = 10^m
    // AB = A1B1*t^2 + ((A1 + A2)(B1 + B2) - A1B1 - A2B2)*t + A2B2  - 3 multiplications
    Number a1_a2 = a.first + a.second;
    Number b1_b2 = b.first + b.second;
    Number a1b1 = this->multiply(a.first, b.first);
    Number a2b2 = this->multiply(a.second, b.second);
    Number a1_a2b1_b2 = this->multiply(a1_a2, b1_b2);
    return a1b1.shift(2 * m) + (a1_a2b1_b2 - (a2b2 + a1b1)).shift(m) + a2b2;
}

