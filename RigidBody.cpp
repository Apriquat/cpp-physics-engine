#include "RigidBody.h"
#include "Vec2.h"

Vec2* gravAcc = new Vec2(0.0f, 750.0f);

RigidBody::RigidBody(Vec2* pos, float radius, std::vector<RigidBody*>* parent)
{
	this->m_pos = pos;
	this->m_lastPos = new Vec2(pos->x, pos->y);
	this->m_radius = radius;

	this->m_acc = new Vec2(0.0f, 0.0f);
	this->m_vel = new Vec2(0.0f, 0.0f);

	this->constraintCoord = new Vec2(300.0f, 200.0f);
	this->constraintR = 150.0f;

	this->m_parent = parent;

	parent->push_back(this);
}

void RigidBody::update(float dt)
{
	// Apply acceleration forces
	this->accelerate(gravAcc);
	//std::cout << this->m_acc->mag << "\n";

	// Apply constraints
	this->applyConstraints();

	// Solve collisions
	this->solveCollisions();

	// Verlet integration
	this->m_vel->setAndDelete(Vec2::sub(this->m_pos, this->m_lastPos));

	this->m_lastPos->set(this->m_pos);

	this->m_pos->setAndDelete(Vec2::addAndDelete(Vec2::add(this->m_pos, this->m_vel), Vec2::mult(this->m_acc, dt * dt), true));
	//std::cout << dt;

	this->m_acc->set(0.0f, 0.0f);

	this->draw();
}

void RigidBody::accelerate(Vec2* acc)
{
	this->m_acc->setAndDelete(Vec2::add(this->m_acc, acc));
}

void RigidBody::applyConstraints()
{
	Vec2* dstVec = Vec2::sub(this->m_pos, constraintCoord);
	if (dstVec->mag > constraintR - this->m_radius)
	{
		Vec2* n = Vec2::normalize(dstVec);
		this->m_pos->setAndDelete(Vec2::addAndDelete(constraintCoord, Vec2::mult(n, constraintR - this->m_radius), false));

		delete(n);
	}
	delete(dstVec);
}

void RigidBody::solveCollisions()
{
	for (int i = 0; i < m_parent->size(); i++)
	{
		RigidBody* other = (*m_parent)[i];
		if (other == this)
			continue;

		Vec2* collisionAxis = Vec2::sub(this->m_pos, other->m_pos);
		if (collisionAxis->mag < this->m_radius + other->m_radius)
		{
			Vec2* n = Vec2::normalize(collisionAxis);
			float delta = this->m_radius + other->m_radius - collisionAxis->mag;
			this->m_pos->setAndDelete(Vec2::addAndDelete(this->m_pos, Vec2::mult(n, 0.5f * delta), false));
			other->m_pos->setAndDelete(Vec2::subAndDelete(other->m_pos, Vec2::mult(n, 0.5f * delta), false));

			delete(n);
		}
		delete(collisionAxis);
	}
}

void RigidBody::draw()
{

}