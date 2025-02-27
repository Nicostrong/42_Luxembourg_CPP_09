/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:03:50 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/02/27 14:16:48 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

class BitcoinExchange
{

	private:

		/*	Attributs	*/

	public:

		/*	Canonical form	*/
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const &src_object );
		~BitcoinExchange( void );

		BitcoinExchange 	&operator=( BitcoinExchange const &src_object );

		/*	Method	*/

};

#endif