#pragma once
#include "pch.h"
#include "IExecute.h"


class LightingDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;

	shared_ptr<GameObject> _camera;
};

