#pragma once
#include "GameObject.h"
class Ship : public GameObject {
	vec3 position;
	vec3 initialPos;
	vec3 forward, up, right;
	float speed;
	float shearAmount;
	float health;
public:
	
	Ship(string const &path, vec3 initialPos = vec3(0, 0, 0)); 
	vec3 getPosition() { return position; }
	void fly() { position += speed * forward; }
	void teleport(vec3 newPos) { position = newPos; }
	vec3 getDirection() { return forward; }
	vec3 getVertical() { return up; }
	void pitch(float angle);
	void roll(float angle);
	void yaw(float angle);
	float getSpeed() { return speed; }
	float getShear() { return shearAmount; }
	float getHealth() { return health; }
	void ResetShip();
	bool IsAlive() { return health > 0; }
	void TakeDamage() { health--; }
	void setSpeed(float newSpeed) { speed += newSpeed; }
	vec3 getMinBox() { return (position + (forward * 5.0f)) - 1.0f; }
	vec3 getMaxBox() { return (position + (forward * 5.0f)) + 1.0f; }
	void Shoot() { shooting = !shooting;  }
	bool shooting;

};

inline Ship::Ship(string const &path, vec3 initialPos) : GameObject(path)
{
	this->initialPos = initialPos;
	position = initialPos;
	forward = vec3(0, 0, -1);
	up = vec3(0, 1, 0);
	right = vec3(1, 0, 0);
	speed = 0.00;
	shearAmount = -0.0001f;
	shooting = false;
	health = 3;
}


inline void Ship::ResetShip()
{
	position = initialPos;
	forward = vec3(0, 0, -1);
	up = vec3(0, 1, 0);
	right = vec3(1, 0, 0);
	speed = 0.01;
	shearAmount = -0.0001f;
	shooting = false;
	health = 3;
}

inline void Ship::pitch(float angle)
{
	forward = normalize(forward * cos(angle) + up * sin(angle));
	up = cross(right, forward);
}

inline void Ship::roll(float angle)
{
	right = normalize(right * cos(angle) + up * sin(angle));
	up = cross(right, forward);
}

inline void Ship::yaw(float angle)
{
	right = normalize(right * cos(angle) + forward * sin(angle));
	forward = cross(up, right);
}
