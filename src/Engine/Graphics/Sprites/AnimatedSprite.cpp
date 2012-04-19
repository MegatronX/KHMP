#include "AnimatedSprite.h"

namespace Graphics
{
	AnimatedSprite::AnimatedSprite() : sf::Sprite()
	{

	}
	AnimatedSprite::AnimatedSprite(const boost::shared_ptr<sf::Texture> texture) : sf::Sprite(*texture), localTexture(texture)
	{

	}
	AnimatedSprite::AnimatedSprite(const boost::shared_ptr<sf::Texture> texture, Animator* anim) : sf::Sprite(*texture), localTexture(texture), animator(anim)
	{

	}
	void AnimatedSprite::Draw(sf::RenderWindow &window, sf::Shader &shader)
	{
		animator->Animate(*this);
		window.draw(*this);
	}
	void AnimatedSprite::Draw(sf::RenderWindow &window)
	{
		animator->Animate(*this);
		window.draw(*this);
	}

	void AnimatedSprite::Update(const sf::Uint32 time, const float TimeScale)
	{
		if (animator != nullptr)
			animator->Update(time * TimeScale);	
	}

	Animator* AnimatedSprite::GetAnimator()
	{
		return animator;
	}
}
