#include "pch.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "10. GlobalTestDemo.h"

void GlobalTestDemo::Init()
{
	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3( 0.f, 0.f, -2.f));

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());

	{
		_shader = make_shared<Shader>(L"08. GlobalTest.fx");
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		RESOURCES->Init();
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"IceCream", L"..\\Resources\\Textures\\kirby.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	RENDER->Init(_shader);
}

void GlobalTestDemo::Update()
{
	_camera->Update();
	RENDER->Update();
	_obj->Update();
}

void GlobalTestDemo::Render()
{
}

