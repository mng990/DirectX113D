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

private:
	unordered_set<shared_ptr<GameObject>> _objects;
	unordered_set<shared_ptr<GameObject>> _cameras;
	unordered_set<shared_ptr<GameObject>> _lights;
};

