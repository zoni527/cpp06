/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:13:45 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/16 12:17:00 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data:: Data( Data const &other ) : _x( other._x ), _y( other._y ) {}

Data	&Data::operator=( Data const &rhs )
{
	if ( this != &rhs )
	{
		_x = rhs._x;
		_y = rhs._y;
	}
	return *this;
}
