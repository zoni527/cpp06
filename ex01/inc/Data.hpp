/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:11:42 by jvarila           #+#    #+#             */
/*   Updated: 2025/09/16 12:15:20 by jvarila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Data
{
public:
	Data( void ) = default;
	Data( Data const &other );
	~Data( void ) = default;

	Data	&operator=( Data const &rhs );

	int		_x = 42;
	int		_y = 1337;
};
