#ifndef EQUITATION_HPP
#define EQUITATION_HPP

#include <boost/optional/optional_io.hpp>
#include <boost/assert.hpp>
#include <utility>
#include <iostream>

class Equitation
{
    double a;
    double b;
    double c;
    double D;
    boost::optional<double> x1;
    boost::optional<double> x2;
public:
    Equitation() :
                a(0.0), b(0.0), c(0.0), D(0.0), x1(boost::none), x2(boost::none) {};
    Equitation(double _a, double _b, double _c) :
                a(_a), b(_b), c(_c), D(0.0), x1(boost::none), x2(boost::none) {};
    ~Equitation() {};

    void addTerm(double mult, int power);
    void printReduced(void);
    void printSolution(void);
    void printDetailedSolution(void);
    void solve(void);
};

#endif // EQUITATION_HPP