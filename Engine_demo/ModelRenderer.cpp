#include "pch.h"
#include "Material.h"
#include "ModelRenderer.h"
#include "ModelMesh.h"
#include "Camera.h"
#include "Light.h"

ModelRenderer::ModelRenderer(shared_ptr<Shader> shader) :
	Super(ComponentType::ModelRenderer), _shader(shader)
{
}

ModelRenderer::~ModelRenderer()
{

}

void ModelRenderer::SetModel(shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();

	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}

void ModelRenderer::RenderInstancing(shared_ptr<InstancingBuffer>& buffer)
{
	if (_model == nullptr) return;

	// GlobalData
	_shader->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);

	// Light
	auto lightObj = SCENE->GetCurrentScene()->GetLight();

	if (lightObj)
		_shader->PushLightData(lightObj->GetLight()->GetLightDesc());

	// Bones
	shared_ptr<BoneDesc> boneDesc = make_shared<BoneDesc>();

	const uint32 boneCount = _model->GetBoneCount();

	assert(boneCount <= MAX_MODEL_TRANSFORMS);

	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc->transforms[i] = bone->transform;
	}

	_shader->PushBoneData(*boneDesc.get());

	const auto& meshes = _model->GetMeshes();

	for (auto& mesh : meshes) {
		if (mesh->material)
			mesh->material->Update();

		// 계층 구조에 맞는 메쉬를 할당
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		mesh->vertexBuffer->PushData();
		mesh->indexBuffer->PushData();
		
		buffer->PushData();

		_shader->DrawIndexedInstanced(0, _pass, mesh->indexBuffer->GetCount(), buffer->GetCount());
	}
}

InstanceID ModelRenderer::GetInstanceID()
{
	return make_pair((uint64)_model.get(), (uint64)_shader.get());
}
