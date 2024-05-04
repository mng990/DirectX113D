#pragma once

struct ModelBone;
struct ModelMesh;
struct ModelAnimation;

class Model : public enable_shared_from_this<Model>
{
public:
	Model();
	~Model();
public:
	void ReadMaterial(wstring filename);
	void ReadModel(wstring filename);
	void ReadAnimation(wstring filename);

public:

	uint32 GetBoneCount() { return _bones.size(); }
	vector<shared_ptr<ModelBone>>& GetBones() { return _bones; }
	shared_ptr<ModelBone> GetBoneByName(const wstring& boneName);
	shared_ptr<ModelBone> GetBoneByIndex(int32 boneIndex) { return (boneIndex <0 || boneIndex >= _bones.size()) ? nullptr : _bones[boneIndex]; }
	
	uint32 GetMaterialCount() { return _materials.size(); }
	vector<shared_ptr<Material>>& GetMaterials() { return _materials; }
	shared_ptr<Material> GetMaterialByName(const wstring& materialName);
	shared_ptr<Material> GetMaterialByIndex(int32 materialIndex) { return _materials[materialIndex]; }

	uint32 GetMeshCount() { return _meshes.size(); }
	vector<shared_ptr<ModelMesh>>& GetMeshes() { return _meshes; }
	shared_ptr<ModelMesh> GetMeshByName(const wstring& meshName);
	shared_ptr<ModelMesh> GetMeshByIndex(int32 meshIndex) { return _meshes[meshIndex]; }


	uint32 GetAnimationCount() { return _animations.size(); }
	vector<shared_ptr<ModelAnimation>>& GetAnimation() { return _animations; }
	shared_ptr<ModelAnimation> GetAnimationByName(wstring name);
	shared_ptr<ModelAnimation> GetAnimationByIndex(int32 index) { return (index < 0 || index >= _animations.size()) ? nullptr : _animations[index]; }

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
	vector<shared_ptr<ModelAnimation>> _animations;
};

