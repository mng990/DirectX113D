#include "pch.h"
#include "RenderDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "ModelAnimator.h"
#include "ModelRenderer.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "SceneDemo.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MonoBehaviour.h"

void SceneDemo::Init()
{
	_shader = make_shared<Shader>(L"24. RenderDemo.fx");

	// Camera
	{
		_camera = make_shared<GameObject>();
		_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraScript>());

		CUR_SCENE->Add(_camera);
	}
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.6f);
		lightDesc.diffuse = Vec4(0.8f);
		lightDesc.specular = Vec4(0.3f);
		lightDesc.direction = Vec3(1.f, -1.f, 1.f);

		auto light = make_shared<GameObject>();
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDesc(lightDesc);

		CUR_SCENE->Add(light);
	}

	shared_ptr<Model> m1 = make_shared<Model>();

	m1->ReadModel(L"Kachujin/Kachujin");
	m1->ReadMaterial(L"Kachujin/Kachujin");
	m1->ReadAnimation(L"Kachujin/Idle");
	m1->ReadAnimation(L"Kachujin/Run");
	m1->ReadAnimation(L"Kachujin/Slash");

	for (int32 i = 0; i < 300; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelAnimator>(_shader));
		{
			obj->GetModelAnimator()->SetModel(m1);
			obj->GetModelAnimator()->SetPass(2);
		}
		CUR_SCENE->Add(obj);
	}

	// Model
	shared_ptr<Model> m2 = make_shared<Model>();
	m2->ReadModel(L"Tower/Tower");
	m2->ReadMaterial(L"Tower/Tower");

	for (int32 i = 0; i < 100; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelRenderer>(_shader));
		{
			obj->GetModelRenderer()->SetPass(1);
			obj->GetModelRenderer()->SetModel(m2);
		}
		CUR_SCENE->Add(obj);
	}

	// Mesh
	
	{
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(_shader);
		auto texture = RESOURCES->Load<Texture>(L"Kirby", L"..\\Resources\\Textures\\kirby.jpg");
		material->SetDiffuseMap(texture);
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		RESOURCES->Add(L"Kirby", material);
	}

	for (int32 i = 0; i < 100; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(2.f));
		obj->GetOrAddTransform()->SetRotation(Vec3(0.f, -1.5f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Kirby"));
		}
		{
			shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
			obj->GetMeshRenderer()->SetMesh(mesh);
			obj->GetMeshRenderer()->SetPass(0);

		}

		CUR_SCENE->Add(obj);
	}

}

void SceneDemo::Update()
{
}

void SceneDemo::Render()
{

}
