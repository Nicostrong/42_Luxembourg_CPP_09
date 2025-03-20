/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:18:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/20 15:57:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <exception>
# include <stack>
# include <cstdlib>

/*	COLOR	*/
# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"


/*	BACKGROUND	*/
# define BG_BLACK	"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GREEN	"\033[42m"
# define BG_YELLOW	"\033[43m"
# define BG_BLUE	"\033[44m"
# define BG_MAGENTA	"\033[45m"
# define BG_CYAN	"\033[46m"
# define BG_WHITE	"\033[47m"

/*	STYLE TEXT	*/
# define BOLD		"\033[1m"
# define ITALIC		"\033[3m"
# define UNDERLINE	"\033[4m"
# define OVERLINE	"\033[53m"
# define BLINK		"\033[5m"
# define INVERTED	"\033[7m"
# define HIDDEN		"\033[8m"
# define STRIKE		"\033[9m"

class	RPN
{

	private:

		std::stack<int>		_stack;

		/*	Private method	*/
		bool				isOperator( const std::string &token ) const;
		bool				isValidValue( const int value ) const;
		void				applyOperator( const std::string &op );
		void				processToken( const std::string &token );

	public:

		/*	Canonical Form */
		RPN( void );
		RPN( RPN const &obj_src );
		~RPN( void );

		RPN					&operator=( RPN const &obj_src );

		/*	Methode	*/
		int					evaluate( const std::string &expression );

		/*	Exception vivision by zero	*/
		class DivByZero:	public std::exception
		{
			public:

				const char	*what() const throw();

		};

		/*	Exception bad operator	*/
		class BadOperator:	public std::exception
		{
			public:

				const char	*what() const throw();

		};

		/*	Exception bad value	*/
		class BadValue:	public std::exception
		{
			public:

				const char	*what() const throw();

		};

		/*	Exception not enougt operands	*/
		class NotEnougtOperands:	public std::exception
		{
			public:

				const char	*what() const throw();

		};

		/*	Exception bad argument	*/
		class BadArg:	public std::exception
		{
			public:

				const char	*what() const throw();

		};
};

#endif