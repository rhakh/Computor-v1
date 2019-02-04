#include <iostream>
#include <fstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

#include "CLI.hpp"
#include "EquitationParser.hpp"

bool	CLI::isFlagSet(const std::string &flag) const {
	if (this->vm.count(flag))
		return (true);
	return (false);
}

bool	CLI::getFlag(const std::string &flag, int &result) const {
	if (this->vm.count(flag)) {
		try {
			result = this->vm[flag].as<int>();
		}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (false);
		}
		return (true);
	}
	return (false);
}

bool	CLI::getFlag(const std::string &flag, std::string &result) const {
	if (this->vm.count(flag)) {
		try {
			result = this->vm[flag].as<std::string>();
		}
		catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (false);
		}
		return (true);
	}
	return (false);
}

bool	CLI::processArguments(int argc, const char **argv) {
	namespace po = boost::program_options;
	try {
		po::store(po::parse_command_line(argc, argv, this->desc), this->vm);
		po::notify(this->vm);

		if (this->vm.count("help")) {
			std::cout << desc << std::endl;
		}
	}
	catch (po::error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << desc << std::endl;
		return (false);
	}
	return (true);
}

CLI::CLI(int _argc, const char **_argv) :
desc("Options"), argc(_argc), argv(_argv)
{
	namespace po = boost::program_options;
	std::string	helpStr = std::string("Print help\n"
							"\tThe program to solve polinomial expresion\n"
							"\twith degree equal or less than 2\n"
							"\tExample of usage:\n") +
							std::string("\t") + std::string(_argv[0]) +
							std::string(" '5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0'\n");

	this->desc.add_options()
			("help,h", helpStr.c_str());

	if (!processArguments(_argc, _argv))
		throw CLI_invalidArguments();
}

CLI::~CLI() {}

void	CLI::startLogic() const {
	bool success;
	std::string expression(this->argv[1]);
	std::string::iterator begin = expression.begin(), end = expression.end();
	EquitationParser 	parser;
	EquitationSolution	solution;

	(void)(this->argc);
	
	success = qi::phrase_parse(begin, end, parser, qi::space);
	
	if(success && begin == end)
		std::cout << "Parsing succeeded\n";
	else
		std::cout << "Parsing failed\nstopped at: \""
					<< std::string(begin,end) << "\"\n";
	
	solution = Equitation::solve();
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "a = " << solution.a
				<< ", b = " << solution.b
				<< ", c = " << solution.c
				<< ", D = " << solution.D
				<< std::endl;
	if (solution.x1 == boost::none) {
		std::cout << "Equitation hasn't solution." << std::endl;
	}
	else {
		std::cout << "Equitation has solution: " << std::endl
					<< "X1 = " << solution.x1;
		if (solution.x2 != boost::none)
			std::cout << " and X2 = " << solution.x2;
		std::cout << std::endl;
	}
}
