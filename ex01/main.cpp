#include "RPN.hpp"

int	main(int argc, char *argv[]) {
	//Check limit count
	try {
		if (argc < 2)
			throw RPN::InvalidArgument();
		std::cout << "Starting computation.." << std::endl;
		RPN	computation(++argv);
		
		// computation.computeRpn(++argv);
		
		// computeRpn(argv);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
}