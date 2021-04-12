#include "DXUT.h"
#include "EXObject.h"

EXObject::EXObject()
{
	mesh = LOADER->FindMeshs("Player");
	ts.SetPos(Vec3(0, 0, 0));

	ObjTag = "EXObject";
}

EXObject::~EXObject()
{
}

void EXObject::Update()
{
	for (auto iter : mesh->v_mesh)
	{
		ts.Radius = abs(iter->maxVec.x - iter->minVec.x) ;
	}
	ts.SetRot(Vec3(0,0,0));
	ts.SetScale(Vec3(100,100,100));
	ts.SetWorldMatrix();

}

void EXObject::Render()
{
	mesh->Render(0.03, ts);

}

void EXObject::UIRender()
{
}

void EXObject::Collision(Object* obj)
{
	if (obj->ObjTag == "Player")
	{
	}
}
