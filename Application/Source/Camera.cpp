#include "Camera.h"
#include "Application.h"
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
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
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	if (Application::IsKeyPressed('A'))
	{
		this->position.x -= 10.f * dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		this->position.x += 10.f * dt;
	}
	if (Application::IsKeyPressed('W'))
	{
		this->position.y -= 10.f * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		this->position.y += 10.f * dt;
	}
}