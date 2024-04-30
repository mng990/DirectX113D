#pragma once
#include "pch.h"
#include "IExecute.h"
#include "Geometry.h"
#include "VertexData.h"
#include "GameObject.h"


class NormalDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;

	// Object
	shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	Matrix _world = Matrix::Identity;
	Matrix _view = Matrix::Identity;
	Matrix _projection = Matrix::Identity;

	// Camera
	shared_ptr<GameObject> _camera;
	shared_ptr<Texture> _texture;

	Vec3 _lightDir = Vec3(0.f, 0.f, 1.f);

};

