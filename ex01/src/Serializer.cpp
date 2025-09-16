/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:56:14 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/16 12:23:21 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

uintptr_t	Serializer::serialize( Data *ptr )
{
	return reinterpret_cast<uintptr_t>( ptr );
}

Data		*Serializer::deserialize( uintptr_t raw )
{
	return reinterpret_cast<Data *>( raw );
}
