#pragma once
#include "Object.h"
class CollisionBox : public Object
{
public:
	CDXUTTimer * timer;
	float DelT = 0;
	bool RenderOn =false;
	CollisionBox(Transform ts,bool RenderOn,string tag, float Del);
	virtual ~CollisionBox();
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(Object * obj) override;
	
	Mesh *mesh;

};

