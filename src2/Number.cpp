//
// Created by vultu on 4/17/2020.
//

#include "Number.h"

Number::Number() = default;



Number::Number(std::string& s) : digits(std::move(s)){};

Number::Number(std::string&& s) : digits(std::move(s)){};



Number& Number::operator+=(const Number &other)
{
    if (size() < other.size())
    {
        digits.reserve(other.size());
    }

    short carry = 0;
    for (size_t i = 0; i < other.size(); ++i)
    {
        short sum = digits[i] + other.digits[i] + carry;
        short new_digit = sum % 10;
        digits[i] = new_digit;
        carry = sum / 10;
    }

    size_t digit_index = other.size();
    while (carry != 0)
    {
        if (digit_index < size())
        {
            short sum = digits[digit_index] + carry;
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

Number& Number::operator-=(const Number &other)
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
        short diff = short(digits[i]) - short(i < other.size() ? other.digits[i] : 0) - borrow;
        if (diff < 0)
        {
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        digits[i] = char(diff + 10 * borrow);
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
    digits.insert(digits.begin(), t, char(0));
}

size_t Number::size() const
{
    return digits.size();
}

char Number::at(size_t index) const // return digits in reversed order
{
    return digits[index];
}

std::pair<Number, Number> Number::split(size_t cut_size) const
{ // split number into two numbers of size n-cut, cut
    Number res1;
    Number res2;

    res1.digits.resize(cut_size, char(0));
    res2.digits.resize(size() - cut_size, char(0));
    std::copy(digits.begin(), digits.begin() + cut_size, res1.digits.begin());
    std::copy(digits.begin() + cut_size, digits.end(), res2.digits.begin());

    return std::make_pair(std::move(res2), std::move(res1));
}

void Number::generate_random(size_t k, int time_seed)
{
    std::string randStr;
    std::srand(std::time(0) + time_seed);
    randStr.reserve(k);
    for (size_t i = 0; i < (k - 1); i++)
    {
        randStr.push_back(char(rand() % 10));
    }
    randStr.push_back(char((rand() % 9) + 1));
    Number ans = Number(std::move(randStr)); //possible trash
    *this = ans;
}

void Number::print() const
{
    // print ignoring leading zeroes
    auto it = digits.rbegin();
    while (it != digits.rend() && *it == 0)
    {
        ++it;
    }
    bool any_digit = false;
    while (it != digits.rend())
    {
        std::cout << char(*it + char(48));
        ++it;
        any_digit = true;
    }
    if (!any_digit)
    {
        std::cout << "0";
    }
    std::cout << "\n";
}

