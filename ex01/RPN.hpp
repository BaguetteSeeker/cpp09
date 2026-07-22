#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <stdlib.h>
# include <stdio.h>
# include <cstring>
# include <stack>
# include <algorithm>

class RPN {

	private:
		std::stack<int>	_sequence;
		
	protected:
		std::string	_errMsg;
		
	public:
		RPN( void );
		RPN( RPN const &copy );
		~RPN( void );
		RPN &operator=(const RPN &src);

		void	eval(std::string expression);
		void	compute(std::string &expression);
		bool	isOperand(std::string &arg) const;
		bool	isOperator(std::string &arg) const;
		//Debug purposes only
		void	printExpr(std::stack<int> pile) const;

		class	InvalidArgument: public std::exception {
			public:
				InvalidArgument(const std::string &msg);
				virtual const char*	what( void ) const throw();
				virtual ~InvalidArgument () throw() {};
			private:
				std::string	_errMsg;
		};
};

#endif