#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

#ifndef __CALCULATOR_GRAMMAR_INTERPRETER_HPP__
#define __CALCULATOR_GRAMMAR_INTERPRETER_HPP__

#include <boost/spirit/include/qi.hpp>

namespace qi     = boost::spirit::qi;
namespace spirit = boost::spirit;

template <typename Iterator>
struct calculator_interpreter
    : qi::grammar<Iterator, int(), qi::space_type>
    {
    calculator_interpreter()
        : calculator_interpreter::base_type(expr)
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
                qi::uint_           [ qi::_val =    qi::_1 ]
            |   '(' >> expr         [ qi::_val =    qi::_1 ] >> ')'
            |   '-' >> factor       [ qi::_val =   -qi::_1 ]
            |   '+' >> factor       [ qi::_val =    qi::_1 ]
            ;

        }

    qi::rule<Iterator, int(), qi::space_type>
           expr, term, factor;
    };

#endif


////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>

int main()
    {
    std::cout << "//////////////////////////////////////////////\n\n";
    std::cout << "Expression parser...\n";
    std::cout << "//////////////////////////////////////////////\n\n";
    std::cout << "Type an expression... or [q or Q] to quit\n\n";

    std::string expression;

    calculator_interpreter<std::string::iterator> calc;

    while(true)
        {
        std::getline(std::cin, expression);
        if(expression == "q" || expression == "Q") break;
        std::string::iterator  begin = expression.begin()
                             , end   = expression.end();

        int result;
        bool success = qi::phrase_parse( begin
                                       , end
                                       , calc
                                       , qi::space
                                       , result);

        std::cout << "-----------------------\n";
        if(success && begin == end)
            {
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << "\n";
            }
        else
            {
            std::cout << "Parsing failed\nstopped at: \""
                      << std::string(begin,end) << "\"\n";
            }
        std::cout << "-----------------------\n";
        }
    }




// #include <boost/config/warning_disable.hpp>
// #include <boost/spirit/include/qi.hpp>
// #include <boost/spirit/include/phoenix_core.hpp>
// #include <boost/spirit/include/phoenix_operator.hpp>
// #include <boost/spirit/include/phoenix_stl.hpp>
// #include <boost/spirit/include/phoenix_bind.hpp>
// // #include <boost/bind.hpp>

// #include <iostream>
// #include <string>
// #include <vector>
// #include <utility>

// namespace qi     = boost::spirit::qi;
// namespace spirit = boost::spirit;

// void    oneArg(int const &a)
// {
//     std::cout << "A = " << a << std::endl;
// }

// void    twoArgs(int const &a, int const &b)
// {
//     std::cout << "A = " << a << ", B = " << b << std::endl;
// }

// struct AAA {
//     void vectFunc(int const &a, int const &b) {
//         std::cout << "A = " << a << ", B = " << b << std::endl;
//     }
// };

// struct SimpleParser : qi::grammar<std::string::iterator, std::pair<int, int>(), qi::space_type>
// {
//     qi::rule<std::string::iterator, std::pair<int, int>(), qi::space_type> expr;

//     void    static twoArgs(int const &a, int const &b)
//     {
//         std::cout << "A = " << a << ", B = " << b << std::endl;
//     }

//     SimpleParser() : SimpleParser::base_type(expr)
//     {
//         // Worked
//         // expr = (qi::int_ >> ',' >> qi::omit[qi::int_])[boost::bind(&oneArg, _1)];

//         // Worked
//         // expr = (qi::int_ >> ',' >> qi::int_)[std::cout << qi::_1 << " ; " << qi::_2 << std::endl];

//         // Not worked
//         AAA b;
//         expr = (qi::int_ >> ',' >> qi::int_)[boost::phoenix::bind(&AAA::vectFunc, &b, qi::_1, qi::_2)];
//     }
// };

// int main()
// {
//     SimpleParser calc;
//     std::string str = "14, 15";
//     std::string::iterator begin = str.begin() , end = str.end();

//     bool success = qi::phrase_parse( begin, end, calc, qi::space);

//     if(success && begin == end)
//         std::cout << "Parsing succeeded\n";
//     else
//         std::cout << "Parsing failed\nstopped at: \""
//                     << std::string(begin,end) << "\"\n";
//     return (0);
}