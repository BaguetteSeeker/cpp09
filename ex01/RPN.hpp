#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include <stdio.h>
# include <cstring>
# include <stack>
# include <algorithm>


class RPN {

	private:
		std::stack<int>		_nbrSequence;
		std::stack<char>	_chrSequence;
		RPN( void );
		
	public:
		RPN( char *args[]);
		RPN( RPN const &copy );
		~RPN( void );
		RPN &operator=(const RPN &src);

		void	parseInput(char *expression[]);
		void	compute(std::string *expression);

		class	InvalidArgument: public std::exception {
			public:
				virtual const char*	what(void) const throw();
		};
};

#endif