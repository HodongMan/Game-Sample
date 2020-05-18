#include "pch.h"

#include "CircleComponent.h"
#include "Actor.h"


CircleComponent::CircleComponent( Actor* owner )
	:Component( owner )
	, _radius( 0.0f )
{

}

const Vector2& CircleComponent::getCenter( void ) const noexcept
{
	return _owner->getPosition();
}

float CircleComponent::getRadius( void ) const noexcept
{
	return _owner->getScale() * _radius;
}

bool Intersect( const CircleComponent& lhs, const CircleComponent& rhs ) noexcept
{
	const Vector2 diff	= lhs.getCenter() - rhs.getCenter();
	float distSq		= diff.LengthSq();

	float radiiSq		= lhs.getRadius() + rhs.getRadius();
	radiiSq				*= radiiSq;

	return distSq <= radiiSq;
}