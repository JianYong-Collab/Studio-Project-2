#pragma once
#include "Vertex.h"
#include "Vector3.h"
#include <cmath>
using namespace std;
struct Enemy
{
	float EnemyHp;
	float Hypotenuse;
	float dirx;
	float diry;
	float dirz;
	float RotateDir;
	Vector3 EnemyPos;
	Vector3 target;
	Vector3 up;
	Vector3 defaultTarget;
	Vector3 defaultPosition;
	Vector3 defaultUp;
	Vector3 defaultView;
	Vector3 view;
	Vector3 right;
	Vector3 Direction;
	double yaw;
	float xdist;
	float ydist;
	float zdist;
	bool NearItem = false;
	bool Alive = true;
	bool PickUpItem = false;
public:
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up) 
	{
		EnemyPos = defaultPosition = pos;
		this->target = defaultTarget = target;
		defaultView=(target - EnemyPos).Normalized();
		view= (target - EnemyPos).Normalized();
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		this->up = defaultUp = right.Cross(view).Normalized();
		/*float dot = (view.x * defaultView.x) + (view.z * defaultView.z);
		float det = (view.x + defaultView.z) + (defaultView.z * view.x);
		yaw = atan2(dot, det);*/
		yaw = 0;
		/*xdist = (EnemyPos.x - target.x);
		ydist = (EnemyPos.y - target.y);
		zdist = (EnemyPos.z - target.z);
		Hypotenuse = sqrt(xdist * xdist) + sqrt(ydist * ydist) + sqrt(zdist * zdist);*/
		Direction = (target - EnemyPos).Normalized();

	}
	void Update(double dt, Vector3 Cameraposition)
	{
		target = Cameraposition;
		view = (target - EnemyPos).Normalized();
		// Viewing
		float dot = (target.z - EnemyPos.z);
		float det = (target.x - EnemyPos.x);
		yaw = Math::RadianToDegree(atan2(det, dot));

		Direction = (target - EnemyPos).Normalized();
		EnemyPos.x += Direction.x * 20 * dt;
		/*EnemyPos.y += Direction.y * 20 * dt;*/
		EnemyPos.z += Direction.z * 20 * dt;
		
	}
	float GetYaw()
	{
		return yaw;
	}
};

Enemy* EnemyArray[10];
