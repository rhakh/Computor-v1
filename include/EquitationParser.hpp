#ifndef EQUITATION_PARSER_HPP
#define EQUITATION_PARSER_HPP

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

#include "Equitation.hpp"

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
// "X^2 + 3X - 4 = 0"
// "X^2 + 3X - 4 =  X ^ 2 + 3 * X - 4"

// FAIL tests
// "5 * X^0 + 4 * X^1 + X^2 = 4 X 2" 
// "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"

// true on success, and false on fail
bool twoArgs(const int &equal,
            const boost::optional<char> &sign,
            const boost::optional<double> &mult,
            const boost::optional<char> &power_sign,
            const boost::optional<unsigned int> &power)
{
    unsigned int local_power = 1;
    double local_mult = 1.0;
    int local_sign = 1;

    if (sign != boost::none)
        local_sign = (sign == '+') ? 1 : -1;
    
    if (mult != boost::none)
        local_mult = mult.get();

    if (power != boost::none)
        local_power = power.get();

    // Check power
    if (local_power > 2)
    {
        // TODO output
        return (false);
    }

    // Check if '^' exist, but power not. And wise versa.
    if ((power_sign != boost::none && power == boost::none) ||
        (power_sign == boost::none && power != boost::none))
    {
        // TODO output
        return (false);
    }

    Equitation::addTerm(equal * local_sign * local_mult, local_power);

    return (true);
}

void constantFunc(const int &equal, const boost::optional<char> &sign, const double &val)
{
    int local_sign = 1;

    if (sign != boost::none)
        local_sign = (sign == '+') ? 1 : -1;

    Equitation::addTerm(equal * local_sign * val, 0);
}

struct EquitationParser : qi::grammar<std::string::iterator, spirit::locals<int>, qi::space_type>
{
    qi::rule<std::string::iterator, spirit::locals<int>, qi::space_type>    equitation;
    qi::rule<std::string::iterator, int(int), qi::space_type>    stmts, term, constant;
    qi::rule<std::string::iterator, boost::optional<char>(), qi::space_type>    sign;

    EquitationParser() : EquitationParser::base_type(equitation)
    {
        using namespace boost::spirit::qi;

        equitation = eps[_a = 1]
                    >> +(stmts(_a))
                    >> char_('=')[_a = -1]
                    >> +(stmts(_a));

        stmts = (term(_r1) | constant(_r1));

        term = (sign
                >> -double_
                >> -char_('*')
                >> char_('X')
                >> -char_('^')
                >> -uint_)
        [_pass = (phx::bind(&twoArgs, _r1, _1, _2, _5, _6))];

        constant = (sign >> double_)
                    [phx::bind(&constantFunc, _r1, _1, _2)];

        sign = -(char_('+') | char_('-'));
    }
};

#endif // EQUITATION_PARSER_HPP
