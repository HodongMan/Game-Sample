#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{
	const float PI = 3.1415926535f;
	const float TwoPI = PI * 2.0f;
	const float PIOver2 = PI / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadius( float degrees ) noexcept
	{
		return degrees * PI / 180.0f;
	}

	inline float ToDegrees( float radius ) noexcept
	{
		return radius * 180.0f / PI;
	}

	inline bool NearZero ( float val, float epsilon = 0.001f ) noexcept
	{
		if ( fabs( val ) <= epsilon )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max( const T& a, const T& b ) noexcept
	{
		return ( a < b ? b : a );
	}

	template <typename T>
	T Min( const T& a, const T& b) noexcept
	{
		return ( a < b ? a : b );
	}

	template <typename T>
	T Clamp( const T& value, const T& lower, const T& upper ) noexcept
	{
		return Min( upper, Max( lower, value ) );
	}

	inline float Abs( float value ) noexcept
	{
		return fabs( value );
	}

	inline float Cos( float angle ) noexcept
	{
		return cosf( angle );
	}

	inline float Sin( float angle ) noexcept
	{
		return sinf( angle );
	}

	inline float Tan( float angle ) noexcept
	{
		return tanf( angle );
	}

	inline float Acos( float value ) noexcept
	{
		return acosf( value );
	}

	inline float Atan2( float x, float y ) noexcept
	{
		return atan2f( x, y );
	}

	inline float Cot( float angle ) noexcept
	{
		return 1.0f / Tan( angle );
	}

	inline float Lerp( float a, float b, float f ) noexcept
	{
		return a + f * ( b - a );
	}

	inline float Sqrt( float value ) noexcept
	{
		return sqrtf( value );
	}

	inline float Fmod( float number, float demon ) noexcept
	{
		return fmod( number, demon );
	}
}

class Vector2
{
public:

	float x;
	float y;

	Vector2() noexcept
		: x( 0.0f )
		, y( 0.0f )
	{
		
	}

	explicit Vector2( float inX, float inY ) noexcept
		: x( inX )
		, y( inY )
	{
	
	}

	void Set( float inX, float inY ) noexcept
	{
		x = inX;
		y = inY;
	}

	friend Vector2 operator+( const Vector2& lhs, const Vector2& rhs ) noexcept
	{
		return Vector2( lhs.x + rhs.x, lhs.y + rhs.y );
	}

	friend Vector2 operator-( const Vector2& lhs, const Vector2& rhs ) noexcept
	{
		return Vector2( lhs.x - rhs.x, lhs.y - rhs.y);
	}

	friend Vector2 operator*( const Vector2& lhs,  const Vector2& rhs ) noexcept
	{
		return Vector2( lhs.x * rhs.x, lhs.y * rhs.y);
	}

	friend Vector2 operator*( const Vector2& vec, float scalar ) noexcept
	{
		return Vector2( vec.x * scalar, vec.y * scalar );
	}

	friend Vector2 operator*( float scalar, const Vector2& vec ) noexcept
	{
		return Vector2( vec.x * scalar, vec.y * scalar );
	}

	Vector2& operator*=( float scalar ) noexcept
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator+=(const Vector2& rhs ) noexcept
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator-=( const Vector2& rhs ) noexcept
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	float LengthSq() const noexcept
	{
		return ( x * x + y * y );
	}

	float Length() const noexcept
	{
		return ( Math::Sqrt( LengthSq() ) );
	}

	void Normalize() noexcept
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	static Vector2 Normalize( const Vector2& vec ) noexcept
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	static float Dot( const Vector2& lhs, const Vector2& rhs ) noexcept
	{
		return ( lhs.x * rhs.x + lhs.y * rhs.y );
	}

	static Vector2 Lerp( const Vector2& lhs, const Vector2& rhs, float f ) noexcept
	{
		return Vector2( lhs + f * ( rhs - lhs ) );
	}

	static Vector2 Reflect( const Vector2& lhs, const Vector2& rhs ) noexcept
	{
		return lhs - 2.0f * Vector2::Dot( lhs, rhs ) * rhs;
	}

	static Vector2 Transform( const Vector2& vec, const class Matrix3& mat, float w = 1.0f ) noexcept;

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};

class Vector3
{
public:
	float x;
	float y;
	float z;
};