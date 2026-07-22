#include "RPN.hpp"

int	main(int argc, char *argv[]) {
	try {
		//Expecting ./RPN " expression " only since standalone operators will be interpreted by the shell
		if (argc != 2)
			throw RPN::InvalidArgument("");
		RPN	a;
		a.eval(argv[1]);
	} catch(const RPN::InvalidArgument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return (0);
}