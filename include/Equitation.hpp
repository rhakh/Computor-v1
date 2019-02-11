#ifndef EQUITATION_HPP
#define EQUITATION_HPP

#include <boost/optional/optional_io.hpp>
#include <utility>

// TODO use move semantics
struct EquitationSolution
{
    boost::optional<double> x1, x2;
    double a, b, c, D;
};


class Equitation
{
public:
    static double a, b, c;
    static void addTerm(double mult, int power);
    static void printReduced(EquitationSolution &sol);
    static void printSolution(EquitationSolution &sol);
    static void printDetailedSolution(EquitationSolution &sol);
    static EquitationSolution solve(void);
};

#endif // EQUITATION_HPP