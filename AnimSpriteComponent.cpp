#include "AnimSpriteComponent.h"
#include "Math.h"


AnimSpriteComponent::AnimSpriteComponent( Actor* owner, int drawOrder )
	: SpriteComponent( owner, drawOrder )
	, mCurrentFrame( 0.0f )
	, mAnimFPS( 24.0f )
{
	
}

void AnimSpriteComponent::update( float deltaTime ) noexcept
{
	SpriteComponent::update( deltaTime );

	if ( 0 < mAnimTextures.size() )
	{
		mCurrentFrame += mAnimFPS * deltaTime;

		while ( mAnimTextures.size() <= mCurrentFrame )
		{
			mCurrentFrame -= mAnimTextures.size();
		}

		setTexture( mAnimTextures[ static_cast<int>( mCurrentFrame ) ] );
	}
}

void AnimSpriteComponent::setAnimTextures( const std::vector<SDL_Texture*>& textures ) noexcept
{
	mAnimTextures = textures;

	if ( 0 < mAnimTextures.size() )
	{
		mCurrentFrame = 0.0f;
		setTexture( mAnimTextures[0] );
	}
}