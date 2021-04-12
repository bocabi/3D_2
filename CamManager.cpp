#include "DXUT.h"
#include "CamManager.h"

CamManager::CamManager()
{
	CamPos = Vec3(0,0,0);
	CamAt = D3DXVECTOR3(0, 0, 10);
	CamUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH(&matView, &CamPos, &CamAt, &CamUp);
	Device->SetTransform(D3DTS_VIEW, &matView);
}

CamManager::~CamManager()
{
}

void CamManager::SetCamPos(Vec3 pos)
{
	CamPos = pos;
	CamUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH(&matView, &CamPos, &CamAt, &CamUp);
	Device->SetTransform(D3DTS_VIEW, &matView);
}

void CamManager::SetCamLook(Vec3 look)
{
	CamAt = D3DXVECTOR3(look.x, look.y, look.z);
	CamUp = D3DXVECTOR3(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH(&matView, &CamPos, &CamAt, &CamUp);
	Device->SetTransform(D3DTS_VIEW, &matView);
}

Vec2 CamManager::GetCamPos()
{
    return Vec2();
}
