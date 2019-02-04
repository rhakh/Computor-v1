#include "Equitation.hpp"
#include "iostream" //delete
#include "math.h"

double Equitation::a = 0, Equitation::b = 0, Equitation::c = 0;

void Equitation::addTerm(double mult, int power) {
    switch (power)
    {
        case 0:
            a += mult;
            break;
        case 1:
            b += mult;
            break;
        case 2:
            c += mult;
            break;
        default:
            // TODO
            // assert, impossile situation
            break;
    }
}

EquitationSolution Equitation::solve(void) {
    EquitationSolution  ret = {boost::none, boost::none, 0, 0, 0, 0};
    double D;

    D = (b * b) - 4 * a * c;
    ret.D = D;
    ret.a = a;
    ret.b = b;
    ret.c = c;

    // hans't solution
    if (ret.a == 0)
        return (ret);

    if (D == 0)
        ret.x1 = -(b / 2 * a);
    else if (D > 0) {
        ret.x1 = (-b + sqrt(D)) / (2 * a);
        ret.x2 = (-b - sqrt(D)) / (2 * a);
    }
    return (ret);
}