#include "Equitation.hpp"
#include "iostream" //delete
#include <cmath>
#include <limits>

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
            BOOST_ASSERT_MSG(0, "Impossible action");
            break;
    }
}

void Equitation::solve(void) {
    D = (b * b) - 4 * a * c;

    // special case
    if (a == 0 && b == 0) {
        x1 = -std::numeric_limits<double>::infinity();
        x2 = std::numeric_limits<double>::infinity();
        return ;
    }

    if (D == 0)
        x1 = -(b / 2 * a);
    else if (D > 0) {
        if (a != 0) {
            x1 = (-b + sqrt(D)) / (2 * a);
            x2 = (-b - sqrt(D)) / (2 * a);
        }
        else {
            if (b != 0)
                x1 = -c / b;
        }
    }
}

void Equitation::printReduced() {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ;

    std::cout << "Polynomial degree: ";
    if (a != 0)
        std::cout << 2 << std::endl;
    else if (b != 0)
        std::cout << 1 << std::endl;
    else
        std::cout << 0 << std::endl;

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
    else
        std::cout << std::endl;

    std::cout.flags(f);
}

void Equitation::printSolution() {
    std::ios_base::fmtflags f(std::cout.flags());
    double integ, local_x1, local_x2;

    // special case
    if (this->a == 0 && this-> b == 0 && this->c == 0) {
        std::cout << "Equitation has solution: all real numbers" << std::endl;
        return ;
    }
    else if (this->a == 0 && this-> b == 0 && this->c != 0) {
        std::cout << "Equitation hasn't solution." << std::endl;
        return ;
    }

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

        std::cout << "\t" << -b << " ± √" << D << std::endl
                        << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯ =" << std::endl
                        << "\t2 × " << a << std::endl << std::endl;

        std::cout << "\t" << -b << " ± " << std::sqrt(D) << std::endl
                    << "X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t" << 2 * a << std::endl << std::endl;

        std::cout << "\t" << -b + std::sqrt(D) << std::endl
                    << "X₁ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t" << 2 * a << std::endl << std::endl;

        std::cout << "\t" << -b - std::sqrt(D) << std::endl
                    << "X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t" << 2 * a << std::endl << std::endl;
    }
    else {
        std::cout << "\t-b ± √D" << std::endl
                    << "X₁, X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯" << std::endl
                    << "\t2 × a" << std::endl;
    }
}
