#pragma once

#include "Component.h"
#include "SDL.h"

class Actor;

class SpriteComponent : public Component
{
public:

	SpriteComponent( Actor* owner, int drawOrder = 100 );
	~SpriteComponent();

	virtual void draw( SDL_Renderer* renderer ) noexcept;
	virtual void setTexture( SDL_Texture* texture ) noexcept;

	int getDrawOrder( void ) const noexcept { return mDrawOrder; };
	int getTexHeight( void ) const noexcept { return mTexHeight; };
	int getTexWidth( void ) const noexcept { return mTexWidth; }; 

protected:

	SDL_Texture * mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};