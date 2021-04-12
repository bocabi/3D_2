#pragma once
#include "Scene.h"
class ingameScene : public Scene
{
private:
	Mesh* mesh;
	Transform ts;
public :
	ingameScene();
	virtual ~ingameScene();

	// Scene을(를) 통해 상속됨
	virtual void init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};

