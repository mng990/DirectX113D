#include "pch.h"
#include "Material.h"
#include "ModelRenderer.h"
#include "RenderManager.h"
#include "ModelMesh.h"

ModelRenderer::ModelRenderer(shared_ptr<Shader> shader) :
	Super(ComponentType::ModelRenderer), _shader(shader)
{
}

ModelRenderer::~ModelRenderer()
{

}

// void ModelRenderer::Update()
// {
// 	if (_model == nullptr)
// 		return;
// 	
// 	auto world = GetTransform()->GetWorldMatrix();
// 	RENDER->PushTransformData(TransformDesc{world});
// 
// 	const auto& meshes = _model->GetMeshes();
// 
// 	for (auto& mesh : meshes) {
// 		if (mesh->material)
// 			mesh->material->Update();
// 
// 		uint32 stride = mesh->vertexBuffer->GetStride();
// 		uint32 offset = mesh->vertexBuffer->GetOffset();
// 
// 		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
// 		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
// 		
// 		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
// 	}
// }

void ModelRenderer::Update()
{
	if (_model == nullptr)
		return;

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();

	assert(boneCount <= MAX_MODEL_TRANSFORMS);

	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}


	RENDER->PushBoneData(boneDesc);

	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();

	for (auto& mesh : meshes) {
		if (mesh->material)
			mesh->material->Update();

		//BoneIndex
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
		
		// _shader->DrawIndexedInstanced();
	}
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
