#include "DXUT.h"
#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(Vec3 pos)
	: pos(pos)
{
	ts.timer = new CDXUTTimer;
	ts.timer->Start();
	CollKind = "¹Ú½º";
	ObjTag = "NormalEnemy";
	
	mesh = LOADER->FindMesh("Enemy");
	ts.SetRot(Vec3(0,0,0));
	ts.SetScale(Vec3(0.4,0.4,0.4));
	ts.GetMesh = mesh;
	Hp = 5;
	GravityOn = true;
}

NormalEnemy::~NormalEnemy()
{
}

void NormalEnemy::Update()
{
	if (Hp <= 0)
	{
		Die = true;

	}

	ts.SetPos(pos);
	D3DXVec3Normalize(&PP,&Vec3(OBJMANAGER->m_Player->ts.Pos - pos));
	pos += PP *10* DXUTGetElapsedTime();
	pos.y = 0.5;
}

void NormalEnemy::Render()
{
	ts.SetWorldMatrix();
	RENDER3D->Render(mesh,ts);
}

void NormalEnemy::UIRender()
{
}

void NormalEnemy::Collision(Object* obj)
{

}
