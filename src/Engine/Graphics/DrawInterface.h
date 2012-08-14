#pragma once
#ifndef _DRAWINTERFACE_H_
#define _DRAWINTERFACE_H_
#include <sfml/Graphics.hpp>
#include <sfml/Window.hpp>
#include <Utilities/Cloneable.h>
namespace Graphics
{
	class DrawInterface : public Cloneable<DrawInterface>
	{
	public:
		DrawInterface(int drawPriority = 0, bool drawing = true) : DrawPriority(drawPriority), Drawing(drawing)
		{

		}
		bool IsDrawing() const
		{
			return Drawing;
		}
		void SetDrawing(const bool value)
		{
			Drawing = value;
		}
		virtual void Draw(sf::RenderWindow &window) { }
		virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) {}
		int GetDrawPriority() const
		{
			return DrawPriority;
		}
		void SetDrawPriority(const int priority)
		{
			DrawPriority = priority;
		}
		RawClonePtr RawClone() const override
		{
			return new DrawInterface(*this);
		}
	protected:
		bool Drawing;
		int DrawPriority;
	private:
		
	};
}

#endif