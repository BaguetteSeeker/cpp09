#include "RPN.hpp"

RPN::RPN( void ) {

}

RPN::RPN( char *args[] ) {
	parseInput(args);
	//Check expression
	//Evaluate expression
}

RPN::RPN( const RPN &copy ) {
	*this = copy;
}

RPN::~RPN( void ) {

}

RPN &RPN::operator=( const RPN &src ) {
	(void)src;
	return (*this);
}

void	RPN::parseInput(char *expression[]) {
	while (*expression) {
		if (strlen(*expression) > 1)
			throw	InvalidArgument();
		
		if (strchr("0123456789", **expression))
			_chrSequence.push(**expression);
		else if (strchr("-+/*", **expression))
			_nbrSequence.push(static_cast<int>(**expression));
		else
			throw	InvalidArgument();
		std::cout << "Pushing :" << *expression <<std::endl;
		expression++;
	}
}

void	RPN::compute(std::string *expression) {
	(void)expression;
}

const char	*RPN::InvalidArgument::what( void ) const throw() {
	return ("Error:");
}