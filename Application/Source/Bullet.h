#pragma once
#include "Vertex.h"

struct Bullet
{
public:
	Vector3 BulletPos;
	Vector3 Direction;
	double Lifetime;
	Vector3 target;
	Vector3 up;
	Vector3 defaultTarget;
	Vector3 defaultPosition;
	Vector3 defaultUp;
	Vector3 defaultView;
	Vector3 view;
	Vector3 right;



void Update(double dt)
{
	BulletPos.x += Direction.x * 500 * dt;
	BulletPos.y += Direction.y * 500 * dt;
	BulletPos.z += Direction.z * 500 * dt;
	
}
};

Bullet* BulletArray[100];

