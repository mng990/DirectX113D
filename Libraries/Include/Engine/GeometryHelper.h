#pragma once
#include "Geometry.h"
#include "GeometryHelper.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
};

