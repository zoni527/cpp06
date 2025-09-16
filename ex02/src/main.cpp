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

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <random>
#include <iostream>

Base	*generate( void )
{
	std::random_device	rd;
	size_t				r = rd() % 3;

	switch ( r )
	{
		case 0:
			return new A();
		case 1:
			return new B();
		case 2:
			return new C();
		default:
			return nullptr;
	}
}

void	identify( Base *p )
{
	if ( dynamic_cast<A *>( p ) )
		std::cout << "A" << std::endl;
	else if ( dynamic_cast<B *>( p ) )
		std::cout << "B" << std::endl;
	else if ( dynamic_cast<C *>( p ) )
		std::cout << "C" << std::endl;
	else
		std::cout << "D... wait what?!" << std::endl;
}

void	identify( Base &p )
{
	try
	{
		(void)dynamic_cast<A &>( p );
		std::cout << "A" << std::endl;
		return;
	}
	catch ( std::exception const &e ) {}
	try
	{
		(void)dynamic_cast<B &>( p );
		std::cout << "B" << std::endl;
		return;
	}
	catch ( std::exception const &e ) {}
	try
	{
		(void)dynamic_cast<C &>( p );
		std::cout << "C" << std::endl;
		return;
	}
	catch ( std::exception const &e ) {}
	std::cout << "D... wait what?!" << std::endl;
}

int	main()
{
	Base	*b = generate();
	std::cout << "Type identified by pointer casting:	";
	identify( b );
	std::cout << "Type identified by reference casting:	";
	identify( *b );
	delete b;
	return 0;
}
