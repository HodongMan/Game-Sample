#pragma once
#include "Component.h"
#include "Math.h"


class Actor;

class CircleComponent : public Component
{
public:
	CircleComponent( Actor* owner );

	void setRadius( float radius ) noexcept { mRadius = radius; }
	float getRadius( void ) const noexcept;
	
	const Vector2& getCenter( void ) const noexcept;

private:
	float mRadius;
};

bool Intersect( const CircleComponent& lhs, const CircleComponent& rhs ) noexcept;