#pragma once
#include "IExecute.h"

class GroupDemo : public IExecute
{

	struct Input
	{
		float value;
	};

	struct Output
	{
		uint32 groupID[3];
		uint32 groupThreadID[3];
		uint32 dispatchThreadID[3];
		uint32 groupIndex;
		float value;
	};

public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

private:
	shared_ptr<Shader> _shader;
};
