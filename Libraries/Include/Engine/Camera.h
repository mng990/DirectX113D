#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective, // 원근 투영
	Orthographic, // 직교 투영
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetProjectionType() { return _type; }

	void UpdateMatrix();

	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFov(float value) { _fov = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }
	
	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }

private:
	ProjectionType _type = ProjectionType::Perspective;
	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;


	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

