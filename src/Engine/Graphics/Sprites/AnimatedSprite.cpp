#include "AnimatedSprite.h"

namespace Graphics
{

	AnimatedSprite::AnimatedSprite()
	{

	}

	AnimatedSprite::AnimatedSprite(boost::shared_ptr<sf::Texture> tx, bool center) : Sprite(tx, center)
	{

	}

	void AnimatedSprite::SetTexture(boost::shared_ptr<sf::Texture> txt)
	{
		if (Textures.size() > 0)
		{
			Textures[0] = txt;
		}
		else
		{
			Textures.push_back(txt);
		}
		sp.setTexture(*txt);
	}

	void AnimatedSprite::Update(const sf::Uint32 time, const float TimeScale)
	{
			Anim.update(time);
			Anim.animate(sp);
			Lastupdate = time;
	}

	void AnimatedSprite::Draw(sf::RenderWindow &window, sf::Shader &shader)
	{
		Sprite::Draw(window, shader);
	}

	void AnimatedSprite::Draw(sf::RenderWindow& window)
	{
		Sprite::Draw(window);
	}

	Animator<sf::Sprite, std::string>& AnimatedSprite::GetAnimator()
	{
		return Anim;
	}

	/*AnimatedSprite::AnimatedSprite() : sf::Sprite()
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
	}*/
}
