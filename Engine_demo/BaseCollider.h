#pragma once
#include "Component.h"

enum class ColliderType
{
	Sphere,
	AABB,
	OBB,
};

class BaseCollider : public Component
{
	using Super = Component;
public:
	BaseCollider(ColliderType colliderType);
	virtual ~BaseCollider();

	virtual bool Intersects(Ray& ray, OUT float& distance) abstract;


	ColliderType GetColliderType() { return _colliderType; }

protected:
	ColliderType _colliderType;
};

