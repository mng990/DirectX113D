#include "pch.h"
#include "Camera.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
	: Super(ComponentType::MeshRenderer)
{	
}

MeshRenderer::~MeshRenderer()
{
}

//void MeshRenderer::Update()
//{
//	// Render
//	if (_mesh == nullptr || _texture == nullptr || _shader == nullptr)
//		return;
//
//	// �̵�����
//	_shader->GetSRV("DiffuseMap")->SetResource(_texture->GetComPtr().Get());
//
//	Matrix world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{world});
//
//	_shader->GetMatrix("World")->SetMatrix((float*)&world);
//
//	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
//	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();
//
//	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
//	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _mesh->GetIndexBuffer()->GetOffset());
//	
//	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount());
//}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _material == nullptr)
		return;

	shared_ptr<Shader> shader = _material->GetShader();
	if (shader == nullptr)
		return;

	_material->Update();

	Matrix world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();

	DC->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}