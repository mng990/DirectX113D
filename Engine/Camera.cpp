#include "pch.h"
#include "Camera.h"
#include "Transform.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{

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
	// ī�޶� ��ġ�ϴ� ��ǥ
	Vec3 eyePosition = GetTransform()->GetPosition();
	// ī�޶� �ٶ󺸴� ����
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	// ī�޶��� y ��ǥ(����)
	Vec3 upDirection = GetTransform()->GetUp();
	
	// ��ġ ��ǥ, �ٶ󺸴� ����, orthogonal vector�� ������� ���
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// ī�޶��� ���� ��ǥ�� ���÷� ��ȯ -> �� �����̽�
	// S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
	{
		// ī�޶��� �Կ� ����
		// (pi, ȭ���, �����(near), �ĸ��(far))
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	}
	else
	{
		S_MatProjection = ::XMMatrixOrthographicLH(8, 6, 0.f, 1.f);
	}
}
