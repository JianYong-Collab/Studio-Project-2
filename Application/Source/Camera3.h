#ifndef CAMERA3_H
#define CAMERA3_H
#include "Application.h"
#include "Vector3.h"

class Camera3
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 defaultTarget;
	Vector3 defaultPosition;
	Vector3 defaultUp;
	Vector3 view;
	Vector3 right;
	double posx;
	double posy;
	float yaw;
	float pitch;

	Camera3();
	~Camera3();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
};

#endif