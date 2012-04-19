#include "FrameAnimation.h"
#include <algorithm>
#include <cassert>

namespace Graphics
{
	FrameAnimation::Ptr FrameAnimation::create()
	{
		return Ptr( new FrameAnimation() );
	}

	FrameAnimation::FrameAnimation()
		: mFrames()
		, mNormalized(false)
	{
	}

	void FrameAnimation::AddFrame(float relativeDuration, const sf::IntRect& subrect)
	{
		AddFrame(relativeDuration, boost::shared_ptr<sf::Texture>(), subrect);
	}

	void FrameAnimation::AddFrame(float relativeDuration, boost::shared_ptr<const sf::Texture> texture, const sf::IntRect& subrect)
	{
		mFrames.push_back(Frame(relativeDuration, texture, subrect));
		mNormalized = false;
	}

	void FrameAnimation::Apply(sf::Sprite& target, float progress) const
	{
		assert(!mFrames.empty());
		assert(progress >= 0.f && progress <= 1.f);

		EnsureNormalized();
		std::vector<Frame>::const_iterator currentFrame = std::find_if(mFrames.begin(), mFrames.end(), ExhaustTime(progress));
		if (currentFrame == mFrames.end())
			return;

		// Set texture, if necessary - don't adjust sub-rect to whole image
		if (currentFrame->texture)
			target.setTexture(*currentFrame->texture);

		// Set sub-rect
		target.setTextureRect(currentFrame->subrect);
	}

	void FrameAnimation::EnsureNormalized() const
	{
		if (mNormalized)
			return;

		float sum = 0.f;
		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
		{
			sum += it->duration;
		}

		for (auto it = mFrames.begin(); it != mFrames.end(); ++it)
		{
			it->duration /= sum;
		}

		mNormalized = true;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	FrameAnimation::Frame::Frame(float duration, boost::shared_ptr<const sf::Texture> texture, const sf::IntRect& subrect)
		: duration(duration)
		, texture(texture)
		, subrect(subrect)
	{
	}

	FrameAnimation::ExhaustTime::ExhaustTime(float time)
		: time(time)
	{
	}

	bool FrameAnimation::ExhaustTime::operator() (const Frame& frame)
	{
		time -= frame.duration;
		return time < 0.f;
	}
}