#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2 pos = { 0, 0 };
	Vec2 velocity = { 0, 0 };
	float angle = 0;

	CTransform(const Vec2& inpos, const Vec2& invelocity, float inangle)
		:	pos(inpos), velocity(invelocity), angle(inangle)
	{}
};

class CShape
{
public:
	sf::CircleShape shape;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float outlineThickness)
		: shape(radius, points)
	{
		shape.setFillColor(fill);
		shape.setOutlineColor(outline);
		shape.setOutlineThickness(outlineThickness);
		shape.setOrigin(radius, radius);
	}

	CShape(sf::CircleShape shape)
	{
		this->shape = shape;
	}
};

class CCollision
{
public:
	float radius;

	CCollision(float inradius)
		: radius(inradius)
	{}
};

class CEnemy
{
public:
	float score;
	bool dividable;

	CEnemy(float inscore, float individable = true)
		: score(inscore), dividable(individable)
	{}
};

class CLifespan
{
public:
	int remaining	= 0;	// Remaining frames to live
	int total		= 0;	// Total frames to live

	CLifespan(int intotal)
		: remaining(intotal), total(intotal)
	{}
};

class CInput
{
public:
	bool up		= false;
	bool down	= false;
	bool left	= false;
	bool right	= false;
	bool mouse	= false;

	CInput()
	{}
};
