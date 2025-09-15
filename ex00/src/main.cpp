/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:16:14 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/15 15:19:12 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int	main( int argc, char *argv[] )
{
	if ( argc != 2 )
	{
		std::cout << "Usage: ./convert <literal>" << std::endl;
		return 1;
	}
	std::string	str = argv[1];
	ScalarConverter::convert( str );
	return 0;
}
