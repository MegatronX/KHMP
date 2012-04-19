#include "Animator.h"
#include <graphics/Animation/FrameAnimation.h>
namespace Graphics
{
	Animator::Animator(sf::Uint32 time)
		: mAnimationMap()
		, mPlayingAnimation(nullptr)
		, mDefaultAnimation()
		, mProgress(0.f)
		, mLoop(false)
		, LastUpdate(time)
		, NextFrameTime(0)
	{
	}

	void Animator::AddAnimation(const std::string& name, Animation::Ptr animation, sf::Time duration)
	{
		auto anim = mAnimationMap.find(name);
		if (anim == mAnimationMap.end())
		{
			mAnimationMap.insert( std::make_pair(name, ScaledAnimation(animation, duration)) );
		}
		else
		{
			//Need to append frames here


			/*auto framAnim = boost::dynamic_pointer_cast<FrameAnimation>(anim->second.first);
			if (frameAnim.get() != nullptr)
			{
				for (auto it )
			}*/
		}
	}

	void Animator::PlayAnimation(const std::string& name, sf::Uint32 time, bool loop)
	{
		AnimationMap::iterator itr = mAnimationMap.find(name);
		assert(itr != mAnimationMap.end());
		LastUpdate = time;
		PlayAnimation(itr->second, loop);
	}

	void Animator::StopAnimation()
	{
		// Animations stopped: Play default animation if available
		if (mDefaultAnimation.first)
			PlayAnimation(mDefaultAnimation, true);
		else
			mPlayingAnimation = nullptr;
	}

	void Animator::Update(sf::Time dt)
	{
		// No animation playing (no default animation available): Do nothing
		if (!mPlayingAnimation)
			return;

		// Update progress, scale dt with 1 / current animation duration
		mProgress += dt.asSeconds() / mPlayingAnimation->second.asSeconds();

		// If animation is expired, stop or restart animation at loops
		if (mProgress > 1.f)
		{
			if (mLoop)
				mProgress = 0.f;//1.f;
			else
				StopAnimation();
		}
	}

	void Animator::Update(sf::Uint32 time)
	{
		if (time > LastUpdate)
		{
			Update(sf::milliseconds(time - LastUpdate));
			LastUpdate = time;
		}
		else
		{
			LastUpdate = time;
		}
		
	}

	void Animator::Animate(sf::Sprite& target) const
	{
		// If animation is playing, apply it (includes default animation, if others are stopped)
		if (mPlayingAnimation)
			mPlayingAnimation->first->Apply(target, mProgress);
	}

	void Animator::PlayAnimation(ScaledAnimation& animation, bool loop)
	{
		mPlayingAnimation = &animation;
		mProgress = 0.f;
		mLoop = loop;
		NextFrameTime = animation.second.asMilliseconds() + LastUpdate;
	}

	void Animator::SetDefaultAnimation(Animation::Ptr animation, sf::Time duration)
	{
		// Invalidate old playing animation, if it refers to default animation (which might be destroyed)
		if (mPlayingAnimation == &mDefaultAnimation)
			mPlayingAnimation = nullptr;

		// Assign animation and duration
		mDefaultAnimation.first = animation;
		mDefaultAnimation.second = duration;

		// If no other animation is active, play default animation
		if (!mPlayingAnimation)
			StopAnimation();
	}
}