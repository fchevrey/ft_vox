/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:21:31 by jules             #+#    #+#             */
/*   Updated: 2019/09/04 14:33:28 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNKMANAGER_HPP
# define CHUNKMANAGER_HPP

# include <list>
# include "Chunk.hpp"
# include "IGameObject.hpp"

class ChunkManager : public Engine42::IGameObject, public Renderer
{
	public:
		ChunkManager(std::shared_ptr<Shader> shader); 
		virtual	~ChunkManager();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);

		//void Draw();
    	virtual void Draw() const;

		static const int	RENDER_SIZE = 10;
		static const int	ASYNC_NUM_CHUNKS_PER_FRAME = 8;
	private:
		std::list<std::shared_ptr<Chunk>>	_chunkList;
		unsigned int						_text;

		void _CheckUnload(float & coord, float & dif, std::shared_ptr<Chunk> chunk);
};

#endif
