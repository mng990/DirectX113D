#pragma once
#include "Component.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override;

	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }

	// Legacy
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }
	void SetShader(shared_ptr<Shader> shader) { _shader = shader; }
	void SetPass(uint8 pass) { _pass = pass; }

private:
	// Mesh
	shared_ptr<Mesh> _mesh;
	shared_ptr<Texture> _texture;
	shared_ptr<Shader> _shader;
	shared_ptr<Material> _material;
	uint8 _pass = 0;
};

