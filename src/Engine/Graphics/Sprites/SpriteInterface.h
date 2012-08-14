#pragma once
#ifndef _SPRITEINTERFACE_H_
#define _SPRITEINTERFACE_H_

#include <Graphics/DrawInterface.h>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace Graphics
{
	class SpriteInterface;
	

	class SpriteInterface : public virtual DrawInterface
	{
	public:
		SpriteInterface() : Rotation(0.f), Position(0.f, 0.f), Scale(1.f, 1.f)
		{

		}
		virtual void Rotate(const float angle, bool absolute = true)
		{
			if (absolute)
				Rotation = angle;
			else
				Rotation += angle;
		}
		float GetRotation() const
		{
			return Rotation;
		}

		virtual void SetPosition(const sf::Vector2f& pos)
		{
			Position = pos;
		}
		virtual void SetPosition(const float x, const float y)
		{
			Position.x = x;
			Position.y = y;
		}
		const sf::Vector2f& GetPosition() const
		{
			return Position;
		}

		virtual void IncrementPosition(const sf::Vector2f& incrpos)
		{
			Position += incrpos;
		}
		virtual void IncrementPosition(const float xAdd, const float yAdd = 0)
		{
			Position.x += xAdd;
			Position.y += yAdd;
		}

		virtual void SetScale(const sf::Vector2f& scale)
		{
			Scale = scale;
		}
		virtual void SetScale(const float xScale, const float yScale)
		{
			Scale.x = xScale;
			Scale.y = yScale;
		}
		const sf::Vector2f GetScale() const
		{
			return Scale;
		}

		virtual void SetAlpha(const sf::Uint8 alpha)
		{
			Alpha = alpha;
		}
		virtual void IncrementAlpha(const sf::Uint8 alphaAdd)
		{
			Alpha += alphaAdd;
		}
		sf::Uint8 GetAlpha() const
		{
			return Alpha;
		}
	private:
		float Rotation;
		sf::Vector2f Position;
		sf::Vector2f Scale;
		sf::Uint8 Alpha;
	};
	typedef boost::shared_ptr<SpriteInterface> sprintr_ptr;
}

#endif