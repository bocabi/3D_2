#include "DXUT.h"
#include "DirtBlock.h"


DirtBlock::DirtBlock(Vec3 pos)
	:pos(pos)
{
	ts.timer = new CDXUTTimer;
	ts.timer->Start();
	ObjTag = "Block";
	mesh = LOADER->FindMesh("Block");
	ts.SetPos(pos);
	ts.SetRot(Vec3(0,0,0));
	ts.SetScale(Vec3(5,5,5));
	ts.SetWorldMatrix();
	ts.GetMesh = mesh;

}


DirtBlock::~DirtBlock()
{
}

void DirtBlock::Update()
{

	ts.Radius = abs(mesh->maxVec.x - mesh->minVec.x);
}

void DirtBlock::Render()
{
	RENDER3D->Render(mesh,ts);
}

void DirtBlock::UIRender()
{
}

void DirtBlock::Collision(Object* obj)
{
}
