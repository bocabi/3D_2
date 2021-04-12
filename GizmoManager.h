#pragma once
#include "singleton.h"
#define CIRCLEGIZMO_SEGMENTS 36
class GizmoManager : public singleton<GizmoManager>
{
private :
	typedef struct tagGIZMOVERTEX
	{
		Vec3 pos;
		DWORD color;
		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
	}GIZMOVERTEX,*LPGIZMOVERTEX;
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	Vec3 pCirclePos[CIRCLEGIZMO_SEGMENTS +1];
public:
	GizmoManager();
	~GizmoManager();

	HRESULT Init(LPDIRECT3DDEVICE9 pDevice);
	void Release();
	void Line(const Vec3& startpos, const Vec3& endpos, DWORD color = 0xff808080) const;

	void Circle(const Vec3 & centerpos,float radius,DWORD color = 0xff808080)const;

	void AABBBox(const Vec3& minpos, const Vec3& maxpos, DWORD color = 0xff808080)const;
};

#define GIZMO_MGR GizmoManager::GetInstance()

