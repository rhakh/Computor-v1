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


namespace qi     = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phx    = boost::phoenix;

//  "5 * X^0 + 4 * X^1 + X^2 = 4 * X^0"

void twoArgs(unsigned int const &val, unsigned int const &val2) {
    std::cout << "coef = " << val << ", power = " << val2 << std::endl;
}

template <typename Iterator>
struct D2parser : qi::grammar<Iterator, int(), qi::space_type>
{
    qi::rule<Iterator, int(), qi::space_type>   expr, term, factor;
    double  a = 0, b = 0, c = 0;
    int     errorCode = 0;

    void    addCoef(int coef, int powerOfX) {
        switch (powerOfX) {
            case 0:
                a += coef;
                break;
            case 1:
                b += coef;
                break;
            case 2:
                c += coef;
                break;
            default:
                // TODO: Add error codes
                errorCode = 1;
                break;
        }
    }

    D2parser() : D2parser::base_type(expr)
    {
        expr = 
            term                    [ qi::_val =    qi::_1 ]
            >> *(   '+' >> term     [ qi::_val +=   qi::_1 ]
                |   '-' >> term     [ qi::_val -=   qi::_1 ]
                )
            ;

        term =
            factor                  [ qi::_val =    qi::_1 ]
            >> *(   '*' >> factor   [ qi::_val *=   qi::_1 ]
                |   '/' >> factor   [ qi::_val /=   qi::_1 ]
                )
            ;

        factor =
                (qi::uint_ >> '*' >> 'X' >> '^' >> qi::uint_)[phx::bind(&twoArgs, qi::_1, qi::_2)]
            |   '(' >> expr         [ qi::_val =    qi::_1 ] >> ')'
            |   '-' >> factor       [ qi::_val =   -qi::_1 ]
            |   '+' >> factor       [ qi::_val =    qi::_1 ]
            ;
    }
};

#endif // PARSER_HPP