#pragma once
#include "GameObject.h"
class Bullet : public GameObject 
{
	vec3 position;
	vec3 forward;
	float speed;
	float lifeStart;
	float lifeEnd;
public:
	Bullet(string const &path, vec3 initialPos, vec3 forward, float time);
	vec3 getMinBox() { return position - .5f; }
	vec3 getMaxBox() { return position + .5f; }
	vec3 getPosition() { return position; }
	bool Fly(float time);
};

inline Bullet::Bullet(string const &path, vec3 initialPos, vec3 forward, float time) : GameObject(path)
{
	lifeStart = time;
	lifeEnd = time + 5.0f;
	this->forward = forward;
	position = initialPos + (forward * 5.0f);
	speed = 1;
}

inline bool Bullet::Fly(float time)
{
	if (time > lifeEnd)
	{
		return true;
	}
	else
	{
		position += speed * forward;
		return false;
	}
}