#pragma once
#include "IExecute.h"

class MeshInstancingDemo : public IExecute
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	shared_ptr<Shader> _shader;
	shared_ptr<GameObject> _camera;
	vector<shared_ptr<GameObject>> _objs;

private:
	// INSTANCING
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;

	vector<Matrix> _worlds;
	shared_ptr<VertexBuffer> _instanceBuffer;

};

