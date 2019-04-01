#pragma once

#include <random>
#include "Math.h"


class Random
{
public:

	static void			init( void ) noexcept;

	static void			seed( unsigned int seed ) noexcept;

	static float		getFloat( void ) noexcept;

	static float		getFloatRange( const float min, const float max ) noexcept;

	static int			getIntRange( const int min, const int max ) noexcept;

	static Vector2		getVector( const Vector2& min, const Vector2& max ) noexcept;
	static Vector3		getVector( const Vector3& min, const Vector3& max ) noexcept;

private:
	static std::mt19937	sGenerator;


};