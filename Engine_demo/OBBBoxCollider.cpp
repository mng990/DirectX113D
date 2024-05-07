#include "pch.h"
#include "OBBBoxCollider.h"

OBBBoxCollider::OBBBoxCollider() : BaseCollider(ColliderType::OBB)
{

}

OBBBoxCollider::~OBBBoxCollider()
{

}

void OBBBoxCollider::Update()
{

}

bool OBBBoxCollider::Intersects(Ray& ray, OUT float& distance)
{
	return _boundingBox.Intersects(ray.position, ray.direction, OUT distance);
}
