#pragma once
#include "Component.h"

class Camera;
class Transform;
class MonoBehavior;
class MeshRenderer;
class ModelRenderer;
class ModelAnimator;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Camera> GetCamera();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<ModelRenderer> GetModelRenderer();
	shared_ptr<ModelAnimator> GetModelAnimator();
	//shared_ptr<Animator> GetAnimator();

	shared_ptr<Transform> GetOrAddTransform();

	void AddComponent(shared_ptr<Component> component);

private:
	ComPtr<ID3D11Device> _device;

protected:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<Component>> _scripts;
};

