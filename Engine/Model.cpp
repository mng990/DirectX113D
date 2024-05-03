#include "pch.h"
#include "Model.h"
#include "tinyxml2.h"
#include "Utils.h"
#include "FileUtils.h"
#include "Material.h"
#include "ModelMesh.h"
#include <filesystem>


Model::Model()
{

}

Model::~Model()
{

}

shared_ptr<ModelBone> Model::GetBoneByName(wstring boneName)
{
	for (auto bone : _bones)
	{
		if (bone->name == boneName)
			return bone;
	}

	return nullptr;
}

shared_ptr<Material> Model::GetMaterialByName(wstring materialName)
{
	for (auto mesh : _meshes)
	{
		if (mesh->materialName == materialName)
			return mesh->material;
	}

	return nullptr;
}

shared_ptr<ModelMesh> Model::GetMeshByName(wstring meshName)
{
	for (auto mesh : _meshes)
	{
		if (mesh->name == meshName)
			return mesh;
	}

	return nullptr;
}

void Model::ReadMaterial(wstring filename)
{
	wstring fullPath = _texturePath + filename + L".xml";

	auto parentPath = filesystem::path(fullPath), parent_path();
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	tinyxml2::XMLError check = document->LoadFile(Utils::ToString(fullPath).c_str());
	assert(check == tinyxml2::XML_SUCCESS);

	tinyxml2::XMLElement* root = document->FirstChildElement();
	tinyxml2::XMLElement* materialNode = root->FirstChildElement();

	while (materialNode)
	{
		shared_ptr<Material> material = make_shared<Material>();

		tinyxml2::XMLElement* node = nullptr;

		node = materialNode->FirstChildElement();
		material->SetName(Utils::ToWString(node->GetText()));

		// Diffuse Texture
		node = node->NextSiblingElement();
		
		if (node->GetText()) 
		{
			wstring textureStr = Utils::ToWString(node->GetText());

			if(textureStr.length() > 0)
			{
				auto texture = RESOURCES->GetOrAddTexture(textureStr, (parentPath / textureStr).wstring());
				material->SetDiffuseMap(texture);
			}
			
		}

		// SpecularTexture
		node = node->NextSiblingElement();

		if (node->GetText())
		{
			wstring textureStr = Utils::ToWString(node->GetText());

			if (textureStr.length() > 0)
			{
				auto texture = RESOURCES->GetOrAddTexture(textureStr, (parentPath / textureStr).wstring());
				material->SetSpecularMap(texture);
			}

		}

		// NormalTexture
		node = node->NextSiblingElement();

		if (node->GetText())
		{
			wstring textureStr = Utils::ToWString(node->GetText());

			if (textureStr.length() > 0)
			{
				auto texture = RESOURCES->GetOrAddTexture(textureStr, (parentPath / textureStr).wstring());
				material->SetNormalMap(texture);
			}

		}

		// Ambient
		{
			node = node->NextSiblingElement();
			Color color;

			color.x = node->FloatAttribute("R");
			color.y = node->FloatAttribute("G");
			color.z = node->FloatAttribute("B");
			color.w = node->FloatAttribute("A");

			material->GetMaterialDesc().ambient = color;
		}
		
		// Diffuse
		{
			node = node->NextSiblingElement();
			Color color;

			color.x = node->FloatAttribute("R");
			color.y = node->FloatAttribute("G");
			color.z = node->FloatAttribute("B");
			color.w = node->FloatAttribute("A");

			material->GetMaterialDesc().diffuse = color;
		}

		// Specular
		{
			node = node->NextSiblingElement();
			Color color;

			color.x = node->FloatAttribute("R");
			color.y = node->FloatAttribute("G");
			color.z = node->FloatAttribute("B");
			color.w = node->FloatAttribute("A");

			material->GetMaterialDesc().specular = color;
		}

		// Emissive
		{
			node = node->NextSiblingElement();
			Color color;

			color.x = node->FloatAttribute("R");
			color.y = node->FloatAttribute("G");
			color.z = node->FloatAttribute("B");
			color.w = node->FloatAttribute("A");

			material->GetMaterialDesc().emissive = color;
		}	
		
		materialNode = materialNode->NextSiblingElement();
	}
	
	BindCacheInfo();
}

void Model::ReadModel(wstring filename)
{
	wstring fullPath = _modelPath + filename + L".mesh";

	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(fullPath, FileMode::Read);

	// Bones
	{
		const uint32 count = file->Read<uint32>();

		for (uint32 i = 0; i < count; i++)
		{
			shared_ptr<ModelBone> bone = make_shared<ModelBone>();
			bone->index = file->Read<int32>();
			bone->name = Utils::ToWString(file->Read<string>());
			bone->parentIndex = file->Read<int32>();
			bone->transform = file->Read<Matrix>();

			_bones.push_back(bone);
		}
	}

	// Mesh

	{
		const uint32 count = file->Read<uint32>();

		for (uint32 i = 0; i < count; i++)
		{
			shared_ptr<ModelMesh> mesh = make_shared<ModelMesh>();

			mesh->name = Utils::ToWString(file->Read<string>());
			mesh->boneIndex = file->Read<int32>();
			
			// Material
			mesh->materialName = Utils::ToWString(file->Read<string>());

			// VertexData
			{
				const uint32 count = file->Read<uint32>();
				vector<ModelVertexType> vertices;
				vertices.resize(count);

				void* data = vertices.data();
				file->Read(&data, sizeof(ModelVertexType) * count);
				mesh->geometry->AddVertices(vertices);
			}

			// IndexData
			{
				const uint32 count = file->Read<uint32>();

				vector<uint32> indices;
				indices.resize(count);

				void* data = indices.data();
				file->Read(&data, sizeof(uint32) * count);
				mesh->geometry->AddIndices(indices);
			}

			mesh->CreateBuffers();

			_meshes.push_back(mesh);
		}

	}

	BindCacheInfo();
}

void Model::BindCacheInfo()
{
	for (const auto& mesh : _meshes)
	{
		if (mesh->material != nullptr) continue;

		mesh->material = GetMaterialByName(mesh->materialName);
	}

	for (const auto& mesh : _meshes)
	{
		if (mesh->bone != nullptr) continue;

		mesh->bone = GetBoneByIndex(mesh->boneIndex);
	}

	if (_root == nullptr && _bones.size() > 0)
	{
		_root = _bones[0];

		for (const auto& bone : _bones)
		{
			if (bone->parentIndex >= 0)
			{
				bone->parent = _bones[bone->parentIndex];
				bone->parent->children.push_back(bone);
			}
			else
			{
				bone->parent = nullptr;
			}
		}
	}
}