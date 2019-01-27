#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <iostream>
#include <vector>
// #include <boost/spirit.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/optional/optional_io.hpp>


namespace qi     = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phx    = boost::phoenix;

//  "5 * X^0 + 4 * X^1 + X^2 = 4 * X^0"

void twoArgs(const boost::optional<char> &sign, const boost::optional<unsigned int> &coef, const boost::optional<unsigned int> &power) {
    std::cout << "TERM: ";
    if (sign == boost::none)
        std::cout << "sign NONE";
    else
        std::cout << "sign " << sign;
    
    if (coef == boost::none)
        std::cout << ", coef = NONE";
    else
        std::cout << ", coef = " << coef;

    if (power == boost::none)
        std::cout << ", power = NONE";
    else
        std::cout << ", power = " << power;
    std::cout << std::endl;
}

void constantFunc(const boost::optional<char> &sign, const unsigned int &val) {
    std::cout << "CONSTANT: ";
    if (sign == boost::none)
        std::cout << "sign NONE";
    else
        std::cout << "sign " << sign;
    std::cout << ", val = " << val << std::endl;
}

struct D2parser : qi::grammar<std::string::iterator, qi::space_type>
{
    qi::rule<std::string::iterator, qi::space_type>   equitation, stmts, term, constant;

    D2parser() : D2parser::base_type(equitation)
    {
        // bool equal = false;

        equitation = +(stmts) >> qi::char_('=') >> +(stmts);

        stmts = (term | constant);

        term = (-(qi::char_('+') | qi::char_('-'))
                >> -qi::uint_
                >> -qi::char_('*')
                >> qi::char_('X')
                >> -qi::char_('^')
                >> -qi::uint_)[phx::bind(&twoArgs, qi::_1, qi::_2, qi::_6)];

        constant = (-(qi::char_('+') | qi::char_('-')) >> qi::uint_)[phx::bind(&constantFunc, qi::_1, qi::_2)];
    }
};

#endif // PARSER_HPP
