#include "DXUT.h"
#include "Main.h"
#include "ingameScene.h"
Main::Main()
{

}

Main::~Main()
{

}

void Main::Init()
{
	LOADER->AddImages("HitEffect", "./Resource/HitEffect/", 4);

	//Run_000001
	//씬
	SCENE->AddScene("ingame",new ingameScene);
	//3D오브젝트
	LOADER->AddMesh("Enemy","./Resource/Ditto/Enemy.obj");
	LOADER->AddMesh("Cat","./Resource/ll/cat.obj");
	LOADER->AddMesh("BackGround","./Resource/BG1.obj");
	LOADER->AddMesh("BacksGround", "./Resource/Run/Run_000001.obj");
	LOADER->AddMesh("Block","./Resource/DirtBlock.obj");
	LOADER->AddMesh("CollBox", "./Resource/CollBox.obj");

	//3D 애니메이션
	LOADER->AddMeshs("PlayerRun","./Resource/Run/(",21);
	LOADER->AddMeshs("PlayerIdle", "./Resource/Idle/(", 57);
	LOADER->AddMeshs("PlayerRightPunch", "./Resource/RightPunch/(", 30);
	LOADER->AddMeshs("PlayerLeftPunch", "./Resource/LeftPunch/(", 39);
	LOADER->AddMeshs("PlayerRoll", "./Resource/Roll/(", 35);
	LOADER->AddMeshs("PlayerLeftUper", "./Resource/Uper/(", 40);

	//2D 이미지
	LOADER->AddImage("fdas","./media/cup.jpg");
	//2D 애니메
	SCENE->ChangeScene("ingame");
	ts.SetPos(Vec3(0,-10,0));
	ts.SetRot(Vec3(0, 0, 0));
	ts.SetScale(Vec3(10,10,10));
	tts.SetPos(Vec3(0,0,0));
	tts.SetRot(Vec3(0,0,0));
	tts.SetScale(Vec3(1,1,1));
	tts.SetWorldMatrix();
}

void Main::Update()
{
	OBJMANAGER->Update();
	SCENE->Update();
}

void Main::Render()
{
	
	RENDER3D->BoxRender(tts);

	SCENE->Render();
	OBJMANAGER->Render();
	RENDER2D->Begin();
	SCENE->UIRender();
	OBJMANAGER->UIRender();
	RENDER2D->End();

	
}

void Main::Release()
{
	SceneManager::ReleaseIntacne();
	cMeshLoader::ReleaseIntacne();
	CamManager::ReleaseIntacne();
	LoadManager::ReleaseIntacne();
	Render2DManager::ReleaseIntacne();
	Render3DManager::ReleaseIntacne();
	ObjectManager::ReleaseIntacne();
}

void Main::ResetDevice()
{
	RENDER2D->ResetDevice();
}

void Main::LostDevice()
{
	RENDER2D->LostDevice();
}
