#pragma once
#ifndef _IANIMATED_DRAW_H_
#define _IANIMATED_DRAW_H_
#include <sfml\Graphics.hpp>
#include <sfml\System.hpp>
#include <graphics/DrawInterface.h>
namespace Graphics
{
	class AnimatedDraw : public virtual DrawInterface
	{
	public:
		AnimatedDraw(bool paused = false, int drawPriority = 0) : DrawInterface(drawPriority), Paused(paused)
		{
		}

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) 
		{

		}
		virtual void Update(const float time, const float TimeScale = 1.0)
		{
			Update(static_cast<sf::Uint32>(time * 0.001), TimeScale);
		}
		virtual void SetPause(const bool value)
		{
			Paused = value;
		}
		virtual bool GetPause() const
		{
			return Paused;
		}
		virtual RawClonePtr RawClone() const override
		{
			return new AnimatedDraw(*this);
		}

	protected:
		bool Paused;
	private:
	};
}


#endif