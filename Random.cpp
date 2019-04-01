#include "Random.h"


void Random::init( void ) noexcept
{
	std::random_device	rd;
	Random::seed( rd() );
}

void Random::seed( unsigned int seed ) noexcept
{
	sGenerator.seed( seed );
}

float Random::getFloat( void ) noexcept
{
	return getFloatRange( 0.0f, 1.0f );
}

float Random::getFloatRange( const float min, const float max ) noexcept
{
	std::uniform_real_distribution<float> dist( min, max );

	return dist( sGenerator );
}

int Random::getIntRange( const int min, const int max ) noexcept
{
	std::uniform_real_distribution<int> dist( min, max );

	return dist( sGenerator );
}

Vector2 Random::getVector( const Vector2& min, const Vector2& max ) noexcept
{
	Vector2 rangeVector = Vector2( getFloat(), getFloat() );
	return min + ( max - min ) * rangeVector;
}

Vector3 Random::getVector( const Vector3& min, const Vector3& max ) noexcept
{
	Vector3 rangeVector = Vector3( getFloat(), getFloat(), getFloat() );
	return min + ( max - min ) * rangeVector;
}

std::mt19937 Random::sGenerator;