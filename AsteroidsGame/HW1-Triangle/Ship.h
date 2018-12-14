#pragma once
#include "GameObject.h"
class Ship : public GameObject {
	vec3 position;
	vec3 forward, up, right;
	float speed;
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
	void setSpeed(float newSpeed) { speed += newSpeed; }
};

inline Ship::Ship(string const &path, vec3 initialPos) : GameObject(path)
{
	position = initialPos;
	forward = vec3(0, 0, -1);
	up = vec3(0, 1, 0);
	right = vec3(1, 0, 0);
	speed = 0.01;
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