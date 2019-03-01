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

// struct Obj
// {
//     int var;
//     Obj() { std::cout << "Obj created" << std::endl; };
// };

// void    oneArg(Obj &a, const int &vec)
// {
//     std::cout << "Vec = " << vec << std::endl;
// }

// struct SimpleParser : qi::grammar<std::string::iterator, Obj(), qi::space_type>
// {
//     qi::rule<std::string::iterator, Obj(), qi::space_type> expr;
//     qi::rule<std::string::iterator, qi::space_type> num;

//     SimpleParser() : SimpleParser::base_type(expr)
//     {
//         expr = num % ',';

//         num = qi::int_[boost::phoenix::bind(&oneArg, qi::_val, qi::_1)];
//     }
// };

// int main()
// {
//     SimpleParser calc;
//     std::string str = "14, 15, 16";
//     std::string::iterator begin = str.begin() , end = str.end();
//     Obj a;

//     bool success = qi::phrase_parse( begin, end, calc, qi::space, a);
//     std::cout << "a = " << a.var << std::endl;

//     if(success && begin == end)
//         std::cout << "Parsing succeeded\n";
//     else
//         std::cout << "Parsing failed\nstopped at: \""
//                     << std::string(begin,end) << "\"\n";
//     return (0);
// }


#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace client
{
    namespace fusion = boost::fusion;
    namespace phoenix = boost::phoenix;
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////
    //  Our mini XML tree representation
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_xml1_structures
    struct mini_xml;

    typedef
        boost::variant<
            boost::recursive_wrapper<mini_xml>
          , std::string
        >
    mini_xml_node;

    struct mini_xml
    {
        std::string name;                           // tag name
        std::vector<mini_xml_node> children;        // children
        mini_xml() : name("") { std::cout << "I'm created" << std::endl; };
    };
    //]
}

// We need to tell fusion about our mini_xml struct
// to make it a first-class fusion citizen
//[tutorial_xml1_adapt_structures
BOOST_FUSION_ADAPT_STRUCT(
    client::mini_xml,
    (std::string, name)
    (std::vector<client::mini_xml_node>, children)
)
//]

void just_print(struct client::mini_xml &xml) {
    std::cout << "JUST PRINT " << xml.name << std::endl;
}

namespace client
{
    ///////////////////////////////////////////////////////////////////////////
    //  Print out the mini xml tree
    ///////////////////////////////////////////////////////////////////////////
    int const tabsize = 4;

    void tab(int indent)
    {
        for (int i = 0; i < indent; ++i)
            std::cout << ' ';
    }

    struct mini_xml_printer
    {
        mini_xml_printer(int indent = 0)
          : indent(indent)
        {
        }

        void operator()(mini_xml const& xml) const;

        int indent;
    };

    struct mini_xml_node_printer : boost::static_visitor<>
    {
        mini_xml_node_printer(int indent = 0)
          : indent(indent)
        {
        }

        void operator()(mini_xml const& xml) const
        {
            mini_xml_printer(indent+tabsize)(xml);
        }

        void operator()(std::string const& text) const
        {
            tab(indent+tabsize);
            std::cout << "text: \"" << text << '"' << std::endl;
        }

        int indent;
    };

    void mini_xml_printer::operator()(mini_xml const& xml) const
    {
        tab(indent);
        std::cout << "tag: " << xml.name << std::endl;
        tab(indent);
        std::cout << '{' << std::endl;

        BOOST_FOREACH(mini_xml_node const& node, xml.children)
        {
            boost::apply_visitor(mini_xml_node_printer(indent), node);
        }

        tab(indent);
        std::cout << '}' << std::endl;
    }

    ///////////////////////////////////////////////////////////////////////////
    //  Our mini XML grammar definition
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_xml1_grammar
    template <typename Iterator>
    struct mini_xml_grammar : qi::grammar<Iterator, mini_xml(), ascii::space_type>
    {
        mini_xml_grammar() : mini_xml_grammar::base_type(xml)
        {
            using qi::lit;
            using qi::lexeme;
            using ascii::char_;
            using ascii::string;
            using namespace qi::labels;

            using phoenix::at_c;
            using phoenix::push_back;

            text = lexeme[+(char_ - '<')        ];//[_val += _1]];
            node = (xml | text)                 ;//[_val = _1];

            start_tag =
                    '<'
                >>  !lit('/')
                >>  lexeme[+(char_ - '>')       ]//[_val += _1]]
                >>  '>'
            ;

            end_tag =
                    "</"
                >>  string(_r1)
                >>  '>'
            ;

            xml =
                    start_tag                   [at_c<0>(_val) = _1, phoenix::bind(&just_print, _val)]
                >>  *node                       [push_back(at_c<1>(_val), _1)]
                >>  end_tag(at_c<0>(_val))
            ;
        }

        qi::rule<Iterator, mini_xml(), ascii::space_type> xml;
        qi::rule<Iterator, mini_xml_node(), ascii::space_type> node;
        qi::rule<Iterator, std::string(), ascii::space_type> text;
        qi::rule<Iterator, std::string(), ascii::space_type> start_tag;
        qi::rule<Iterator, void(std::string), ascii::space_type> end_tag;
    };
    //]
}


///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    char const* filename;
    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    std::ifstream in(filename, std::ios_base::in);

    if (!in)
    {
        std::cerr << "Error: Could not open input file: "
            << filename << std::endl;
        return 1;
    }

    std::string storage; // We will read the contents here.
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::copy(
        std::istream_iterator<char>(in),
        std::istream_iterator<char>(),
        std::back_inserter(storage));

    typedef client::mini_xml_grammar<std::string::const_iterator> mini_xml_grammar;
    mini_xml_grammar xml; // Our grammar
    client::mini_xml ast; // Our tree

    using boost::spirit::ascii::space;
    std::string::const_iterator iter = storage.begin();
    std::string::const_iterator end = storage.end();
    bool r = phrase_parse(iter, end, xml, space, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        client::mini_xml_printer printer;
        printer(ast);
        return 0;
    }
    else
    {
        std::string::const_iterator some = iter+30;
        std::string context(iter, (some>end)?end:some);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \": " << context << "...\"\n";
        std::cout << "-------------------------\n";
        return 1;
    }
}