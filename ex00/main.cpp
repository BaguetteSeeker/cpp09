#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[]) {
	try {
		if (argc != 2)
			throw BitcoinExchange::InvalidParameterCount();
		BitcoinExchange	exchange(argv[1]);
	}
	catch(const BitcoinExchange::InvalidParameterCount& e) {
		std::cerr << e.what() << std::endl;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}