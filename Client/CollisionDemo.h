#pragma once
#include "IExecute.h"
#include "MonoBehaviour.h"

class CollisionDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<Shader> _shader;
};


class MoveScript : public MonoBehaviour
{
public:
	virtual void Update() override;
};