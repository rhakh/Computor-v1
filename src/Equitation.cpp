#include "Equitation.hpp"
#include "iostream" //delete
#include "math.h"

double Equitation::a = 0, Equitation::b = 0, Equitation::c = 0;

void Equitation::addTerm(double mult, int power) {
    switch (power)
    {
        case 2:
            a += mult;
            break;
        case 1:
            b += mult;
            break;
        case 0:
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

void Equitation::printReduced(EquitationSolution &sol) {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ;

    std::cout << "Reduced form: a × X² + b × X + c = 0" << std::endl << "\t\t";
    if (sol.a != 0)
        std::cout << ((std::modf(sol.a, &integ) == 0.0) ? (int)sol.a : sol.a)
                << " × X² ";
    if (sol.b != 0)
        std::cout << std::showpos
                << ((std::modf(sol.b, &integ) == 0.0) ? (int)sol.b : sol.b)
                << " × X ";
    if (sol.c != 0)
        std::cout << std::showpos
                << ((std::modf(sol.c, &integ) == 0.0) ? (int)sol.c : sol.c)
                << " = 0" << std::endl;
    std::cout.flags(f);
}

void Equitation::printSolution(EquitationSolution &sol) {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ, x1, x2;

    if (sol.x1 == boost::none) {
		std::cout << "Equitation hasn't solution." << std::endl;
	}
	else {
        x1 = sol.x1.get();
		std::cout << "Equitation has solution: " << std::endl
                    << "X₁ = "
                    << ((std::modf(x1, &integ) == 0.0) ? (int)x1 : x1);
		if (sol.x2 != boost::none) {
            x2 = sol.x2.get();
			std::cout << " and X₂ = "
                    << ((std::modf(x2, &integ) == 0.0) ? (int)x2 : x2);
        }
		std::cout << std::endl;
	}
    std::cout.flags(f);
}

void Equitation::printDetailedSolution(EquitationSolution &sol) {
    std::cout << "a = " << sol.a
                << ", b = " << sol.b
                << ", c = " << sol.c << std::endl
                << "Discriminant = (b)² - (4 × a × c) =" << std::endl
                << "\t\t = (" << sol.b << ")² - (4 × "
                    << sol.a << " × " << sol.c << ") =" << std::endl
                << "\t\t = (" << sol.b * sol.b << ") - ("
                    << 4 * sol.a * sol.c << ") = " << std::endl
                << "\t\t = " << sol.D << std::endl;

    if (sol.D >= 0.0) {
        std::cout << "\t-b ± √D" << std::endl
                    << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯ =" << std::endl
                    << "\t2 × a" << std::endl << std::endl;

        std::cout << "\t" <<sol.b << " ± √" << sol.D << std::endl
                        << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯ =" << std::endl
                        << "\t2 × " << sol.a << std::endl << std::endl;

        std::cout << "\t" << sol.b << " ± " << std::sqrt(sol.D) << std::endl
                    << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t" << 2 * sol.a << std::endl << std::endl;
    }
    else {
        std::cout << "\t-b ± √D" << std::endl
                    << "X₁, X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t2 × a" << std::endl;
    }
}
