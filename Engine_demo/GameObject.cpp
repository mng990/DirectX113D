#include "pch.h"
#include "MonoBehavior.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "BaseCollider.h"


GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
}


// ��� ������Ʈ Awake
void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) component->Awake();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		if (script) script->Awake();
	}
}

// ��� ������Ʈ Start
void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components) 
	{
		if(component) component->Start();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		if (script) script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if(component) component->Update();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		if(script) script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) component->LateUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		if (script) script->LateUpdate();
	}
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) component->FixedUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		if (script) script->FixedUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);
	return static_pointer_cast<Camera>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::MeshRenderer);
	return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<ModelRenderer> GameObject::GetModelRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::ModelRenderer);
	return static_pointer_cast<ModelRenderer>(component);
}

shared_ptr<ModelAnimator> GameObject::GetModelAnimator()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
	return static_pointer_cast<ModelAnimator>(component);
}

shared_ptr<Light> GameObject::GetLight()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Light);
	return static_pointer_cast<Light>(component);
}

shared_ptr<BaseCollider> GameObject::GetCollider()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Collider);
	return static_pointer_cast<BaseCollider>(component);
}
 
// shared_ptr<Animator> GameObject::GetAnimator()
// {
// 	shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
// 	return static_pointer_cast<Animator>(component);
// }

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr) 
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		AddComponent(transform);
	}

	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	// shared_from_this: ���� ��ü�� weak_ptr�� ��ȯ
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else 
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehavior>(component));
	}
}