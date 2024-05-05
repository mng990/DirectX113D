#include "pch.h"
#include "MeshInstancingDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "InstancingManager.h"

void MeshInstancingDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"21. MeshInstancingDemo.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	// Material
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
		// INSTANCING
		_material = material;
	}

	for (int32 i = 0; i < 50000; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0, rand() % 100));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Kirby"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			obj->GetMeshRenderer()->SetMesh(mesh);
			
			// INSTANCING
			_mesh = mesh;
		}

		_objs.push_back(obj);
	}

	RENDER->Init(_shader);

	_instanceBuffer = make_shared<VertexBuffer>();


	for (auto& obj : _objs)
	{
		Matrix world = obj->GetTransform()->GetWorldMatrix();
		_worlds.push_back(world);
	}

	_instanceBuffer->Create(_worlds, /* slot */1);
}

void MeshInstancingDemo::Update()
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

void MeshInstancingDemo::Render()
{

}
