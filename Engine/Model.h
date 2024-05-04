#pragma once

struct ModelBone;
struct ModelMesh;

class Model : public enable_shared_from_this<Model>
{
public:
	Model();
	~Model();


public:

	uint32 GetBoneCount() { return _bones.size(); }

	vector<shared_ptr<ModelBone>>& GetBones() { return _bones; }
	shared_ptr<ModelBone> GetBoneByName(wstring boneName);
	shared_ptr<ModelBone> GetBoneByIndex(int32 boneIndex) { return _bones[boneIndex]; }
	
	vector<shared_ptr<Material>>& GetMaterials() { return _materials; }
	shared_ptr<Material> GetMaterialByName(wstring materialName);
	shared_ptr<Material> GetMaterialByIndex(int32 materialIndex) { return _materials[materialIndex]; }

	vector<shared_ptr<ModelMesh>>& GetMeshes() { return _meshes; }
	shared_ptr<ModelMesh> GetMeshByName(wstring meshName);
	shared_ptr<ModelMesh> GetMeshByIndex(int32 meshIndex) { return _meshes[meshIndex]; }


public:
	void ReadMaterial(wstring filename);
	void ReadModel(wstring filename);


private:
	void BindCacheInfo();

private:
	wstring _modelPath = L"../Resources/Models/";
	wstring _texturePath = L"../Resources/Textures/";

private:
	shared_ptr<ModelBone> _root;
	vector<shared_ptr<Material>> _materials;
	vector<shared_ptr<ModelBone>> _bones;
	vector<shared_ptr<ModelMesh>> _meshes;
};

