#include "DXUT.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

Object *ObjectManager::AddObject(Object* obj, int Tag)
{
	if (obj == nullptr)
		return nullptr;
	L_obj[Tag].push_back(obj);
	return obj;
}

void ObjectManager::Update()
{

	for (int i = 0; i < 10; i++)
	{
		for (auto iter = L_obj[i].begin(); iter != L_obj[i].end();)
		{
			(*iter)->Update();
		
			if ((*iter)->GravityOn == true)
			{
				Gravity(*iter);
			}
			for (int a = 0; a < 10; a++)
			{
				for (auto iter_ : L_obj[a])
				{
					if ((*iter) != iter_)
					{
						if ((*iter)->ObjTag != iter_->ObjTag)
						{
							if ((*iter)->CollKind == "¿ø")
								if (COLL->IsOverlap(&(*iter)->ts, &iter_->ts) == true)
								{

									(*iter)->CollNow = true;
									(*iter)->Collision(iter_);

								}
							if ((*iter)->CollKind == "¹Ú½º")
								if (COLL->BoxColl(&(*iter)->ts, &iter_->ts) == true)
								{
									(*iter)->CollNow = true;
									(*iter)->Collision(iter_);
								}
						}
					}
				}
			}
			if ((*iter)->ObjDie() == true)
			{
				SAFE_DELETE(*iter);
				iter = L_obj[i].erase(iter);
			}
			else iter++;
		}

	}

}

void ObjectManager::Render()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto iter : L_obj[i])
		{
			iter->Render();
		}
	}
}

void ObjectManager::UIRender()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto iter : L_obj[i])
		{
			iter->UIRender();
		}
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		for (auto iter : L_obj[i])
		{
			SAFE_DELETE(iter);
		}
		L_obj[i].clear();
	}
}

void ObjectManager::Gravity(Object* obj)
{
	if (obj->CollNow == true)
	{
		obj->ts.PlusPower = 0;
		obj->ts.GravityPower = 0;
	}
	else
	{
		obj->ts.PlusPower+= 0.001;
		obj->ts.GravityPower -= obj->ts.PlusPower;
	}
	obj->CollNow = false;
}
