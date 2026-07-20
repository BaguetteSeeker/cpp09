#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <ctime>
# include <map>
# include <list>
# include <algorithm>

class BitcoinExchange {

	private:
		std::map<std::string, std::string>	_priceData;
		std::list< std::pair<std::string, std::string> >	_userRequests;

	protected:
		std::string	_errData;

	public:
		BitcoinExchange( void );
		BitcoinExchange( char *userReqsFile );
		BitcoinExchange( BitcoinExchange const &copy );
		~BitcoinExchange( void );
		BitcoinExchange &operator=(const BitcoinExchange &src);

		void	initExchange( char *userFilename );
		int		openFiles(const std::string userFileName, std::ifstream *btcFile, std::ifstream *userFile);
		template <typename Container>
		void	extractData(std::ifstream &fromFile, Container &dst, char delimitor);
		void	printUserWealth( void );

		class	InvalidParameterCount : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
		class	WrongFileName : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
		class	InvalidColumnFormat : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
		class	InvalidDate : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
		class	InvalidBitcoinAmount : public std::exception {
			public :	
				virtual const char* what(void) const throw();
		};
};

std::string	trim(const std::string &s);
inline void store(std::map<std::string, std::string> &dst, const std::pair<std::string, std::string> &entry);
inline void store(std::list< std::pair<std::string, std::string> > &dst, const std::pair<std::string, std::string> &entry);

template <typename Container>
void	BitcoinExchange::extractData(std::ifstream &fromFile, Container &dst, char delimitor) {
	std::string	line;
	size_t		splitIdx;

	while(std::getline(fromFile, line)) {
		splitIdx = line.find(delimitor);
		//Handles the case of empty BTC amount
		if (splitIdx == std::string::npos) { 
			store(dst, std::make_pair(trim(line), std::string("")));
			continue ;
		}
		std::string	key = trim(line.substr(0, splitIdx));
        std::string	value = trim(line.substr(splitIdx + 1, line.size() - splitIdx));
        store(dst, std::make_pair(key, value));
	}
	fromFile.close();
}

#endif