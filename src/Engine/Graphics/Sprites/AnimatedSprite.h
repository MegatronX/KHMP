#pragma once
#ifndef _ANIMATEDSPRITE__H_
#define _ANIMATEDSPRITE__H_

#include <graphics/AnimatedDraw.h>
#include <sfml/Graphics.hpp>
#include <Graphics/Sprites/Sprite.h>
#include <graphics/Animation/Animator.hpp>
//#include <graphics/Animation/Animation.h>
//#include <graphics/Animation/FrameAnimation.h>
namespace Content
{

}
namespace Graphics
{
	class AnimatedSprite : public virtual Sprite, public virtual AnimatedDraw
	{
	public:
		AnimatedSprite();

		AnimatedSprite(boost::shared_ptr<sf::Texture> tx, bool Center = false);

		virtual void SetTexture(boost::shared_ptr<sf::Texture> txt) override;

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

		virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;

		virtual void Draw(sf::RenderWindow& window) override;

		Animator<sf::Sprite, std::string>& GetAnimator();


	protected:
		std::vector<boost::shared_ptr<sf::Texture> > Textures;
		Animator<sf::Sprite, std::string> Anim;
		sf::Uint32 Lastupdate;
	private:
	};
	/*class AnimatedSprite : public sf::Sprite, public AnimatedDraw
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

	typedef boost::shared_ptr<AnimatedSprite> animspr_ptr;*/
}

#endif