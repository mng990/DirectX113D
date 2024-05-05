#include "pch.h"
#include "AnimInstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "ModelAnimator.h"
#include "InstancingManager.h"
#include "RenderManager.h"

void AnimInstancingDemo::Init()
{
	_shader = make_shared<Shader>(L"23. AnimInstancingDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	shared_ptr<Model> m1 = make_shared<Model>();

	m1->ReadModel(L"Kachujin/Kachujin");
	m1->ReadMaterial(L"Kachujin/Kachujin");
	m1->ReadAnimation(L"Kachujin/Idle");
	m1->ReadAnimation(L"Kachujin/Run");
	m1->ReadAnimation(L"Kachujin/Slash");

	for (int32 i = 0; i < 400; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelAnimator>(_shader));
		{
			obj->GetModelAnimator()->SetModel(m1);
		}
		_objs.push_back(obj);
	}

	RENDER->Init(_shader);
}

void AnimInstancingDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.6f);
		lightDesc.diffuse = Vec4(0.8f);
		lightDesc.specular = Vec4(0.3f);
		lightDesc.direction = Vec3(1.f, -1.f, 1.f);
		RENDER->PushLightData(lightDesc);
	}

	INSTANCING->Render(_objs);
}

void AnimInstancingDemo::Render()
{

}
