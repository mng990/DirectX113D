#include "pch.h"
#include "Scene.h"

void Scene::Start()
{
	// 추가, 삭제 로직이 데이터에 반영되지 않게 복사해서 순회
	auto objects = _objects;

	for (shared_ptr<GameObject> object : objects)
	{
		object->Start();
	}
}

void Scene::Update()
{
	auto objects = _objects;

	for (shared_ptr <GameObject> object : objects)
	{
		object->Update();
	}
}

void Scene::LateUpdate()
{
	auto objects = _objects;

	for (shared_ptr <GameObject> object : objects)
	{
		object->LateUpdate();
	}
}

void Scene::Add(shared_ptr<GameObject> object)
{
	_objects.insert(object);
	if (object->GetCamera() != nullptr)
	{
		_cameras.insert(object);
	}

	if (object->GetLight() != nullptr)
	{
		_lights.insert(object);
	}
}

void Scene::Remove(shared_ptr<GameObject> object)
{
	_objects.erase(object);
	_cameras.erase(object);
	_lights.erase(object);
}
