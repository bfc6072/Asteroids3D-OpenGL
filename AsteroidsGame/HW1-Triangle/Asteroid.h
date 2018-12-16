/*
 Authors: Barrington Campbell & Kaloyana Mihova
 Class: IGME.309.03
 Proffesor: David Schwartz

 File Name: Main_Fixed_Data.h
 Description: Stores data neceassry to run the main program. Another level of abstraction to
			  clean up  main.cpp.
*/
#pragma once
#include "GameObject.h"
#include <time.h>
#include <stdlib.h> 
#include <glm/gtc/random.hpp>
#include "Bullet.h"

class Asteroid : public GameObject
{
public:
	Asteroid(string const &path);
	void Move(float dt);
	void Rotate(float dt);
	bool CheckCollision(Ship obj);
	bool CheckBulletCollision(Bullet bullet);
	/* Linear Physics */
	//Primary
	vec3 position;
	vec3 momentum;

	//Secondary
	vec3 velocity;

	//Constants
	float mass;
	float inversemass;

	/* Angular Physics */
	//Primary
	quat orientation;
	vec3 angularMomentum;

	//Secondary
	quat spin;
	vec3 angularVelocity;

	//constant
	float inertia;
	float inverseInertia;
private:
	float speed;
	vec3 direction;
	float radius;
	vec3 RandVec3(float value);
	void RecalcLinearMomentum() { velocity = momentum * inversemass; }
	void RecalcAngularMomentum();
	vec3 torque(float t) { return vec3(1, 0, 0) - angularVelocity * 0.1f; }
	
};

inline void Asteroid::Move(float dt)
{
	if (position.x > 50 || position.x < -50)
		velocity.x *= -1;
	if (position.y > 50 || position.y < -50)
		velocity.y *= -1;
	if (position.z > 50 || position.z < -50)
		velocity.z *= -1;

	position += velocity * dt;
}

inline void Asteroid::Rotate(float dt)
{
	angularVelocity *= dt;
}

inline Asteroid::Asteroid(string const &path) : GameObject(path)
{
	position = RandVec3(30);
	velocity = normalize(RandVec3(1));
	mass = linearRand(1.0f, 3.0f);
	inversemass = mass / 1;
	momentum = mass * velocity;

	angularVelocity = vec3(1, 0, 0);


	direction = velocity;
	speed = linearRand(0.01f, 0.02f);
}

inline bool Asteroid::CheckCollision(Ship ship)
{
	vec3 objMin = ship.getMinBox();
	vec3 objMax = ship.getMaxBox();
	vec3 astMin = position - 2.5f;
	vec3 astMax = position + 2.5f;
	return	(objMin.x <= astMax.x && objMax.x >= astMin.x) &&
			(objMin.y <= astMax.y && objMax.y >= astMin.y) &&
			(objMin.z <= astMax.z && objMax.z >= astMin.z);
}

inline bool Asteroid::CheckBulletCollision(Bullet bullet)
{
	vec3 objMin = bullet.getMinBox();
	vec3 objMax = bullet.getMaxBox();
	vec3 astMin = position - 2.5f;
	vec3 astMax = position + 2.5f;
	return	(objMin.x <= astMax.x && objMax.x >= astMin.x) &&
		(objMin.y <= astMax.y && objMax.y >= astMin.y) &&
		(objMin.z <= astMax.z && objMax.z >= astMin.z);
}

inline void Asteroid::RecalcAngularMomentum()
{
	angularVelocity = angularMomentum * inverseInertia;

	normalize(orientation);

	quat q = quat(0, angularVelocity.x, angularVelocity.y, angularVelocity.z);
	spin = 0.5f * q * orientation;
}

inline vec3 Asteroid::RandVec3(float value)
{
	float x = linearRand(-value, value);
	float y = linearRand(-value, value);
	float z = linearRand(-value, value);
	return vec3(x, y, z);
}