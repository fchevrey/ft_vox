/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:41:12 by jules             #+#    #+#             */
/*   Updated: 2019/09/03 14:51:49 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_HPP
# define WORLD_HPP

# include "FastNoise.h"

class World
{
	public:
		World(void);
		virtual	~World();

		static World	*instance;
		FastNoise	_noise;
	private:
};

#endif
