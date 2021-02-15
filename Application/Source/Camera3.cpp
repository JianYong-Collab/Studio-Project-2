#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
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
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
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
void Camera3::Reset()
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
void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 1.5f;
	static const float ZOOM_SPEED = 80.0f;
	view = (target - position).Normalized();
	right = view.Cross(up);
	static const float rotational_speed = 45.0f;
	yaw = ZOOM_SPEED * static_cast<float>(dt);
	pitch = ZOOM_SPEED * static_cast<float>(dt);
	
	if (Application::IsKeyPressed('A'))
	{
		//view = (target - position).Normalized();
		//right = view.Cross(up).Normalized();
		//// Create a Rotation Matrix
		//Mtx44 rotation;
		//rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		//view = rotation * view; //p' =[R]p
		//target = position + view;
		//up = rotation * up;

		position -= right * CAMERA_SPEED;
		target = position + view;
		if(!((position.x >= -500 && position.x <= 500) && (position.z >= -500 && position.z <= 500)))
		{
			position += right * CAMERA_SPEED;
			target = position + view;
		}
		
	}
	if (Application::IsKeyPressed('D'))
	{
		//view = (target - position).Normalized();
		//right = view.Cross(up).Normalized();
		//// Create a Rotation Matrix
		//Mtx44 rotation;
		//rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
		//view = rotation * view; //p' =[R]p
		//target = position + view;
		//up = rotation * up;
		position += right * CAMERA_SPEED;
		target = position + view;
		if (!((position.x >= -500 && position.x <= 500) && (position.z >= -500 && position.z <= 500)))
		{
			position -= right * CAMERA_SPEED;
			target = position + view;
		}
	}
	if (Application::IsKeyPressed('N'))
	{
		//view = (target - position).Normalized();
		//Vector3 right = view.Cross(up).Normalized();
		//right.y = 0;
		//right.Normalized();
		//up = right.Cross(view).Normalized();
		//// Create a Rotation Matrix
		//Mtx44 rotation;
		//rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		//view = rotation * view; //p' =[R]p
		//target = position + view;

		position += up;
		target = position + view;
	}
	if (Application::IsKeyPressed('M'))
	{
		//view = (target - position).Normalized();
		//Vector3 right = view.Cross(up).Normalized();
		//right.y = 0;
		//right.Normalized();
		//up = right.Cross(view).Normalized();
		//// Create a Rotation Matrix
		//Mtx44 rotation;
		//rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z); 
		//view = rotation * view; //p' =[R]p
		//target = position + view;


		position -= up;
		target = position + view;
	}
	if (Application::IsKeyPressed('W'))
	{
		position.x += view.x * ZOOM_SPEED * dt;
		position.z += view.z * ZOOM_SPEED * dt;
		target = position + view;
		if (!((position.x >= -500 && position.x <= 500) && (position.z >= -500 && position.z <= 500)))
		{
			position.x -= view.x * ZOOM_SPEED * dt;
			position.z -= view.z * ZOOM_SPEED * dt;
			target = position + view;
		}
		
		
	}
	if (Application::IsKeyPressed('S'))
	{
		position.x -= view.x * ZOOM_SPEED * dt;
		position.z -= view.z * ZOOM_SPEED * dt;
		target = position + view;
		if (!((position.x >= -500 && position.x <= 500) && (position.z >= -500 && position.z <= 500)))
		{
			position.x += view.x * ZOOM_SPEED * dt;
			position.z += view.z * ZOOM_SPEED * dt;
			target = position + view;
		}
		
	}
	if (Application::IsKeyPressed(0x28)) // up
	{
		

		//view = (target - position).Normalized();
		//Vector3 right = view.Cross(up);
		//position -= up;
		//target = position + view;
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;

	}
	if (Application::IsKeyPressed(0x25)) // left
	{
		
		/*view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		position -= right * CAMERA_SPEED * dt;
		target = position + view;*/
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(0x26)) // down
	{
		

	//	view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up);
	//	position += up;
	//	target = position + view;
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}

	if (Application::IsKeyPressed(0x27)) // right
	{
		
		/*view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		position += right * CAMERA_SPEED * dt;
		target = position + view;*/
		view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}

	//up = defaultUp = right.Cross(view).Normalized();
	Application::GetCursorPos(&posx, &posy);
	// Left
	//if (posx/10 <= 45)
	//{
	//	posx = 450;
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up).Normalized();
	//	// Create a Rotation Matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(CAMERA_SPEED* dt, 0, 1, 0);
	//	view = rotation * view; //p' =[R]p
	//	target = position + view;
	//	up = rotation * up;
	//}
	//// Right
	//if (posx/10 >= 135 )
	//{
	//	posx = 1350;
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up).Normalized();
	//	// Create a Rotation Matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
	//	view = rotation * view; //p' =[R]p
	//	target = position + view;
	//	up = rotation * up;
	//}
	//// UP
	//if (posy/10 <= 27)
	//{
	//	posy = 270;
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up).Normalized();
	//	right.y = 0;
	//	right.Normalized();
	//	up = right.Cross(view).Normalized();
	//	// Create a Rotation Matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(CAMERA_SPEED* dt, right.x, right.y, right.z);
	//	view = rotation * view; //p' =[R]p
	//	target = position + view;
	//}
	//// Down
	//if (posy/10 >= 81)
	//{
	//	posy = 810;
	//	Vector3 view = (target - position).Normalized();
	//	Vector3 right = view.Cross(up).Normalized();
	//	right.y = 0;
	//	right.Normalized();
	//	up = right.Cross(view).Normalized();
	//	// Create a Rotation Matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
	//	view = rotation * view; //p' =[R]p
	//	target = position + view;
	//	
	//}
}
