#include "Parser.hpp"
#include <vector>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace sp = boost::spirit;
namespace ph = boost::phoenix;

bool Parser::parse(const std::string &str) {
    bool res;
    std::vector<int> v;
    auto start = str.begin();
    auto finish = str.end();

    res = qi::phrase_parse(start, finish,
            (
                // qi::int_[ph::push_back(ph::ref(v), qi::_1)] >> *(qi::int_[ph::push_back(ph::ref(v), qi::_1)])
                qi::int_[ph::push_back(ph::ref(v), qi::_1)] % ','
            ),
            sp::ascii::space);

    std::cout << "Full match: " << (bool)(start == finish) << std::endl;
    std::cout << "Result: " << res << std::endl;

    if (res) {
        for(auto a : v)
            std::cout << a << ", ";
        std::cout << std::endl;
    }
    return (res);
}