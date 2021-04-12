#pragma once
#include "singleton.h"
#include "Object.h"
class ObjectManager : public singleton<ObjectManager>
{
private:
	CDXUTTimer* timer;
	float GravityPower =0 ;
public:
	list <Object* > L_obj[10];
	ObjectManager();
	~ObjectManager();
	Object *m_Player;
public:
	Object* AddObject(Object *obj,int Tag);
	void Update();
	void Render();
	void UIRender();
	void Release();
	void Gravity(Object* obj);
};

#define OBJMANAGER ObjectManager::GetInstance()
