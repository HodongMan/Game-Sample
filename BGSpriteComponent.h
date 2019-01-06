#pragma once

#include "TypeComponent.h"
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"


class Actor;

class BGSpriteComponent : public SpriteComponent
{
public:

	BGSpriteComponent( Actor* owner, int drawOrder = 10 );

	void update( float deltaTime ) noexcept override;
	void draw( SDL_Renderer* renderer ) noexcept override;

	void setBGTextures( const std::vector<SDL_Texture*>& textures ) noexcept;

	void setScreenSize( const Vector2& size ) noexcept { mScreenSize = size; }
	void setScrollSpeed( float speed ) { mScrollSpeed = speed; }
	
	float getScrollSpeed( void ) const noexcept { return mScrollSpeed; }

private:

	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;

};