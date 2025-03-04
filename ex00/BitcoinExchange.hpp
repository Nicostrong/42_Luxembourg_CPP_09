/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/03/04 15:53:41 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
# include <string>
# include <map>

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

class BitcoinExchange
{

	private:

		/*	Attributs	*/
		std::map<std::string, double>	_data;

		/*	Private Method	*/
		void							loadData( std::string const &filename );
		bool							isValidDate( const std::string &date ) const;

	public:

		/*	Canonical form	*/
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const &src_object );
		~BitcoinExchange( void );

		BitcoinExchange 	&operator=( BitcoinExchange const &src_object );

		/*	Method	*/
		double				getExchangeRate( std::string const &date ) const;

		/*	Exception for open file	*/
		class ErrorOpenFile:	public std::exception
		{
			private:

				std::string		_msg;

			public:

				ErrorOpenFile( std::string const &filename ) throw();
				virtual ~ErrorOpenFile() throw();
				virtual const char	*what() const throw();

		};
		
		/*	Exception for bad date input	*/
		class BadDateInput:	public std::exception
		{
			
			private:

				std::string		_msg;

			public:

				BadDateInput( std::string const &date ) throw();
				virtual ~BadDateInput() throw();
				virtual const char	*what() const throw();

		};

		/*	Exception for bad value input	*/
		class BadValueInput:	public std::exception
		{

			private:

				std::string		_msg;
			
			public:

				BadValueInput( std::string const &value ) throw();
				virtual ~BadValueInput() throw();
				virtual const char	*what() const throw();

		};

};

#endif