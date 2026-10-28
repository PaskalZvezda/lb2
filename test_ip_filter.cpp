#include "ip_filter.cpp"

#include <gtest/gtest.h>

TEST(ip_filter, reverse_sort)
{
    std::vector<ip_t> ip_pool = {parse_ip("1.1.1.1"), parse_ip("1.10.1.1"), parse_ip("1.2.1.1")};
    reverse_sort(ip_pool);
    std::vector<ip_t> expected = {parse_ip("1.10.1.1"), parse_ip("1.2.1.1"), parse_ip("1.1.1.1")};
    EXPECT_EQ(ip_pool, expected);
}

TEST(ip_filter, filter)
{
    std::vector<ip_t> ip_pool = {parse_ip("46.70.225.39"), parse_ip("46.71.1.1"), parse_ip("1.2.3.4")};
    EXPECT_EQ(filter(ip_pool, 1), std::vector<ip_t>({parse_ip("1.2.3.4")}));
    EXPECT_EQ(filter(ip_pool, 46, 70), std::vector<ip_t>({parse_ip("46.70.225.39")}));
}

TEST(ip_filter, filter_any)
{
    std::vector<ip_t> ip_pool = {parse_ip("186.204.34.46"), parse_ip("1.2.3.4"), parse_ip("39.46.86.85")};
    std::vector<ip_t> expected = {parse_ip("186.204.34.46"), parse_ip("39.46.86.85")};
    EXPECT_EQ(filter_any(ip_pool, 46), expected);
}
