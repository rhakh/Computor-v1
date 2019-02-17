#include "Equitation.hpp"
#include "iostream" //delete
#include "cmath"

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

    std::cout << "a = " << a << " b = " << b << " c = " << c << " D = " << D << " p = " << this << std::endl;
}

void Equitation::solve(void) {
    D = (b * b) - 4 * a * c;

    if (D == 0)
        x1 = -(b / 2 * a);
    else if (D > 0) {
        x1 = (-b + sqrt(D)) / (2 * a);
        x2 = (-b - sqrt(D)) / (2 * a);
    }
}

void Equitation::printReduced() {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ;

    std::cout << "Reduced form: a × X² + b × X + c = 0" << std::endl << "\t\t";
    if (a != 0)
        std::cout << ((std::modf(a, &integ) == 0.0) ? (int)a : a)
                << " × X² ";
    if (b != 0)
        std::cout << std::showpos
                << ((std::modf(b, &integ) == 0.0) ? (int)b : b)
                << " × X ";
    if (c != 0)
        std::cout << std::showpos
                << ((std::modf(c, &integ) == 0.0) ? (int)c : c)
                << " = 0" << std::endl;
    std::cout.flags(f);
}

void Equitation::printSolution() {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ, local_x1, local_x2;

    if (x1 == boost::none) {
		std::cout << "Equitation hasn't solution." << std::endl;
	}
	else {
        local_x1 = x1.get();
		std::cout << "Equitation has solution: " << std::endl
                    << "X₁ = "
                    << ((std::modf(local_x1, &integ) == 0.0) ? (int)local_x1 : local_x1);
		if (x2 != boost::none) {
            local_x2 = x2.get();
			std::cout << " and X₂ = "
                    << ((std::modf(local_x2, &integ) == 0.0) ? (int)local_x2 : local_x2);
        }
		std::cout << std::endl;
	}
    std::cout.flags(f);
}

void Equitation::printDetailedSolution() {
    std::cout << "a = " << a
                << ", b = " << b
                << ", c = " << c << std::endl
                << "Discriminant = (b)² - (4 × a × c) =" << std::endl
                << "\t\t = (" << b << ")² - (4 × "
                    << a << " × " << c << ") =" << std::endl
                << "\t\t = (" << b * b << ") - ("
                    << 4 * a * c << ") = " << std::endl
                << "\t\t = " << D << std::endl;

    if (D >= 0.0) {
        std::cout << "\t-b ± √D" << std::endl
                    << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯ =" << std::endl
                    << "\t2 × a" << std::endl << std::endl;

        std::cout << "\t" << b << " ± √" << D << std::endl
                        << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯ =" << std::endl
                        << "\t2 × " << a << std::endl << std::endl;

        std::cout << "\t" << b << " ± " << std::sqrt(D) << std::endl
                    << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t" << 2 * a << std::endl << std::endl;
    }
    else {
        std::cout << "\t-b ± √D" << std::endl
                    << "X₁, X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t2 × a" << std::endl;
    }
}
