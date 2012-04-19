#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <boost/shared_ptr.hpp>
#include <sfml/Graphics/Sprite.hpp>
namespace Graphics
{
	class Animation
	{
		// ---------------------------------------------------------------------------------------------------------------------------
		// Public types
	public:
		/// @brief Shared pointer type to Animation objects
		/// 
		typedef boost::shared_ptr<Animation>		Ptr;


		// ---------------------------------------------------------------------------------------------------------------------------
		// Public member functions
	public:
		/// @brief Applies the animation to a sprite
		/// @param target The sprite who is modified according to the animation.
		/// @param progress Total animation progress, in the interval [0,1].
		virtual void	Apply(sf::Sprite& target, float progress) const = 0;
	};
}

#endif