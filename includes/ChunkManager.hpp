/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:21:31 by jules             #+#    #+#             */
/*   Updated: 2019/08/29 16:35:15 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNKMANAGER_HPP
# define CHUNKMANAGER_HPP

# include <list>
# include "Chunk.hpp"

class ChunkManager
{
	public:
		ChunkManager(std::shared_ptr<Shader> shader); 
		virtual	~ChunkManager();

		void Draw();
		const int	RENDER_SIZE = 10;
	private:
		std::list<std::shared_ptr<Chunk>>	_chunkList;
};

#endif
