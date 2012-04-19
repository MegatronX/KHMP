#pragma once
#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <graphics/Animation/Animation.h>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <string>

namespace Graphics
{
	class Animator
	{
	public:
		/// @brief Default constructor
		/// 
		Animator(sf::Uint32 time = 0);

		/// @brief Registers an animation with a given name.
		/// @param name String to assign to the animation (may not be registered yet).
		/// @param animation Animation to add to the animator.
		/// @param duration Duration of the animation.
		void	AddAnimation(const std::string& name, Animation::Ptr animation, sf::Time duration);

		/// @brief Plays the animation with the given name.
		/// @param name Name of the animation to play (std::string). An animation with this name must have been added before.
		/// @param loop True if the animation is played repeatedly.
		void	PlayAnimation(const std::string& name, sf::Uint32 time, bool loop = false);

		/// @brief Interrupts the animation that is currently active.
		/// @details If a static frame has been specified, it is shown. Otherwise, the last visible frame of the stopped
		///  animation is shown.
		void	StopAnimation();

		/// @brief Updates the animator's progress. You should call this method each frame.
		/// @param dt Frame time.
		void	Update(sf::Time dt);

		/// @brief Updates the animator's progress. Looks for .
		/// @param dt Frame time.
		void	Update(sf::Uint32 time);
		/// @brief Applies the stored animations to a sf::Sprite.
		/// @param target Sprite whose subrect is changed according to the current animation. If no animation is active,
		///  the sprite is left unchanged or set to the static frame, if previously specified.
		void	Animate(sf::Sprite& target) const;

		/// @brief Sets an animation that is active when all others are stopped.
		/// @param animation Default animation to set. Will be played in a loop if no other animation is currently active.
		///  @a animation can be empty to reset the default animation. In this case, the sprite is not affected when
		///  no animation is playing.
		/// @param duration Duration of the animation.
		void	SetDefaultAnimation(Animation::Ptr animation, sf::Time duration);


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private types
	private:
		typedef std::pair<Animation::Ptr, sf::Time>		ScaledAnimation;
		typedef std::map<std::string, ScaledAnimation>	AnimationMap;


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private member functions
	private:
		void	PlayAnimation(ScaledAnimation& animation, bool loop);


		// ---------------------------------------------------------------------------------------------------------------------------
		// Private variables
	private:
		AnimationMap				mAnimationMap;
		const ScaledAnimation*		mPlayingAnimation;
		ScaledAnimation				mDefaultAnimation;
		float						mProgress;
		bool						mLoop;
		sf::Uint32 LastUpdate;
		sf::Uint32 NextFrameTime;
	};
}

#endif