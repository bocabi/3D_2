#pragma once
#include "singleton.h"
class Render3DManager : public singleton<Render3DManager>
{
private:
	D3DXQUATERNION q;

	struct sVerTex
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR2 uv;
		D3DXVECTOR3 normal;
		inline static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	};
	CDXUTTimer* timer = new CDXUTTimer;

	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;
	D3DXMATRIXA16 matProj;
public:
	Render3DManager();
	~Render3DManager();
public:
	void BoxRender(Transform ts);
	void Render(Mesh* mesh, Transform transform);
	void BackRender(Mesh* mesh, Transform transform);

};

#define RENDER3D Render3DManager::GetInstance()