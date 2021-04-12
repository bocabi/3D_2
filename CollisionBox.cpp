#include "DXUT.h"
#include "CollisionBox.h"



CollisionBox::CollisionBox(Transform ts, bool RenderOn, string tag, float Del)
	:RenderOn(RenderOn), DelT(Del)
{
	this->ts = ts;
	this->ts.SetScale(Vec3(2, 2, 2));
	this->ts.SetRot(Vec3(0, 0, 0));
	this->ObjTag = tag;
	CollKind = "¹Ú½º";
	mesh = LOADER->FindMesh("Block");
	this->ts.GetMesh = mesh;
	timer = new CDXUTTimer;
	timer->Start();
}

CollisionBox::~CollisionBox()
{
}

void CollisionBox::Update()
{

	if (DelT != 0)
	{
		if (timer->GetTime() >= DelT)
		{
			Die = true;
		}
	}
}

void CollisionBox::Render()
{
	ts.SetScale(Vec3(2,2, 2));
	ts.SetWorldMatrix();

	//RENDER3D->Render(mesh, ts);
}

void CollisionBox::UIRender()
{
}

void CollisionBox::Collision(Object * obj)
{
	if (ObjTag == "")
	{
		if (obj->ObjTag == "NormalEnemy")
		{
			obj->Hp--;
		}
	}
}




