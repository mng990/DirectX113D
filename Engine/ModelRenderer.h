#pragma once
#include "Component.h"
#include "Shader.h"
#include "Model.h"


class ModelRenderer : public Component
{
	using Super = Component;

public:
	ModelRenderer(shared_ptr<Shader> shader);
	~ModelRenderer();

	void SetModel(shared_ptr<Model> model);
	void SetPass(uint8 pass) { _pass = pass; }

	void RenderInstancing(shared_ptr<InstancingBuffer>& buffer);
	InstanceID GetInstanceID();

private:
	shared_ptr<Shader> _shader;
	uint8			   _pass = 0;
	shared_ptr<Model>  _model;
};

