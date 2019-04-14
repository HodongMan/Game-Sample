#include "CircleComponent.h"
#include "Actor.h"


CircleComponent::CircleComponent( Actor* owner )
	:Component( owner )
	, mRadius( 0.0f )
{

}

const Vector2& CircleComponent::getCenter( void ) const noexcept
{
	return mOwner->getPosition();
}

float CircleComponent::getRadius( void ) const noexcept
{
	return mOwner->getScale() * mRadius;
}

bool Intersect( const CircleComponent& lhs, const CircleComponent& rhs ) noexcept
{
	const Vector2 diff	= lhs.getCenter() - rhs.getCenter();
	float distSq		= diff.LengthSq();

	float radiiSq		= lhs.getRadius() + rhs.getRadius();
	radiiSq				*= radiiSq;

	return distSq <= radiiSq;
}