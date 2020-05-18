#pragma once

#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent( Actor* owner, int drawOrder )
	: SpriteComponent( owner, drawOrder )
	, mScrollSpeed( 0.0f )
{

}

void BGSpriteComponent::update( float deltaTime ) noexcept
{
	SpriteComponent::update( deltaTime );

	for ( auto& bg : mBGTextures )
	{
		bg.mOffset.x += mScrollSpeed * deltaTime;

		if ( bg.mOffset.x < -mScreenSize.x )
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}

}

void BGSpriteComponent::draw( SDL_Renderer* renderer ) noexcept
{
	for ( auto& bg : mBGTextures )
	{
		SDL_Rect rect;

		rect.w = static_cast<int>( mScreenSize.x );
		rect.h = static_cast<int>( mScreenSize.y );
		
		rect.x = static_cast<int>( _owner->getPosition().x - rect.w / 2 + bg.mOffset.x );
		rect.y = static_cast<int>( _owner->getPosition().y - rect.h / 2 + bg.mOffset.y );

		SDL_RenderCopy( 
			renderer,
			bg.mTexture,
			nullptr,
			&rect
		);
	}
}

void BGSpriteComponent::setBGTextures( const std::vector<SDL_Texture*>& textures ) noexcept
{
	int count = 0;
	for ( auto tex : textures )
	{
		BGTexture temp;

		temp.mTexture = tex;
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		
		mBGTextures.emplace_back( temp );
		++count;
	}
}