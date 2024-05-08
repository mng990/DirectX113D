#pragma once
#include "IExecute.h"
#include "MonoBehaviour.h"

class OrthographicDemo: public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<Shader> _shader;
};