#include "pch.h"
#include "StaticMeshDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"

void StaticMeshDemo::Init()
{
	RESOURCES->Init();
	
	_shader = make_shared<Shader>(L"16. ModelDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3(0.f, 0.f, -5.f));
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	CreateTank();

	RENDER->Init(_shader);
}

void StaticMeshDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		RENDER->PushLightData(lightDesc);
	}
	{
		_obj->Update();
	}
}

void StaticMeshDemo::Render()
{

}

void StaticMeshDemo::CreateTower()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Tower/Tower");
	m1->ReadMaterial(L"Tower/Tower");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vec3(0.1f));

	shared_ptr<ModelRenderer> modelRenderer = make_shared<ModelRenderer>(_shader);
	modelRenderer->SetPass(1);

	_obj->AddComponent(modelRenderer);

	_obj->GetModelRenderer()->SetModel(m1);
}

void StaticMeshDemo::CreateTank()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Tank/Tank");
	m1->ReadMaterial(L"Tank/Tank");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vec3(1.f));

	shared_ptr<ModelRenderer> modelRenderer = make_shared<ModelRenderer>(_shader);
	modelRenderer->SetPass(1);

	_obj->AddComponent(modelRenderer);

	_obj->GetModelRenderer()->SetModel(m1);
}

void StaticMeshDemo::CreateDragon()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Dragon/Dragon");
	m1->ReadMaterial(L"Dragon/Dragon");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vec3(1.f));

	shared_ptr<ModelRenderer> modelRenderer = make_shared<ModelRenderer>(_shader);
	modelRenderer->SetPass(1);

	_obj->AddComponent(modelRenderer);

	_obj->GetModelRenderer()->SetModel(m1);
}

void StaticMeshDemo::CreateAlien()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Alien/Alien");
	m1->ReadMaterial(L"Alien/Alien");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vec3(1.f));

	shared_ptr<ModelRenderer> modelRenderer = make_shared<ModelRenderer>(_shader);
	modelRenderer->SetPass(1);

	_obj->AddComponent(modelRenderer);

	_obj->GetModelRenderer()->SetModel(m1);
}

void StaticMeshDemo::CreateHulkbuster()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Hulkbuster/Hulkbuster");
	m1->ReadMaterial(L"Hulkbuster/Hulkbuster");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vec3(1.f));

	shared_ptr<ModelRenderer> modelRenderer = make_shared<ModelRenderer>(_shader);
	modelRenderer->SetPass(1);

	_obj->AddComponent(modelRenderer);

	_obj->GetModelRenderer()->SetModel(m1);
}
