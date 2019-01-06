#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent( Actor* owner, int drawOrder )
	: Component( owner )
	, mTexture( nullptr )
	, mDrawOrder( drawOrder )
	, mTexWidth( 0 )
	, mTexHeight( 0 )
{
	mOwner->getGame()->addSprite( this );
}

SpriteComponent::~SpriteComponent()
{
	mOwner->getGame()->removeSprite( this );
}

void SpriteComponent::draw(SDL_Renderer* renderer) noexcept
{
	if ( mTexture )
	{
		SDL_Rect rect;

		rect.w = static_cast<int>( mTexWidth * mOwner->getScale() );
		rect.h = static_cast<int>( mTexHeight * mOwner->getScale() );
		rect.x = static_cast<int>( mOwner->getPosition().x - rect.w / 2);
		rect.y = static_cast<int>( mOwner->getPosition().y - rect.h / 2);

		SDL_RenderCopyEx( renderer, 
			mTexture, 
			nullptr, 
			&rect,
			-Math::ToDegrees( mOwner->getRotation() ),
			nullptr,
			SDL_FLIP_NONE );
	}
}

void SpriteComponent::setTexture( SDL_Texture* texture ) noexcept
{
	mTexture = texture;
	SDL_QueryTexture( texture, nullptr, nullptr, &mTexWidth, &mTexHeight );
}

