#pragma once
#include "Object.h"
class NormalEnemy :public Object
{
private :
	Mesh * mesh;
	Vec3 pos;
	Vec3 PP;
public:
	NormalEnemy(Vec3 pos);
	virtual ~NormalEnemy();
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(Object* obj) override;
};

