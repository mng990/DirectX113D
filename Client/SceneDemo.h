#pragma once
#include "IExecute.h"

class SceneDemo : public IExecute
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	shared_ptr<Shader> _shader;
	vector<shared_ptr<GameObject>> _objs;
	shared_ptr<GameObject> _camera;
};

