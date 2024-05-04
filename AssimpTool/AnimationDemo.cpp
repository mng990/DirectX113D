#include "pch.h"
#include "AnimationDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"

void AnimationDemo::Init()
{
	RESOURCES->Init();
	
	_shader = make_shared<Shader>(L"17. AnimationDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3(0.f, 0.f, -5.f));
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	CreateTank();

	RENDER->Init(_shader);
}

void AnimationDemo::Update()
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

void AnimationDemo::Render()
{

}

void AnimationDemo::CreateKachujin()
{
// 	shared_ptr<Model> m1 = make_shared<Model>();
// 	m1->ReadModel(L"Kachujin/K");
}
