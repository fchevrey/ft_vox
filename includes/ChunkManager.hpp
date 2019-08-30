/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:21:31 by jules             #+#    #+#             */
/*   Updated: 2019/08/30 18:04:59 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNKMANAGER_HPP
# define CHUNKMANAGER_HPP

# include <list>
# include "Chunk.hpp"
# include "IGameObject.hpp"

class ChunkManager : public Engine42::IGameObject
{
	public:
		ChunkManager(std::shared_ptr<Shader> shader); 
		virtual	~ChunkManager();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);

		void Draw();
		static const int	RENDER_SIZE = 4;
	private:
		std::list<std::shared_ptr<Chunk>>	_chunkList;
};

#endif
