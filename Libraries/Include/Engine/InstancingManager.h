#pragma once
#include "GameObject.h"
#include "InstancingBuffer.h"

class InstancingManager
{
	DECLARE_SINGLE(InstancingManager);

public:
	void Render(vector<shared_ptr<GameObject>>& gameObjects);
	void ClearData();

	void RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	void RenderAnimRenderer(vector<shared_ptr<GameObject>>& gameObjects);
private:
	void RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects);
	
private:
	void AddData(InstanceID instanceId, InstancingData& data);

private:
	map<InstanceID, shared_ptr<InstancingBuffer>> _buffers;
};

