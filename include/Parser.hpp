#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
//#include <boost/spirit.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/phoenix.hpp>

class Parser {

public:
    bool parse(const std::string &str);
    bool validate(const std::string &str);
};

#endif // PARSER_HPP