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

void print_double(double a) {
    std::cout << "Double: " << a << std::endl;
}

void print_int(int a) {
    std::cout << "Int: " << a << std::endl;
}

template <typename Iterator>
struct Grammar_validator : qi::grammar<Iterator, sp::ascii::space_type>
{
    Grammar_validator() : Grammar_validator::base_type(expression)
    {
        expression = left_side >> '=';// >> right_side;

        left_side = term >> *('+' >> term | '-' >> term);

        // right_side = term >> *('+' >> term | '-' >> term);

        // term = sp::double_[&print_double] >> '*' >> 'X' >> '^' >> sp::int_[&print_int];
        term = sp::double_ >> sp::lit('*') >> sp::lit('X') >> sp::lit('^') >> sp::int_;
    }
    qi::rule<Iterator, sp::ascii::space_type> term, factor, left_side, right_side;
    qi::rule<Iterator, sp::ascii::space_type> expression;
};

bool Parser::validate(const std::string &str) {
    bool res;
    auto start = str.begin();
    auto finish = str.end();
    Grammar_validator<std::string::iterator>    checker;

    // res = qi::parse(start, finish, checker);
    res = qi::phrase_parse(start, finish, checker, qi::space);

    std::cout << "Full match: " << (bool)(start == finish) << std::endl;
    std::cout << "Result: " << res << std::endl;

    return (res);
}