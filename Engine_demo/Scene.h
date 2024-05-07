#pragma once
#include "pch.h"

class Scene
{
public:
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();

	virtual void Add(shared_ptr<GameObject> object);
	virtual void Remove(shared_ptr<GameObject> object);

	unordered_set<shared_ptr<GameObject>> GetObjects() { return _objects; }
	shared_ptr<GameObject> GetCameraObj() { return _cameras.empty() ? nullptr : *_cameras.begin(); }
	shared_ptr<GameObject> GetLight() { return _lights.empty() ? nullptr : *_lights.begin(); }
	
	shared_ptr<GameObject> Pick(int32 screenX, int32 screenY);
private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_set<shared_ptr<GameObject>> _cameras;
	unordered_set<shared_ptr<GameObject>> _lights;
};

