#include "pch.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "13. DiffuseDemo.h"

void DiffuseDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"10. Lighting_Diffuse.fx");

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
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"IceCream", L"..\\Resources\\Textures\\IceCream.png");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}

	RENDER->Init(_shader);
}

void DiffuseDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	Vec4 lightDiffuse{ 1.f, 1.f, 1.f, 1.f };
	_shader->GetVector("LightDiffuse")->SetFloatVector((float*)&lightDiffuse);

	Vec3 lightDir{ 1.f, -0.5f, 1.f };
	lightDir.Normalize();
	_shader->GetVector("LightDir")->SetFloatVector((float*)&lightDir);

	{
		Vec4 materialDiffuse(1.f);
		_shader->GetVector("MaterialDiffuse")->SetFloatVector((float*)&materialDiffuse);
		_obj->Update();
	}

	{
		Vec4 materialDiffuse(0.5f);
		_shader->GetVector("MaterialDiffuse")->SetFloatVector((float*)&materialDiffuse);
		_obj2->Update();
	}
}

void DiffuseDemo::Render()
{
}

