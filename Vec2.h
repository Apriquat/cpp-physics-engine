#pragma once
#include <iostream>
#include <cmath>


class Vec2
{
public:
	Vec2(float _x, float _y);
	Vec2(float _x, float _y, Vec2* del);
	Vec2(float _x, float _y, Vec2* del0, Vec2* del1);

	static Vec2* add(Vec2* v0, Vec2* v1);
	static Vec2* add(Vec2* v0, float f);
	static Vec2* addAndDelete(Vec2* v0, Vec2* v1, bool both);

	static Vec2* sub(Vec2* v0, Vec2* v1);
	static Vec2* sub(Vec2* v0, float f);
	static Vec2* subAndDelete(Vec2* v0, Vec2* v1, bool both);

	static Vec2* mult(Vec2* v0, float f);

	static Vec2* normalize(Vec2* v0);

	void set(float _x, float _y);
	void set(Vec2* v0);
	void setAndDelete(Vec2* v0);

	void addTo(float f);
	void addTo(Vec2* v0);
	void addToAndDelete(Vec2* v0);

	Vec2* operator+(Vec2* other) const
	{
		return new Vec2(x + other->x, y + other->y);
	}

	float mag;
	float x;
	float y;

private:
	static void cleanup(Vec2* vecs[]);

};