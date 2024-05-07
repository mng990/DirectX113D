#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height = static_cast<float>(GAME->GetGameDesc().height);
}

Camera::~Camera()
{
	
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection = GetTransform()->GetUp();
	
	// 위치 좌표, 바라보는 방향, orthogonal vector를 기반으로 계산
	_matView = S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// 카메라의 월드 좌표 x 월드 매트릭스의 역행렬 
	// -> 카메라의 월드 좌표를 로컬로 변환 -> View Space
	// S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
	{
		// 카메라의 촬영 영역
		// (pi, 화면비, 전면부(near), 후면부(far))
		_matProjection = S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	}
	else
	{
		_matProjection = S_MatProjection = ::XMMatrixOrthographicLH(8, 6, 0.f, 1.f);
	}
}
