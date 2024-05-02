#pragma once
#include "pch.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "18. NormalMappingDemo.h"

void NormalMappingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"15. NormalMapping.fx");

	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Leather", L"..\\Resources\\Textures\\Leather.jpg");
			material->SetDiffuseMap(texture);
		}
		{
			shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"LeatherNomal", L"..\\Resources\\Textures\\Leather_Normal.jpg");
			material->SetNormalMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		desc.emissive = Vec4(0.f);

		RESOURCES->Add(L"Leather", material);
	}

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
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Material> material = RESOURCES->Get<Material>(L"Leather");
		_obj->GetMeshRenderer()->SetMaterial(material);
	}
	

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{0.5f, 0.f, 2.f});
	_obj2->AddComponent(make_shared<MeshRenderer>());

	{
		shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		shared_ptr<Material> material = RESOURCES->Get<Material>(L"Leather");
		_obj2->GetMeshRenderer()->SetMaterial(material);
	}

	RENDER->Init(_shader);
}

void NormalMappingDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(0.8f);
		lightDesc.specular = Vec4(1.f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		lightDesc.emissive = Vec4(0.f, 0.f, 1.f, 1.f);

		RENDER->PushLightData(lightDesc);
	}

	{
		_obj->Update();
	}
	
	{
		_obj2->Update();
	}
	
}

void NormalMappingDemo::Render()
{
}

