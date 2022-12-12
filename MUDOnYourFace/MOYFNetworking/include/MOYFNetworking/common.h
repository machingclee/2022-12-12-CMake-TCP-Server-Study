#pragma once

#include "boost/asio.hpp"
#include <iostream>
#include <iterator>
#include <vector>


namespace MOYF {
    using tcp = boost::asio::ip::tcp;
}
enum class MyEnum {
    One,
    Two,
    Three
};

template<class F, class First, class... Rest>
void do_for(F f, First first, Rest... rest) {
    f(first);
    do_for(f, rest...);
}

template<class F>

void do_for(F f) {
    std::cout << "\n";
}

template<class... Args>
void print(Args... args) {
    do_for([](auto &arg) {
        std::cout << arg;
    }, args...);
}