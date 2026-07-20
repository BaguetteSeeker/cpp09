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

/* extractData() utilities */
inline void store(std::map<std::string, std::string> &dst, const std::pair<std::string, std::string> &entry){
    dst.insert(entry);
}

inline void store(std::list< std::pair<std::string, std::string> > &dst, const std::pair<std::string, std::string> &entry) {
    dst.push_back(entry);
}

std::string	trim(const std::string &s) {
    std::string::size_type start = s.find_first_not_of(" \t\r\n");
    std::string::size_type end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

/* Date validation utilities */
static bool isDigits(const std::string &s)
{
    for (std::string::size_type i = 0; i < s.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }
    return true;
}

static bool isLeapYear(int y)
{
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static bool isValidDate(const std::string &date)
{
    // Strict format: YYYY-MM-DD
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    std::string ys = date.substr(0, 4);
    std::string ms = date.substr(5, 2);
    std::string ds = date.substr(8, 2);

    if (!isDigits(ys) || !isDigits(ms) || !isDigits(ds))
        return false;

    int y = std::atoi(ys.c_str());
    int m = std::atoi(ms.c_str());
    int d = std::atoi(ds.c_str());

    if (m < 1 || m > 12)
        return false;

    static const int mdays[12] = {
        31,28,31,30,31,30,31,31,30,31,30,31
    };

    int maxDay = mdays[m - 1];
    if (m == 2 && isLeapYear(y))
        maxDay = 29;

    if (d < 1 || d > maxDay)
        return false;

    return true;
}

/* Main flow for exchange launch */
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

void	BitcoinExchange::printUserWealth( void ) {
	std::list< std::pair<std::string, std::string> >::const_iterator requests = this->_userRequests.begin();
	std::map<std::string, std::string>::iterator result;
	char *amountEnd = NULL;
	double btcAmount;

	if (_userRequests.empty())
		return ;
	if (requests->first != "date" || requests->second != "value")
		throw	InvalidColumnFormat();

	while (++requests != _userRequests.end()) {
		btcAmount = std::strtod(requests->second.c_str(), &amountEnd);
		try {
			if (!isValidDate(requests->first)) {
				_errData = requests->first;
				throw	InvalidDate();
			}
			//Also checks that amount contains only digits
			if (requests->second.empty() || btcAmount < 0 || btcAmount > 1000
					|| amountEnd == requests->second.c_str() || *amountEnd != '\0') {
				_errData = requests->second;
				throw	InvalidBitcoinAmount();
			}
			//Next 3 lines fetch closest price by anteriority
			result = _priceData.upper_bound(requests->first);
			if (result != _priceData.begin())
				--result;
			//Print
			if (result != _priceData.end())
				std::cout << requests->first << " => " << btcAmount <<"BTC = " <<
					atof(requests->second.c_str()) * atof(result->second.c_str())  << std::endl;
		} catch (const InvalidDate &e) {
			std::cerr << "Error: Invalid date => " << _errData << e.what() << std::endl;
		} catch (const InvalidBitcoinAmount &e) {
			std::cerr << "Error: Invalid BTC amount => " << _errData << e.what() << std::endl;
		} catch (const std::exception &e) {
			std::cerr << "Error: "<< e.what() << std::endl;
		}
	}
}

const char	*BitcoinExchange::WrongFileName::what() const throw() {
	return ("Failled to open file: Wrong filename or missing data.csv");
}

const char	*BitcoinExchange::InvalidParameterCount::what() const throw() {
	return ("Invalid parameter count: Expecting one filename");
}

const char	*BitcoinExchange::InvalidColumnFormat::what() const throw() {
	return ("Invalid format: \"Date | Value\" expected at the top of the file");
}

const char	*BitcoinExchange::InvalidDate::what() const throw() {
	return (": Make sure to respect format Year-Month-Day and provide valid values");
}

const char	*BitcoinExchange::InvalidBitcoinAmount::what() const throw() {
	return (": Expecting amount between 0 and 1000");
}
