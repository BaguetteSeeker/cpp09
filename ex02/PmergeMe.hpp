#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <algorithm>

class PmergeMe {

	private:

	public:
		PmergeMe( void );
		PmergeMe( PmergeMe const &copy );
		~PmergeMe( void );
		PmergeMe &operator=(const PmergeMe &src);
};

#endif