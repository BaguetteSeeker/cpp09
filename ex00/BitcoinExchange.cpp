#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( void ) {
	std::cerr << "WARNING → Instance initialized without user queries; You can later call in your code the initExchange(userQueriesFName) method to start the exchange" << std::endl;
}

BitcoinExchange::BitcoinExchange( char *userReqsFile ) {
	initExchange(userReqsFile);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &copy ) {
	*this = copy;
}

BitcoinExchange::~BitcoinExchange( void ) {

}

BitcoinExchange &BitcoinExchange::operator=( const BitcoinExchange &src ) {
	this->_priceData = src._priceData;
	this->_userRequests = src._userRequests;
	return (*this);
}

void	BitcoinExchange::initExchange( char *userFilename ) {
	std::ifstream	priceStream;
	std::ifstream	requestStream;

	BitcoinExchange::openFiles(userFilename, &priceStream, &requestStream);
	extractData(priceStream, this->_priceData, ',');
	extractData(requestStream, this->_userRequests, '|');
	printUserWealth();
}

int BitcoinExchange::openFiles(const std::string userFileName, std::ifstream *btcFile, std::ifstream *userFile) {
	(*btcFile).open("data.csv", std::ifstream::in);
	(*userFile).open(userFileName.c_str(), std::ifstream::in);

	if (!btcFile->is_open() || !userFile->is_open()) {
		(*btcFile).close();
		(*userFile).close();
		throw	BitcoinExchange::WrongFileName();
   	}
	return (0);
}

static std::string trim(const std::string &s) {
    std::string::size_type start = s.find_first_not_of(" \t\r\n");
    std::string::size_type end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

void	BitcoinExchange::extractData(std::ifstream &fromFile, 
			std::map<std::string, std::string> &dst, char delimitor) {

	std::string	line;
	std::string	date;
	std::string	data;
	size_t		splitIdx;

	while(std::getline(fromFile, line)) {
		// std::cout << "Entering line" << std::endl;
		// line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		splitIdx = line.find(delimitor);
		if (splitIdx == std::string::npos) { 
			// std::cout << line << " >> empty" << std::endl;
			dst[trim(line)] = "";
			continue ;
		}
		
		dst[trim(line.substr(0, splitIdx))] =
			trim(line.substr(splitIdx + 1, line.size() - splitIdx));
		// std::cout << line.substr(0, splitIdx) << line.substr(splitIdx + 1, line.size() - splitIdx) << std::endl;
	}
	fromFile.close();
	// std::for_each(dst.begin(), dst.end(), ) 
}

void	BitcoinExchange::printUserWealth( void ) {
	std::map<std::string, std::string>::const_iterator requests = this->_userRequests.begin();
	std::map<std::string, std::string>::const_iterator result;


	for(std::map<std::string, std::string>::reverse_iterator it = _priceData.rbegin();
		it != _priceData.rend(); ++it)
	{
		std::cout << it->first << " " << it->second << "\n";
	}

	while (requests != _userRequests.end()) {
		if (_priceData.upper_bound(requests->first) != _priceData.end())
			std::cout << "Matched result: " << _priceData.upper_bound(requests->first)->first
				<< " ==> " << _priceData.upper_bound(requests->first)->second << " asking quantity [" << requests->second<< "]" << std::endl;

		// result = _priceData.find(requests->first);
		// if (result != _priceData.end())
		// 	std::cout << "Matched result: " << _priceData.find(requests->first)->first << _priceData.find(requests->first)->second << std::endl;
		// std::cout << requests->first /* << _priceData.find(it->first)->second */ << std::endl;
		// _priceData.upper_bound
		requests++;
	}

	
	//basic print
	//check top line
	//check date / empty second string
	//handle duplicates in user requests
}


const char	*BitcoinExchange::WrongFileName::what() const throw() {
	return ("Failled to open file: Wrong filename or missing data.csv");
}

const char	*BitcoinExchange::InvalidParameterCount::what() const throw() {
	return ("Invalid parameter count: Expecting one filename");
}