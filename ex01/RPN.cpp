#include "RPN.hpp"

RPN::RPN( void ) {

}

RPN::RPN( const RPN &copy ) {
	*this = copy;
}

RPN::~RPN( void ) {

}

RPN &RPN::operator=( const RPN &src ) {
	_sequence = src._sequence;
	_errMsg = src._errMsg;
	return (*this);
}

bool	RPN::isOperand(std::string &arg) const{
	size_t track = 0;
	
	if (strchr("+-", arg[track]))
		track++;
	if (!std::isdigit(arg[track]))
		return (false);

	return (true);
}

bool	RPN::isOperator(std::string &arg) const {
	if (strchr("+-*/", arg[0]) && arg.length() == 1)
		return (true);
	return (false);
}

void	RPN::printExpr(std::stack<int> pile) const {
	std::cout << "Pile print ↓" << std::endl;
	while (!pile.empty()) {
		std::cout << pile.top() << std::endl;
		pile.pop();
	}
}

void	RPN::compute(std::string &expression) {
	if (_sequence.size() < 2) {
		throw	InvalidArgument("Stack too small : needs at least 2 operands to compute");
	}

	int	b = _sequence.top(); _sequence.pop();
	int	a = _sequence.top(); _sequence.pop();
	switch (expression[0]) {
		case '+':
			_sequence.push(a + b);
			break;
		case '-':
			_sequence.push(a - b);
			break;
		case '*':
			_sequence.push(a * b);
			break;
		case '/':
			_sequence.push(a / b);
			break;
		default:
			throw	InvalidArgument("Faillure : Argument error should not occur during computation");
	}
}

void	RPN::eval(std::string expression) {
	std::stringstream ss(expression);
	std::string	value;

	ss >> value;
	if (!isOperand(value))
		throw	InvalidArgument("1st stack value has to be an operand");
	_sequence.push(std::strtol(value.c_str(), NULL, 10));
	ss >> value;
	if (!isOperand(value))
		throw	InvalidArgument("2nd stack value has to be an operand");
	_sequence.push(std::strtol(value.c_str(), NULL, 10));

	while (ss >> value) {
		if (isOperator(value))
			compute(value);
		else if (isOperand(value))
			_sequence.push(std::strtol(value.c_str(), NULL, 10));
		else
			throw	InvalidArgument("Invalid Argument");
	}

	if (_sequence.size() != 1)
		throw InvalidArgument("Too many numbers left in stack");
	std::cout << "RPN Result = " << _sequence.top() << std::endl;
}

RPN::InvalidArgument::InvalidArgument(const std::string& msg) : _errMsg(msg) {};

const char	*RPN::InvalidArgument::what() const throw() {
	return (_errMsg.c_str());
}