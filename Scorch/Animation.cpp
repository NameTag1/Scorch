#include "Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "DataTable.h"
#include "Logger.h"


Animation::Animation()
	: mSprite()
	, mFrameSize()
	, mNumFrames(0)
	, mCurrentFrame(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mRepeat(false)
	, mCentered(false)
{
}

Animation::Animation(const sf::Texture& texture)
	: mSprite(texture)
	, mFrameSize()
	, mNumFrames(0)
	, mCurrentFrame(0)
	, mDuration(sf::Time::Zero)
	, mElapsedTime(sf::Time::Zero)
	, mRepeat(false)
	, mCentered(false)
{
}

Animation::Animation(const TextureHolder& textureHolder, json data)
	: mSprite(textureHolder.get(std::string(data["Texture"])))
	, mFrameSize({data["Frame_W"], data["Frame_H"]})
	, mNumFrames(data["Number_of_Frames"])
	, mCurrentFrame(0)
	, mDuration(sf::seconds(data["Duration"]))
	, mElapsedTime(sf::Time::Zero)
	, mRepeat(data["Repeated"])
	, mCentered(data["Centered"])
{
	update(sf::seconds(0));
	Logger::Instance->LogData(Logger::Action, "Animation with texture \"" + std::string(data["Texture"]) + "\" created from JSON");
}

void Animation::setTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}

const sf::Texture* Animation::getTexture() const
{
	return mSprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	mFrameSize = frameSize;
}

sf::Vector2i Animation::getFrameSize() const
{
	return mFrameSize;
}

void Animation::setNumFrames(std::size_t numFrames)
{
	mNumFrames = numFrames;
}

std::size_t Animation::getNumFrames() const
{
	return mNumFrames;
}

std::size_t Animation::getCurrentFrame() const
{
	return mCurrentFrame;
}

void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

sf::Time Animation::getDuration() const
{
	return mDuration;
}

void Animation::setRepeating(bool flag)
{
	mRepeat = flag;
}

bool Animation::isRepeating() const
{
	return mRepeat;
}

void Animation::setCentered(bool centered)
{
	mCentered = centered;
}

void Animation::flip(bool x, bool y)
{
	if (x) {
		mSprite.scale(-1.f, 1.f);
	}
	if (y) {
		mSprite.scale(1.f, -1.f);
	}
}

void Animation::mCenterOrigin()
{
	centerOrigin(mSprite);
}

void Animation::restart()
{
	mCurrentFrame = 0;
}

bool Animation::isFinished() const
{
	return mCurrentFrame >= mNumFrames;
}

sf::FloatRect Animation::getLocalBounds() const
{
	// Use sprite's local bounds and account for sprite origin so local rect
	// is correctly centered when the sprite's origin is moved (e.g. centerOrigin).
	// This returns bounds in the Animation's local coordinate space.
	sf::FloatRect spriteLocal = mSprite.getLocalBounds(); // typically (0,0,width,height)
	sf::Vector2f origin = mSprite.getOrigin();

	// shift by origin so local coords are relative to the Animation (sprite at 0,0 with its origin applied)
	spriteLocal.left -= origin.x;
	spriteLocal.top -= origin.y;

	return spriteLocal;
}

sf::FloatRect Animation::getGlobalBounds() const
{
	// Compute sprite's bounds in its own coordinate space then transform by the Animation's transform.
	// This properly composes the sprite's local transform (origin/scale) with the Animation's transform.
	sf::FloatRect spriteGlobal = mSprite.getGlobalBounds(); // respects mSprite origin/scale/textureRect
	return getTransform().transformRect(spriteGlobal);
}

void Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
	mElapsedTime += dt;

	sf::Vector2i textureBounds(mSprite.getTexture()->getSize());

	sf::IntRect textureRect = mSprite.getTextureRect();

	if (mCurrentFrame == 0)
		textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);

	// While we have a frame to process
	while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
	{
		// Move the texture rect left
		textureRect.left += textureRect.width;

		// If we reach the end of the texture
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			// Move it down one line
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		// And progress to next frame
		mElapsedTime -= timePerFrame;
		if (mRepeat)
		{
			mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

			if (mCurrentFrame == 0)
				textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
		}
		else
		{
			mCurrentFrame++;
		}
	}

	mSprite.setTextureRect(textureRect);

	if (mCentered) {
		centerOrigin(mSprite);
	}
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}