#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

using ip_t = std::tuple<int, int, int, int>;

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_t parse_ip(const std::string &str)
{
    auto parts = split(str, '.');
    return std::make_tuple(std::stoi(parts.at(0)), std::stoi(parts.at(1)),
                           std::stoi(parts.at(2)), std::stoi(parts.at(3)));
}

void reverse_sort(std::vector<ip_t> &ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), [](const ip_t &a, const ip_t &b) { return a > b; });
}

template<typename Pred>
std::vector<ip_t> filter_if(const std::vector<ip_t> &ip_pool, Pred pred)
{
    std::decay_t<decltype(ip_pool)> result;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), pred);
    return result;
}

std::vector<ip_t> filter(const std::vector<ip_t> &ip_pool, int first)
{
    return filter_if(ip_pool, [first](const ip_t &ip) { return std::get<0>(ip) == first; });
}

std::vector<ip_t> filter(const std::vector<ip_t> &ip_pool, int first, int second)
{
    return filter_if(ip_pool, [first, second](const ip_t &ip) {
        return std::tie(std::get<0>(ip), std::get<1>(ip)) == std::tie(first, second);
    });
}

std::vector<ip_t> filter_any(const std::vector<ip_t> &ip_pool, int value)
{
    return filter_if(ip_pool, [value](const ip_t &ip) {
        int a, b, c, d;
        std::tie(a, b, c, d) = ip;
        return a == value || b == value || c == value || d == value;
    });
}

std::string to_string(const ip_t &ip)
{
    return std::to_string(std::get<0>(ip)) + "." + std::to_string(std::get<1>(ip)) + "." +
           std::to_string(std::get<2>(ip)) + "." + std::to_string(std::get<3>(ip));
}

void print(const std::vector<ip_t> &ip_pool)
{
    for(const auto &ip : ip_pool)
    {
        std::cout << to_string(ip) << std::endl;
    }
}

#ifndef UNIT_TEST
int main()
{
    try
    {
        std::vector<ip_t> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(parse_ip(v.at(0)));
        }

        reverse_sort(ip_pool);

        print(ip_pool);
        print(filter(ip_pool, 1));
        print(filter(ip_pool, 46, 70));
        print(filter_any(ip_pool, 46));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#endif
