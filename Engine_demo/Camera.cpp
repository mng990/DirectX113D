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
	
	// ��ġ ��ǥ, �ٶ󺸴� ����, orthogonal vector�� ������� ���
	_matView = S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// ī�޶��� ���� ��ǥ x ���� ��Ʈ������ ����� 
	// -> ī�޶��� ���� ��ǥ�� ���÷� ��ȯ -> View Space
	// S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
	{
		// ī�޶��� �Կ� ����
		// (pi, ȭ���, �����(near), �ĸ��(far))
		_matProjection = S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	}
	else
	{
		_matProjection = S_MatProjection = ::XMMatrixOrthographicLH(8, 6, 0.f, 1.f);
	}
}
