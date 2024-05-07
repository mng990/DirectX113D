#include "pch.h"
#include "RenderDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "ModelAnimator.h"
#include "ModelRenderer.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "ViewportDemo.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Material.h"
#include "MonoBehaviour.h"

void ViewportDemo::Init()
{

	_shader = make_shared<Shader>(L"24. RenderDemo.fx");

	// Camera
	{
		auto _camera = make_shared<GameObject>();
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
	
	// Mesh
	
	{
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(_shader);
		auto texture = RESOURCES->Load<Texture>(L"Kirby", L"..\\Resources\\Textures\\kirby.jpg");
		material->SetDiffuseMap(texture);
		material->SetDiffuseMap(texture);

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		RESOURCES->Add(L"Kirby", material);
	}

	for (int32 i = 0; i < 500; i++)
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

void ViewportDemo::Update()
{
	static float width = 800.f;
	static float height = 600.f;
	static float x = 0.f;
	static float y = 0.f;

	ImGui::InputFloat("Width", &width, 10.f);
	ImGui::InputFloat("Height", &height, 10.f);
	ImGui::InputFloat("X", &x, 10.f);
	ImGui::InputFloat("Y", &y, 10.f);

	GRAPHICS->SetViewport(width, height, x, y);


	static Vec3 pos = Vec3(2, 0, 0);
	ImGui::InputFloat3("Pos", (float*)&pos);

	Viewport& vp = GRAPHICS->GetViewport();
	Vec3 pos2D = vp.Project(pos, Matrix::Identity, Camera::S_MatView, Camera::S_MatProjection);
	
	ImGui::InputFloat3("Pos2D", (float*)&pos2D);

	{
		Vec3 temp = vp.Unproject(pos2D, Matrix::Identity, Camera::S_MatView, Camera::S_MatProjection);
		ImGui::InputFloat3("Recalc", (float*)&temp);
	}
}

void ViewportDemo::Render()
{

}
