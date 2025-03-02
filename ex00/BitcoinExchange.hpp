/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/02/28 14:17:50 by nfordoxc         ###   Luxembourg.lu     */
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

class BitcoinExchange
{

	private:

		/*	Attributs	*/
		std::map<std::string, double>	_data;

	public:

		/*	Canonical form	*/
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const &src_object );
		~BitcoinExchange( void );

		BitcoinExchange 	&operator=( BitcoinExchange const &src_object );

		/*	Method	*/
		void				loadData( std::string const &filename );
		double				getExchangeRate( std::string const &date ) const;

};

#endif