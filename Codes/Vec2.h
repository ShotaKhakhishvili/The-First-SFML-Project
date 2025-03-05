#pragma once
#include <cmath>
#include "Extra.h"

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float xin, float yin);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const Vec2& rhs) const;
	Vec2 operator / (const Vec2& rhs) const;

	Vec2 operator + (const float value) const;
	Vec2 operator - (const float value) const;
	Vec2 operator * (const float value) const;
	Vec2 operator / (const float value) const;

	Vec2& operator += (const Vec2& rhs);
	Vec2& operator -= (const Vec2& rhs);
	Vec2& operator *= (const Vec2& rhs);
	Vec2& operator /= (const Vec2& rhs);

	Vec2& operator += (const float value);
	Vec2& operator -= (const float value);
	Vec2& operator *= (const float value);
	Vec2& operator /= (const float value);

	Vec2& operator = (const float value);
	Vec2& operator = (const Vec2& rhs);

	float dist(const Vec2& other) const;
	float distSqr(const Vec2& other) const;
	float length() const;

	float dot(const Vec2& other) const;

	Vec2 normalized() const;
	Vec2& normalize();

	Vec2 rotated(float degree) const;
	Vec2& rotate(float degree);
};