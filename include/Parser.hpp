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

void twoArgs(const int &val, const int &val2) {
    std::cout << "coef = " << val << ", power = " << val2 << std::endl;
}

void signFunc(boost::optional<char> val) {
    std::cout << "char = " << val << std::endl;
}

// template <typename Iterator>
// struct D2parser : qi::grammar<Iterator, int(), qi::space_type>
// {
//     qi::rule<Iterator, int(), qi::space_type>   expr, term, factor;

//     D2parser() : D2parser::base_type(expr)
//     {
//         expr = 
//             term                    [ qi::_val =    qi::_1 ]
//             >> *(   '+' >> term     [ qi::_val +=   qi::_1 ]
//                 |   '-' >> term     [ qi::_val -=   qi::_1 ]
//                 )
//             ;

//         term =
//             factor                  [ qi::_val =    qi::_1 ]
//             >> *(   '*' >> factor   [ qi::_val *=   qi::_1 ]
//                 |   '/' >> factor   [ qi::_val /=   qi::_1 ]
//                 )
//             ;

//         factor =
//                 qi::uint_           [ qi::_val =    qi::_1 ]
//             |   '(' >> expr         [ qi::_val =    qi::_1 ] >> ')'
//             |   '-' >> factor       [ qi::_val =   -qi::_1 ]
//             |   '+' >> factor       [ qi::_val =    qi::_1 ]
//             ;
//     }
// };

struct D2parser : qi::grammar<std::string::iterator, int(), qi::space_type>
{
    // qi::rule<std::string::iterator, int(), qi::space_type>   expr, factor, num;
    qi::rule<std::string::iterator, int(), qi::space_type>   program, stmts, term, constant, sign;

    D2parser() : D2parser::base_type(program)
    {
        // expr = qi::eps[qi::_val = 1] >>
        //         factor >> *( factor );

        // factor =
        //         num
        //     | qi::char_('-')[qi::_val = -1] >> num
        //     | qi::char_('+')[qi::_val = 1] >> num;
        
        // num = (qi::uint_ >> '*' >> 'X' >> '^' >> qi::uint_)[phx::bind(&twoArgs, qi::_val * qi::_1, qi::_2)];

        program = +(stmts);

        stmts = (term | constant);

        term = +(
            sign
            >> (qi::uint_
            >> '*'
            >> 'X'
            >> '^'
            >> qi::uint_)[phx::bind(&twoArgs, qi::_1, qi::_2)]
        );

        constant = (sign) >> +(qi::uint_);

        sign = qi::char_('+') | qi::char_('-');
    }
};

#endif // PARSER_HPP