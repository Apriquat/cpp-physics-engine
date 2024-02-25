#include "Vec2.h"

Vec2::Vec2(float _x, float _y)
{
	x = _x;
	y = _y;
	mag = sqrt((x * x) + (y * y));
}
Vec2::Vec2(float _x, float _y, Vec2* del)
{
	x = _x;
	y = _y;
	mag = sqrt(x * x + y * y);

	delete(del);
}
Vec2::Vec2(float _x, float _y, Vec2* del0, Vec2* del1)
{
	x = _x;
	y = _y;
	mag = sqrt(x * x + y * y);

	delete(del0);
	delete(del1);
}

Vec2* Vec2::add(Vec2* v0, Vec2* v1)
{
	return new Vec2(v0->x + v1->x, v0->y + v1->y);
}
Vec2* Vec2::add(Vec2* v0, float f)
{
	return new Vec2(v0->x + f, v0->y + f);
}
Vec2* Vec2::addAndDelete(Vec2* v0, Vec2* v1, bool both=false)
{
	if (both)
		return new Vec2(v0->x + v1->x, v0->y + v1->y, v0, v1);
	return new Vec2(v0->x + v1->x, v0->y + v1->y, v1);
}

Vec2* Vec2::sub(Vec2* v0, Vec2* v1)
{
	return new Vec2(v0->x - v1->x, v0->y - v1->y);
}
Vec2* Vec2::sub(Vec2* v0, float f)
{
	return new Vec2(v0->x - f, v0->y - f);
}
Vec2* Vec2::subAndDelete(Vec2* v0, Vec2* v1, bool both=false)
{
	if (both)
		return new Vec2(v0->x - v1->x, v0->y - v1->y, v0, v1);
	return new Vec2(v0->x - v1->x, v0->y - v1->y, v1);
}

Vec2* Vec2::mult(Vec2* v0, float f)
{
	return new Vec2(v0->x * f, v0->y * f);
}

Vec2* Vec2::normalize(Vec2* vec0)
{
	if (vec0->mag == 0)
		return new Vec2(0.0f, 0.0f);

	return new Vec2(vec0->x / vec0->mag, vec0->y / vec0->mag);
}

void Vec2::set(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
	this->mag = sqrt(this->x * this->x + this->y * this->y);
}
void Vec2::set(Vec2* v0)
{
	this->x = v0->x;
	this->y = v0->y;
	this->mag = v0->mag;
}
void Vec2::setAndDelete(Vec2* v0)
{
	this->x = v0->x;
	this->y = v0->y;
	this->mag = v0->mag;

	delete(v0);
}

void Vec2::addTo(float f)
{
	this->x += f;
	this->y += f;
}
void Vec2::addTo(Vec2* v0)
{
	this->x += v0->x;
	this->y += v0->y;
}

void Vec2::addToAndDelete(Vec2* v0)
{
	this->x += v0->x;
	this->y += v0->y;

	delete(v0);
}

void Vec2::cleanup(Vec2* vecs[])
{
	int len = *(&vecs + 1) - vecs;
	for (int i = 0; i < len; i++)
	{
		delete(vecs[i]);
	}

	delete(vecs);
}