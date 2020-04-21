//
// Created by vultu on 4/17/2020.
//

#include "Number.h"

Number::Number() = default;

Number::Number(std::vector<short> v) : digits(std::move(v)){};


Number &Number::operator+=(const Number &other)
{
    if (size() < other.size())
    {
        digits.resize(other.size(), 0);
    }

    short carry = 0;
    for (size_t i = 0; i < other.size(); ++i)
    {
        short sum = digit(i) + other.digit(i) + carry;
        short new_digit = sum % 10;
        digits[i] = new_digit;
        carry = sum / 10;
    }

    size_t digit_index = other.size();
    while (carry != 0)
    {
        if (digit_index < size())
        {
            short sum = digit(digit_index) + carry;
            short new_digit = sum % 10;
            digits[digit_index] = new_digit;
            carry = sum / 10;
        }
        else
        {
            digits.push_back(carry);
            break;
        }
        digit_index++;
    }

    return *this;
}

Number Number::operator+(const Number &other) const
{
    Number ans = *this;
    ans += other;
    return ans;
}

Number &Number::operator-=(const Number &other)
{
    Number initial_number = *this;
    if (size() < other.size())
    {
        digits.resize(other.size(), 0);
    }
    short borrow = 0;

    // Works only for positive-resulting numbers

    for (size_t i = 0; i != size(); ++i)
    {
        short diff = digits[i] - (i < other.size() ? other.digits[i] : 0) - borrow;
        if (diff < 0)
        {
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        digits[i] = diff + 10 * borrow;
    }
    return *this;
}

Number Number::operator-(const Number &other) const
{
    Number ans = *this;
    ans -= other;
    return ans;
}

void Number::shift(size_t t)
{
    digits.insert(digits.begin(), t, 0);
}

size_t Number::size() const
{
    return digits.size();
}

short Number::digit(size_t index) const // return digits in reversed order
{
    return digits[index];
}

std::pair<Number, Number> Number::split(size_t cut_size) const
{ // split number into two numbers of size n-cut, cut
    Number res1;
    Number res2;

    res1.digits.resize(cut_size, 0);
    res2.digits.resize(size() - cut_size, 0);
    std::copy(digits.begin(), digits.begin() + cut_size, res1.digits.begin());
    std::copy(digits.begin() + cut_size, digits.end(), res2.digits.begin());

    return std::make_pair(res2, res1);
}

void Number::generate_random(size_t k, int time_seed)
{
    DigitVec randVec;
    std::srand(std::time(0) + time_seed);
    randVec.reserve(k);
    for (size_t i = 0; i < (k - 1); i++)
    {
        randVec.push_back(rand() % 10);
    }
    randVec.push_back((rand() % 9) + 1);
    Number ans = Number(randVec);
    *this = ans;
}

void Number::print() const
{
    // print ignoring leading zeroes
    Number tmp = strip_zeroes(*this);

    for(auto it = tmp.digits.rbegin(); it!=tmp.digits.rend(); --it){
        std::cout<<*it;
    }
    std::cout<<std::endl;
}

Number strip_zeroes(const Number& n1){ //returns copy without leading zeroes

    DigitVec res_vec;
    size_t i = 0;
    while(n1.digit(i) == 0 && i!=n1.size()){
        ++i;
    }
    bool any_digit = false;
    while (i!=n1.size())
    {
        res_vec.push_back(n1.digit(i));
        ++i;
        any_digit = true;
    }
    if (!any_digit)
    {
        res_vec.push_back(0);
    }
    Number res = Number(res_vec);

    return res;
}
