/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:16:14 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/16 12:39:47 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int	main( void )
{
	Data		d;
	Data		*ptr = &d;

	std::cout << "ptr:		" << ptr << '\n';
	std::cout << "ptr->_x:	" << ptr->_x << '\n';
	std::cout << "ptr->_y:	" << ptr->_y << '\n';
	ptr = Serializer::deserialize( Serializer::serialize( &d ) );
	std::cout << "ptr:		" << ptr << '\n';
	std::cout << "ptr->_x:	" << std::dec << ptr->_x << '\n';
	std::cout << "ptr->_y:	" << ptr->_y << '\n';
	return 0;
}
