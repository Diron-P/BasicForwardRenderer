#include "Camera.h"


Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f))
    , MovementSpeed(SPEED)
    , MouseSensitivity(SENSITIVITY)
    , Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, 1.0f))
    , MovementSpeed(SPEED)
    , MouseSensitivity(SENSITIVITY)
    , Zoom(ZOOM)
{
    Position = Vector3(posX, posY, posZ);
    WorldUp = Vector3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::~Camera()
{
}

Matrix44 Camera::GetViewMatrix()
{
    return LookAtRH(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
        Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= MouseSensitivity;
	yOffset *= MouseSensitivity;

	Yaw += xOffset;
	Pitch += yOffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yOffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    Vector3 front;
    front.x = cos(DegToRad(Yaw)) * cos(DegToRad(Pitch));
    front.y = sin(DegToRad(Pitch));
    front.z = sin(DegToRad(Yaw)) * cos(DegToRad(Pitch));
    Normalize(front);
	Front = front;
	// Also re-calculate the Right and Up vector
    Vector3 cross(CrossProduct(Front, WorldUp));
    Normalize(cross);
    Right = cross; // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cross = CrossProduct(Right, Front);
    Normalize(cross);
    Up = cross;
}
