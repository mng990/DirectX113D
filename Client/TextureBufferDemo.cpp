#include "pch.h"
#include "RenderDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "ModelAnimator.h"
#include "ModelRenderer.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "SceneDemo.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureBufferDemo.h"
#include "TextureBuffer.h"
#include "Material.h"
#include "MonoBehaviour.h"

void TextureBufferDemo::Init()
{

	auto newSRV = MakeComputeShaderTexture();

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
		auto texture = make_shared<Texture>();
		texture->SetSRV(newSRV);
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

void TextureBufferDemo::Update()
{
}

void TextureBufferDemo::Render()
{

}

ComPtr<ID3D11ShaderResourceView> TextureBufferDemo::MakeComputeShaderTexture()
{
	auto shader = make_shared<Shader>(L"27. TextureBufferDemo.fx");

	auto texture = RESOURCES->Load<Texture>(L"Kirby", L"..\\Resources\\Textures\\kirby.jpg");
	
	shared_ptr<TextureBuffer> textureBuffer = make_shared<TextureBuffer>(texture->GetTexture2D());
	
	shader->GetSRV("Input")->SetResource(textureBuffer->GetSRV().Get());
	shader->GetUAV("Output")->SetUnorderedAccessView(textureBuffer->GetUAV().Get());
	
	uint32 width = textureBuffer->GetWidth();
	uint32 height = textureBuffer->GetHeight();
	uint32 arraySize = textureBuffer->GetArraySize();

	uint32 x = max(1, (width + 31) / 32);
	uint32 y = max(1, (height + 31)/32);
	shader->Dispatch(0, 0, x, y, arraySize);

	return textureBuffer->GetOutputSRV();
}
