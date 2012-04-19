#pragma once
#ifndef _ANIMATEDSPRITE__H_
#define _ANIMATEDSPRITE__H_

#include <graphics/AnimatedDraw.h>
#include <sfml/Graphics.hpp>
#include <graphics/Animation/Animator.h>
#include <graphics/Animation/Animation.h>
#include <graphics/Animation/FrameAnimation.h>
namespace Content
{

}
namespace Graphics
{
	class AnimatedSprite : public sf::Sprite, public AnimatedDraw
	{
	public:
		AnimatedSprite();
		AnimatedSprite(const boost::shared_ptr<sf::Texture> texture);
		AnimatedSprite(const boost::shared_ptr<sf::Texture> texture, Animator* anim);
		//AnimatedSprite(SpriteLoadDescription& loadDescript);
		void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
		void Draw(sf::RenderWindow &window) override;

		void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

		Animator* GetAnimator();
	protected:
	private:
		Animator* animator;

		boost::shared_ptr<sf::Texture> localTexture;
	};

	typedef boost::shared_ptr<AnimatedSprite> animspr_ptr;
}

#endif