#include "pch.h"
#include "Camera.h"
#include "GeometryHelper.h"
#include "CameraScript.h"
#include "07. HeightMapDemo.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"06. Terrain.fx");

	// Texture
	_heightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Terrain\\ulsan.png");
	_texture = RESOURCES->Load<Texture>(L"Jupiter", L"..\\Resources\\Terrain\\grass.jpg");

	const int32 width = _heightMap->GetSize().x;
	const int32 height = _heightMap->GetSize().y;

	const DirectX::ScratchImage& info = _heightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();

	// Object
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, width, height);
	 
	// CPU
	{
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());

		for (int32 z = 0; z < height; z++)
		{
			for (int32 x = 0; x < width; x++)
			{
				int32 idx = width * z + x;

				uint8 height = pixelBuffer[idx];
				v[idx].position.y = height; // ���� ����
			}
		}
	}
	

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	_camera->GetTransform()->SetPosition(Vec3( 0.f, 5.f, 0.f));
	_camera->GetTransform()->SetPosition(Vec3(25.f, 0.f, 0.f));
}

void HeightMapDemo::Update()
{
	_camera->Update();
}

void HeightMapDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)(&_world));
	_shader->GetMatrix("View")->SetMatrix((float*)(&Camera::S_MatView));
	_shader->GetMatrix("Projection")->SetMatrix((float*)(&Camera::S_MatProjection));
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _indexBuffer->GetOffset());

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount());
}
