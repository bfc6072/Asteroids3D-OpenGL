/*
Authors: Barrington Campbell & Kaloyana Mihova
Class: IGME.309.03
Proffesor: David Schwartz

File Name: Bullet.h
Description: Bullet class manages individual bullet movement and lifespan
*/
#pragma once
#include "GameObject.h"
class Bullet : public GameObject 
{
	vec3 position;		//Current positoin
	vec3 forward;		//Forward direction
	float speed;		//Current speed
	float lifeStart;	//Time when the bullet is instantiated
	float lifeEnd;		//Time inwhich the bolt should be destroyed
public:
	Bullet(string const &path, vec3 initialPos, vec3 forward, float time);
	vec3 GetMinBox() { return position - .5f; }	//Minimum vec3 positions for AABB
	vec3 GetMaxBox() { return position + .5f; } //Maximum vec3 positions for AABB
	vec3 GetPosition() { return position; }
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