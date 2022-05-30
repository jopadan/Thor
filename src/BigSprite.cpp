/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2022 Jan Haller
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <Thor/Graphics/BigSprite.hpp>
#include <Thor/Graphics/BigTexture.hpp>

#include <Aurora/Tools/ForEach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cassert>


namespace thor
{

BigSprite::BigSprite()
: sf::Drawable()
, sf::Transformable()
, mSplitSprites()
, mSize(0.f, 0.f)
, mColor(sf::Color::White)
, mTexture(NULL)
, mTextureRect()
{
}

BigSprite::BigSprite(const BigTexture& texture)
: sf::Drawable()
, sf::Transformable()
, mSplitSprites()
, mSize()
, mColor(sf::Color::White)
, mTexture(NULL)
, mTextureRect()
{
	setTexture(texture);
}

BigSprite::BigSprite(const BigTexture& texture, const sf::IntRect& rectangle)
: sf::Drawable()
, sf::Transformable()
, mSplitSprites()
, mSize()
, mColor(sf::Color::White)
, mTexture(NULL)
{
	setTexture(texture);
	setTextureRect(rectangle);
}


void BigSprite::setTexture(const BigTexture& texture, bool resetRect)
{
	if (resetRect || (!mTexture && (mTextureRect == sf::IntRect())))
	    setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));

	mTexture = &texture;

	mSize = texture.fillSprites(mColor, mSplitSprites);
}

void BigSprite::setTextureRect(const sf::IntRect& rectangle)
{
	if (rectangle != mTextureRect)
	{
	    mTextureRect = rectangle;
	    updatePositions();
	    updateTexCoords();
	}
}

void BigSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	AURORA_FOREACH(const sf::Sprite& sprite, mSplitSprites)
		target.draw(sprite, states);
}

void BigSprite::setColor(const sf::Color& color)
{
	mColor = color;
	AURORA_FOREACH(sf::Sprite& sprite, mSplitSprites)
		sprite.setColor(color);
}

sf::Color BigSprite::getColor() const
{
	return mColor;
}

const BigTexture* BigSprite::getTexture() const
{
	return mTexture;
}

const sf::IntRect& BigSprite::getTextureRect() const
{
	return mTextureRect;
}

sf::FloatRect BigSprite::getLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mSize.x, mSize.y);
}

sf::FloatRect BigSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void BigSprite::updatePositions()
{
	sf::FloatRect bounds = getLocalBounds();

	mVertices[0].position = sf::Vector2f(0, 0);
	mVertices[1].position = sf::Vector2f(0, bounds.height);
	mVertices[2].position = sf::Vector2f(bounds.width, 0);
	mVertices[3].position = sf::Vector2f(bounds.width, bounds.height);
}

void BigSprite::updateTexCoords()
{
	float left   = static_cast<float>(mTextureRect.left);
	float right  = left + mTextureRect.width;
	float top    = static_cast<float>(mTextureRect.top);
	float bottom = top + mTextureRect.height;

	mVertices[0].texCoords = sf::Vector2f(left, top);
	mVertices[1].texCoords = sf::Vector2f(left, bottom);
	mVertices[2].texCoords = sf::Vector2f(right, top);
	mVertices[3].texCoords = sf::Vector2f(right, bottom);
}

} // namespace thor
