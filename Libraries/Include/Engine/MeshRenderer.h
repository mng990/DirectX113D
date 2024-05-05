#pragma once
#include "Component.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "InstancingBuffer.h"

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	void SetPass(uint8 pass) { _pass = pass; }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	InstanceID GetInstanceID() { return make_pair((uint64)_mesh.get(), (uint64)_material.get()); };

	void RenderInstancing(shared_ptr<InstancingBuffer>& buffer);
private:
	// Mesh
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
	uint8 _pass = 0;
};

