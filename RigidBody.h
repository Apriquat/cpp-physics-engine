#pragma once
#include "Vec2.h"
#include <vector>

class RigidBody
{
public:

	Vec2* m_pos;
	Vec2* m_lastPos;
	float m_radius;

	Vec2* m_acc;
	Vec2* m_vel;

	Vec2* constraintCoord;
	float constraintR;

	std::vector<RigidBody*>* m_parent;

	RigidBody(Vec2* pos, float radius, std::vector<RigidBody*>* parent);

	void update(float dt);
	void accelerate(Vec2* acc);
	void applyConstraints();
	void solveCollisions();

	void draw();
};