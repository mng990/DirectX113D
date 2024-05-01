#include "pch.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "12. AmbientDemo.h"

void AmbientDemo::Init()
{
	RESOURCES->Init();

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
		_shader = make_shared<Shader>(L"09. Lighting_Ambient.fx");
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"IceCream", L"..\\Resources\\Textures\\IceCream.png");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{0.5f, 0.f, 2.f});
	_obj2->AddComponent(make_shared<MeshRenderer>());

	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"IceCream", L"..\\Resources\\Textures\\IceCream.png");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}

	RENDER->Init(_shader);
}

void AmbientDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	Vec4 lightAmbient{ 1.0f, 1.f, 1.f, 1.f };
	_shader->GetVector("LightAmbient")->SetFloatVector((float*)&lightAmbient);

	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj->Update();
	}

	{
		Vec4 materialAmbient(0.5f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj2->Update();
	}
}

void AmbientDemo::Render()
{
}

