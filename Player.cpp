#include "DXUT.h"
#include "Player.h"
#include "CollisionBox.h"

Player::Player()
{
	hiteffect = LOADER->FindImages("HitEffect");
	OBJMANAGER->m_Player = this;
	ts.timer = new CDXUTTimer;
	ts.timer->Start();
	CollKind = "¹Ú½º";
	timer = new CDXUTTimer;
	LeftUper = LOADER->FindMeshs("PlayerLeftUper");
	mes = LOADER->FindMesh("Block");
	mesh = LOADER->FindMeshs("PlayerIdle");
	meshRun = LOADER->FindMeshs("PlayerRun");
	LeftPunch = LOADER->FindMeshs("PlayerLeftPunch");
	SetHp(10);
	RightPunch = LOADER->FindMeshs("PlayerRightPunch");
	RollPunch = LOADER->FindMeshs("PlayerRoll");
	ObjTag = "Player";
	ts.SetPos(Vec3(0, 10, 0));
	pos = Vec3(0, 0, 0);
	CamPos = Vec3(0, 10, -10);
	radius = 0;
	CamR.y = 0;
	CamAt.y = -10;
	ShowCursor(false);
	GravityOn = true;
	for (auto iter : mesh->v_mesh)
	{
		ts.GetMesh = iter;

	}
	ts.SetRot(Vec3(D3DXToDegree(radius + 1.55), 0, 0));
	ttts.timer = new CDXUTTimer;



}


Player::~Player()
{
}

void Player::Update()
{
	for (auto iter : CollObj)
	{
		iter->UpdatePos(iter->ts.Pos);
	}
	//ttts = ts;

	for (auto iter : mesh->v_mesh)
	{
		ts.GetMesh = iter;

	}

		
	GetCursorPos(&ptf);
	if (DXUTIsKeyDown(VK_SPACE))
	{
		ts.GravityPower += 1;
	}
	if (ptf.x - WINSIZEX / 2 < 0)
	{
		radius -= 0.05;

	}
	if (ptf.x - WINSIZEX / 2 > 0)
	{
		radius += 0.05;

	}



	if (DXUTIsKeyDown(0x57))
	{
		if (LEftRoll || RightRoll || FrontRoll || BackRoll)
		{

		}
		else if (Right_Punch || Left_Uper)
		{

		}
		else if (DXUTWasKeyPressed(VK_SPACE))
		{
			timer->Start();
			FrontRoll = true;
		}
		else
		{
			Dir = Vec2(cosf(-radius), sinf(-radius));
			pos.x += Dir.x * 10 * DXUTGetElapsedTime();
			pos.z += Dir.y * 10 * DXUTGetElapsedTime();
		}
	}
	if (DXUTIsKeyDown(0x41))
	{
		if (LEftRoll || RightRoll || FrontRoll || BackRoll)
		{

		}
		else if (Right_Punch || Left_Uper)
		{

		}
		else if (DXUTWasKeyPressed(VK_SPACE))
		{
			timer->Start();
			LEftRoll = true;
		}
		else
		{
			Dir = Vec2(cosf(-radius + 1.57), sinf(-radius + 1.57));
			pos.x += Dir.x * 10 * DXUTGetElapsedTime();
			pos.z += Dir.y * 10 * DXUTGetElapsedTime();
			
		}
	}
	if (Left_Uper == true)
	{
		
		
		if (timer->GetTime() >= 0.75)
		{
			Left_Uper = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (Right_Punch == true)
	{
		
		if (timer->GetTime() >= 0.75)
		{
			Right_Punch = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (LEftRoll == true)
	{
		if (timer->GetTime() >= 0.65)
		{
			LEftRoll = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (LEftRoll)
	{
		Dir = Vec2(cosf(-radius + 1.57), sinf(-radius + 1.57));
		pos.x += Dir.x * 20 * DXUTGetElapsedTime();
		pos.z += Dir.y * 20 * DXUTGetElapsedTime();
	}
	if (RightRoll == true)
	{
		if (timer->GetTime() >= 0.65)
		{
			RightRoll = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (RightRoll)
	{
		Dir = Vec2(cosf(-radius - 1.57), sinf(-radius - 1.57));
		pos.x += Dir.x * 20 * DXUTGetElapsedTime();
		pos.z += Dir.y * 20 * DXUTGetElapsedTime();
	}
	if (FrontRoll == true)
	{
		if (timer->GetTime() >= 0.65)
		{
			FrontRoll = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (FrontRoll)
	{
		Dir = Vec2(cosf(-radius), sinf(-radius));
		pos.x += Dir.x * 20 * DXUTGetElapsedTime();
		pos.z += Dir.y * 20 * DXUTGetElapsedTime();
	}
	if (BackRoll == true)
	{
		if (timer->GetTime() >= 0.65)
		{
			BackRoll = false;
			timer->Reset();
			timer->Stop();
		}
	}
	if (BackRoll)
	{
		Dir = Vec2(cosf(-radius - 3.14), sinf(-radius - 3.14));
		pos.x += Dir.x * 20 * DXUTGetElapsedTime();
		pos.z += Dir.y * 20 * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(0x53))
	{


		if (LEftRoll || RightRoll || FrontRoll || BackRoll)
		{

		}
		else if (Right_Punch|| Left_Uper)
		{

		}
		else if (DXUTWasKeyPressed(VK_SPACE))
		{
			timer->Start();
			BackRoll = true;
		}
		else
		{
			Dir = Vec2(cosf(-radius - 3.14), sinf(-radius - 3.14));
			pos.x += Dir.x * 10 * DXUTGetElapsedTime();
			pos.z += Dir.y * 10 * DXUTGetElapsedTime();
		}
	}
	if (DXUTIsKeyDown(0x44))
	{
		if (LEftRoll || RightRoll || FrontRoll || BackRoll)
		{

		}
		else if (Right_Punch || Left_Uper)
		{

		}
		else if (DXUTWasKeyPressed(VK_SPACE))
		{
			timer->Start();
			RightRoll = true;
		}
		else
		{
			Dir = Vec2(cosf(-radius - 1.57), sinf(-radius - 1.57));
			pos.x += Dir.x * 10* DXUTGetElapsedTime();
			pos.z += Dir.y * 10 * DXUTGetElapsedTime();
		}
	}
	if (LEftRoll || RightRoll || FrontRoll || BackRoll)
	{

	}
	else if (Left_Uper || Right_Punch)
	{

	}
	else if (DXUTIsKeyDown(VK_LBUTTON))
	{
		ttts.SetPos(Vec3(pos.x +3 * Dir.x, 3, pos.z + 3 * Dir.y));
		ttts.SetRot(Vec3(0, 0, 0));
		ttts.SetScale(Vec3(1, 1, 1));
		ttts.GetMesh = ts.GetMesh;
		ttts.SetWorldMatrix();
		CollObj.push_back(OBJMANAGER->AddObject(new CollisionBox(ttts,true,"",0.75),1));
		timer->Start();
		Left_Uper = true;

	}
	else if (DXUTIsKeyDown(VK_RBUTTON))
	{
		ttts.SetPos(Vec3(pos.x + 3 * Dir.x, 3, pos.z + 3 * Dir.y));
		ttts.SetRot(Vec3(0, 0, 0));
		ttts.SetScale(Vec3(1, 1, 1));
		ttts.GetMesh = ts.GetMesh;
		ttts.SetWorldMatrix();
		CollObj.push_back(OBJMANAGER->AddObject(new CollisionBox(ttts, true, "", 0.75), 1));
		timer->Start();
		Right_Punch = true;

	}
	CamR.x = pos.x - 10 * cos(radius);
	CamR.z = pos.z + 10 * sin(radius);
	CamPos = CamR * 1;
	CamAt.x = pos.x + 10 * cos(radius);
	CamAt.z = pos.z - 10 * sin(radius);
	CamPos.y = pos.y + 6;

	SetCursorPos(WINSIZEX / 2, WINSIZEY / 2);


}

void Player::Render()
{
	//hiteffect->Render(0.03,ts);
	if (LEftRoll || RightRoll || FrontRoll || BackRoll)
	{
		RollPunch->Render(0.01, ts);
	}
	else if (Right_Punch)
	{
		LeftPunch->Render(0.01, ts);
	}
	else if (Left_Uper)
	{
		ts.SetScale(Vec3(-0.2, 0.2, 0.2));

		LeftUper->Render(0.01,ts);
	}
	else
	{
		LeftPunch->i = 0;
		LeftUper->i = 0;
		RollPunch->i = 0;
		ts.SetScale(Vec3(0.2, 0.2, 0.2));

		
		if (DXUTIsKeyDown(0x57))
		{
			meshRun->Render(0.01, ts);
			ts.SetRot(Vec3(D3DXToDegree(radius + 1.55), 0, 0));

		}
		else if (DXUTIsKeyDown(0x41))
		{
			meshRun->Render(0.01, ts);
			ts.SetRot(Vec3(D3DXToDegree(radius), 0, 0));

		}
		else if (DXUTIsKeyDown(0x53))
		{
			meshRun->Render(0.01, ts);
			ts.SetRot(Vec3(D3DXToDegree(radius - 1.55), 0, 0));

		}
		else if (DXUTIsKeyDown(0x44))
		{
			meshRun->Render(0.01, ts);
			ts.SetRot(Vec3(D3DXToDegree(radius + 3.1), 0, 0));

		}
		else
		{
			mesh->Render(0.01, ts);
		}
	}

	CAM->SetCamPos(Vec3(CamPos));
	CAM->SetCamLook(Vec3(CamAt.x, -1, CamAt.z));
	//ts.Pos = Vec3(0, 0, 0);
	ts.SetPos(pos);

	ts.SetWorldMatrix();
	//mesh->Render(0.03, ts);

	if (Hp <= 0)
	{
		ObjDel();
	}
}

void Player::UIRender()
{
}

void Player::Collision(Object* obj)
{
	if (obj->ObjTag == "Block")
	{
	}
	if (obj->ObjTag == "NormalEnemy")
	{
		//Hp--;
		Dir = Vec2(cosf(-radius - 3.14), sinf(-radius - 3.14));
		pos.x += Dir.x * 5;
		pos.z += Dir.y * 5;
	}
}
