// #include <boost/config/warning_disable.hpp>
// #include <boost/spirit/include/qi.hpp>
// #include <boost/spirit/include/phoenix_core.hpp>
// #include <boost/spirit/include/phoenix_operator.hpp>
// #include <boost/spirit/include/phoenix_stl.hpp>

// #include <iostream>
// #include <string>
// #include <vector>

// #ifndef __CALCULATOR_GRAMMAR_INTERPRETER_HPP__
// #define __CALCULATOR_GRAMMAR_INTERPRETER_HPP__

// #include <boost/spirit/include/qi.hpp>

// namespace qi     = boost::spirit::qi;
// namespace spirit = boost::spirit;

// template <typename Iterator>
// struct calculator_interpreter
//     : qi::grammar<Iterator, int(), qi::space_type>
//     {
//     calculator_interpreter()
//         : calculator_interpreter::base_type(expr)
//         {
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

//         }

//     qi::rule<Iterator, int(), qi::space_type>
//            expr, term, factor;
//     };

// #endif


// ////////////////////////////////////////////////////////////////////////////
// //  Main program
// ////////////////////////////////////////////////////////////////////////////


// #include <iostream>
// #include <string>

// #include <boost/spirit/include/qi.hpp>

// int main()
//     {
//     std::cout << "//////////////////////////////////////////////\n\n";
//     std::cout << "Expression parser...\n";
//     std::cout << "//////////////////////////////////////////////\n\n";
//     std::cout << "Type an expression... or [q or Q] to quit\n\n";

//     std::string expression;

//     calculator_interpreter<std::string::iterator> calc;

//     while(true)
//         {
//         std::getline(std::cin, expression);
//         if(expression == "q" || expression == "Q") break;
//         std::string::iterator  begin = expression.begin()
//                              , end   = expression.end();

//         int result;
//         bool success = qi::phrase_parse( begin
//                                        , end
//                                        , calc
//                                        , qi::space
//                                        , result);

//         std::cout << "-----------------------\n";
//         if(success && begin == end)
//             {
//             std::cout << "Parsing succeeded\n";
//             std::cout << "result = " << result << "\n";
//             }
//         else
//             {
//             std::cout << "Parsing failed\nstopped at: \""
//                       << std::string(begin,end) << "\"\n";
//             }
//         std::cout << "-----------------------\n";
//         }
//     }




#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
// #include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

namespace qi     = boost::spirit::qi;
namespace spirit = boost::spirit;

struct Obj
{
    int var;
    Obj() { std::cout << "Obj created" << std::endl; };
};

void    oneArg(Obj &a, const int &vec)
{
    std::cout << "Vec = " << vec << std::endl;
}

struct SimpleParser : qi::grammar<std::string::iterator, Obj(), qi::space_type>
{
    qi::rule<std::string::iterator, Obj(), qi::space_type> expr;
    qi::rule<std::string::iterator, qi::space_type> num;

    SimpleParser() : SimpleParser::base_type(expr)
    {
        expr = num % ',';

        num = qi::int_[boost::phoenix::bind(&oneArg, qi::_val, qi::_1)];
    }
};

int main()
{
    SimpleParser calc;
    std::string str = "14, 15, 16";
    std::string::iterator begin = str.begin() , end = str.end();
    Obj a;

    bool success = qi::phrase_parse( begin, end, calc, qi::space, a);
    std::cout << "a = " << a.var << std::endl;

    if(success && begin == end)
        std::cout << "Parsing succeeded\n";
    else
        std::cout << "Parsing failed\nstopped at: \""
                    << std::string(begin,end) << "\"\n";
    return (0);
}