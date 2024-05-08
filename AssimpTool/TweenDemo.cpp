#include "pch.h"
#include "TweenDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Model.h"
#include "Light.h"

void TweenDemo::Init()
{
	//RESOURCES->Init();

	_shader = make_shared<Shader>(L"18. TweenDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3(0.f, 0.f, -5.f));
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	CreateKachujin();

	CUR_SCENE->Add(_camera);

	{
		auto light = make_shared<GameObject>();
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.8f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		light->GetLight()->SetLightDesc(lightDesc);
		CUR_SCENE->Add(light);
	}
}

void TweenDemo::Update()
{
}

void TweenDemo::Render()
{

}

void TweenDemo::CreateKachujin()
{
	shared_ptr<Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Kachujin/Kachujin");
	m1->ReadMaterial(L"Kachujin/Kachujin");

	m1->ReadAnimation(L"Kachujin/Idle");
	m1->ReadAnimation(L"Kachujin/Run");
	m1->ReadAnimation(L"Kachujin/Slash");


	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vec3(0, 0, 1));
	_obj->GetOrAddTransform()->SetScale(Vec3(0.01f));

	_obj->AddComponent(make_shared<ModelAnimator>(_shader));
	{
		_obj->GetModelAnimator()->SetModel(m1);
		_obj->GetModelAnimator()->SetPass(0);
	}
}