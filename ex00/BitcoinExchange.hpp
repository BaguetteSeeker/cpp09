#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <map>
# include <algorithm>

class BitcoinExchange {

	private:
		std::map<std::string, std::string>	_priceData;
		std::map<std::string, std::string>	_userRequests;

	public:
		BitcoinExchange( void );
		BitcoinExchange( char *userReqsFile );
		BitcoinExchange( BitcoinExchange const &copy );
		~BitcoinExchange( void );
		BitcoinExchange &operator=(const BitcoinExchange &src);

		void	initExchange( char *userFilename );
		int		openFiles(const std::string userFileName, std::ifstream *btcFile, std::ifstream *userFile);
		void	extractData(std::ifstream &fromFile, std::map<std::string, std::string> &dst, char delimitor);
		void	printUserWealth( void );

		class	InvalidParameterCount : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
		class	WrongFileName : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
};

#endif