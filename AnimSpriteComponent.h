#pragma once

#include "SpriteComponent.h"
#include <vector>

class Actor;

class AnimSpriteComponent : public SpriteComponent
{
public:

	AnimSpriteComponent( Actor* owner, int drawOrder = 100 );

	void update( float deltaTime ) noexcept override;
	void setAnimTextures( const std::vector<SDL_Texture*>& textures ) noexcept;
	
	float getAnimFPS( void ) const noexcept { return mAnimFPS; }
	void setAnimFPS( float fps ) noexcept { mAnimFPS = fps; }

private:

	std::vector<SDL_Texture*> mAnimTextures;

	float mCurrentFrame;
	float mAnimFPS;
};