#pragma once
#ifndef _FRAMEANIMATION_H_
#define _FRAMEANIMATION_H_

#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace Graphics
{
	class FrameAnimation : public Animation
	{
	public:
		/// @brief Shared pointer type to FrameAnimation objects
		/// 
		typedef boost::shared_ptr<FrameAnimation>		Ptr;


		// ---------------------------------------------------------------------------------------------------------------------------
		// Public static member functions
	public:
		/// @brief Returns a shared pointer to a newly created FrameAnimation.
		/// @copydetails FrameAnimation::FrameAnimation()
		static Ptr					create();


		// ---------------------------------------------------------------------------------------------------------------------------
		// Public member functions
	public:
		/// @brief Default constructor
		/// 
		FrameAnimation();

		/// @brief Adds a frame to the animation, changes only the sub-rect.
		/// @param relativeDuration Duration of the frame relative to the other durations.
		/// @param subrect %Rectangle of the sf::Texture that is used for the new frame.
		void	AddFrame(float relativeDuration, const sf::IntRect& subrect);

		/// @brief Adds a frame to the animation, changes both texture and sub-rect.
		/// @param relativeDuration Duration of the frame relative to the other durations.
		/// @param texture Smart pointer to sf::Texture that is used for the new frame.
		/// @param subrect %Rectangle of the sf::Texture that is used for the new frame.
		void	AddFrame(float relativeDuration, boost::shared_ptr<const sf::Texture> texture,
			const sf::IntRect& subrect);

		virtual void	Apply(sf::Sprite& target, float progress) const;


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private types
	private:
		// Frame with sub-rectangle and duration
		struct Frame
		{
			Frame(float duration, boost::shared_ptr<const sf::Texture> texture, const sf::IntRect& subrect);

			mutable float					duration;
			sf::IntRect						subrect;
			boost::shared_ptr<const sf::Texture>	texture;
		};

		// Functor to find current frame
		struct ExhaustTime
		{
			explicit					ExhaustTime(float time);
			bool						operator() (const Frame& frame);

			float						time;
		};


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private member functions
	private:
		void	EnsureNormalized() const;


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private variables
	private:
		std::vector<Frame>			mFrames;
		mutable bool				mNormalized;
	};
}

#endif