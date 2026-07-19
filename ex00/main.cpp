#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[]) {
	try {
		if (argc != 2)
			throw BitcoinExchange::InvalidParameterCount();

		BitcoinExchange	oui;
		BitcoinExchange	exchange(argv[1]);


		//check userRequests syntax
		//print requests results

	}
	// catch(const BitcoinExchange::InvalidParameterCount& e) {
	// 	std::cerr << e.what() << std::endl;
	// }
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	//Chek filename integrity
	//Parse file to assert data integrity : date | value ; Year-Month-Day ; and value (BTC amount) between 0 ad 1 000
	//throw custom exception for each error	
	//If the date required does not exist, fetch closest by anteriority 
	
	// 
	// 
	return (0);
	
}