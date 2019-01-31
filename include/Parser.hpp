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

// OK tests
// "5 * X^0 + 4 * X^1 + X^2 = 4 * X^0"
// "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^2 = 3 * X^0"
// "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^2 = 3 "
// "8 * X^0 - 6 * X + 0 * X^2 - 5.6 * X^2 = 3 "
// "8 - 6 * X + 0 * X^2 - 5.6 * X^2 = 3 "
// "8 - 6 * X + X^2 - 5.6 * X^2 = 3 "

// FAIL tests
// "5 * X^0 + 4 * X^1 + X^2 = 4 X 2" 
// "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"

// true on success, and false on fail
bool twoArgs(const int &equal,
            const boost::optional<char> &sign,
            const boost::optional<double> &coef,
            const boost::optional<char> &power_sign,
            const boost::optional<unsigned int> &power)
{
    unsigned int local_power = 0;
    double local_coef = 1.0;
    int local_sign = 1;

    if (sign != boost::none)
        local_sign = (sign == '+') ? 1 : -1;
    
    if (coef != boost::none)
        local_coef = coef.get();

    if (power != boost::none)
        local_power = power.get();

    // Check power
    if (local_power > 2) {
        // TODO output
        return (false);
    }

    // Check if '^' exist, but power not. And wise versa.
    if ((power_sign != boost::none && power == boost::none) ||
        (power_sign == boost::none && power != boost::none)) {
        // TODO output
        return (false);
    }

    // TODO Add to sceleton class
    // sceleton_add(equal * sign * coef, power);
    std::cout << "TERM: COEF = " << equal * local_sign * local_coef
                << ", POWER = " << local_power << std::endl;

    return (true);
}

void constantFunc(const int &equal, const boost::optional<char> &sign, const double &val)
{
    std::cout << "CONSTANT: ";
    if (sign == boost::none)
        std::cout << "sign NONE";
    else
        std::cout << "sign " << sign;
    std::cout << ", val = " << val;
    std::cout << ", Equal = " << equal << std::endl;
}

struct D2parser : qi::grammar<std::string::iterator, spirit::locals<int>, qi::space_type>
{
    qi::rule<std::string::iterator, spirit::locals<int>, qi::space_type>    equitation;
    qi::rule<std::string::iterator, int(int), qi::space_type>    stmts, term, constant;
    qi::rule<std::string::iterator, boost::optional<char>(), qi::space_type>    sign;

    D2parser() : D2parser::base_type(equitation)
    {
        equitation = qi::eps[qi::_a = 1]
                    >> +(stmts(qi::_a))
                    >> qi::char_('=')[qi::_a = -1]
                    >> +(stmts(qi::_a));

        stmts = (term(qi::_r1) | constant(qi::_r1));

        term = (sign
                >> -qi::double_
                >> -qi::char_('*')
                >> qi::char_('X')
                >> -qi::char_('^')
                >> -qi::uint_)
        [qi::_pass = (phx::bind(&twoArgs, qi::_r1, qi::_1, qi::_2, qi::_5, qi::_6))];

        constant = (sign >> qi::double_)
                    [phx::bind(&constantFunc, qi::_r1, qi::_1, qi::_2)];

        sign = -(qi::char_('+') | qi::char_('-'));
    }
};

#endif // PARSER_HPP
