#pragma once
#include "GameObject.h"
#include <time.h>
#include <stdlib.h> 
#include <glm/gtc/random.hpp>

class Asteroid : public GameObject
{
public:
	Asteroid(string const &path);
	void Move(float dt);
	/* Physics */
	//Primary
	vec3 position;
	vec3 momentum;

	//Secondary
	vec3 velocity;

	//Constants
	float mass;
	float inversemass;

private:
	float speed;
	vec3 direction;
	vec3 RandVec3(float value);
	void Recalculate() { velocity = momentum * inversemass; }
	
	
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

inline Asteroid::Asteroid(string const &path) : GameObject(path)
{
	position = RandVec3(30);
	velocity = normalize(RandVec3(1));
	mass = linearRand(1.0f, 3.0f);
	inversemass = mass / 1;
	momentum = mass * velocity;

	direction = normalize(RandVec3(1));
	speed = linearRand(0.01f, 0.02f);
}

inline vec3 Asteroid::RandVec3(float value)
{
	float x = linearRand(-value, value);
	float y = linearRand(-value, value);
	float z = linearRand(-value, value);
	return vec3(x, y, z);
}