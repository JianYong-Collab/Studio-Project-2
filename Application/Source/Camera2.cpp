#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera2::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 20.0f;
	if (Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		// Create a Rotation Matrix
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
		position = rotation * position; //p' =[R]p
		up = rotation * up;
	}
	if (Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		// Create a Rotation Matrix
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		position = rotation * position; //p' =[R]p
		up = rotation * up;
	}
	if (Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		right.y = 0;
		right.Normalized();
		// Create a Rotation Matrix
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
		position = rotation * position; //p' =[R]p
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up).Normalized();
		right.y = 0;
		right.Normalized();
		// Create a Rotation Matrix
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		position = rotation * position; //p' =[R]p
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('N'))
	{
		Vector3 view = (target - position).Normalized();
		position += view * CAMERA_SPEED* dt;
	}
	if (Application::IsKeyPressed('M'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * CAMERA_SPEED * dt;
	}
}