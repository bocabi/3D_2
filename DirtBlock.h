#pragma once
#include "Object.h"
class DirtBlock : public Object
{
private:
	Mesh* mesh;
	Vec3 pos;
public:
	// Object을(를) 통해 상속됨
	DirtBlock(Vec3 pos);
	virtual ~DirtBlock();
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(Object* obj) override;
};

