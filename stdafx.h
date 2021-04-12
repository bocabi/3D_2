#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <istream>
#include <ostream>
#include <string>
#include <dinput.h>

#

using namespace std;
static float TimeScale = 1;
#define VERTEXFVF D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1
#define FLOATEQUAL(a, b) ( abs((a) - (b)) < EPSILON )

#define Device DXUTGetD3D9Device()
#define Vec2 D3DXVECTOR2
#define Vec3 D3DXVECTOR3
#define DTime DXUTGetElapsedTime() * TimeScale
inline const int WINSIZEX = 1920;
inline const int WINSIZEY = 1080;

struct Texture
{
public:
	IDirect3DTexture9* texturePtr;
	D3DXIMAGE_INFO info;
public:
	Texture(IDirect3DTexture9* texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}
	~Texture()
	{
	}
};


struct Material
{
public:
	string mtlName;

	D3DMATERIAL9 material;
	Texture* DiffuseMap = nullptr;
	Texture* specularMap = nullptr;

	float fAlpha;
	float fIllum;
	float fNs;

	Material()
		:fAlpha(1.f), fIllum(0.f), fNs(0.f)
	{
		material.Power = 1;
	}
	~Material() {

	}


};

struct Mesh
{
public:
	bool bNoneDelete = false;
	Vec3 box1;
	Vec3 box2;
	Vec3 box3;
	Vec3 box4;

	LPD3DXMESH lpD3DXMesh;
	std::vector<Material*> vMaterial;
	Vec3 minVec = Vec3(0,0,0);
	Vec3 maxVec = Vec3(0,0,0);
	Material* GetMaterial(int index)
	{
		
		return vMaterial[index];
	}

	Texture* GetDiffuseMap(int index)
	{
		return vMaterial[index]->DiffuseMap;
	}
	Texture* GetSpecularMap(int index)
	{
		return vMaterial[index]->specularMap;
	}
	Mesh()
		: lpD3DXMesh(nullptr) {}
	~Mesh()
	{
		for (auto iter : vMaterial)
			SAFE_DELETE(iter);

		vMaterial.clear();

		SAFE_RELEASE(lpD3DXMesh);
	}
};
typedef struct tagRay {
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
}Ray, * LPRay;

struct VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex;

	VERTEX(D3DXVECTOR3 _pos, D3DXVECTOR2 _tex, D3DXVECTOR3 _normal)
		:pos(_pos), tex(_tex), normal(_normal)
	{}
	~VERTEX() {

	}
};

struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

struct Transform
{
	float PlusPower = 0;
	CDXUTTimer* timer;
	Mesh *GetMesh;
	Vec3 Pos; Vec3 Rot; Vec3 Size;
	float GravityPower = 0;
	D3DXMATRIX matP, matS, matR, matW;
	D3DXQUATERNION q;
	float Radius;
	void SetScale(Vec3 size)
	{
		Size = size;
		D3DXMatrixScaling(&matS, size.x, size.y, size.z);
	}
	void SetPos(Vec3 pos)
	{
		Pos.x = pos.x;
		Pos.z = pos.z;

		Pos.y = pos.y + GravityPower;
		D3DXMatrixTranslation(&matP, Pos.x, Pos.y, Pos.z);
	}

	void SetRot(Vec3 rot)
	{
		Rot = rot;
		D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(rot.x), D3DXToRadian(rot.y), D3DXToRadian(rot.z));
		D3DXMatrixRotationQuaternion(&matR, &q);
	}
	void SetWorldMatrix()
	{
		matW =   matS * matR * matP;
	}
	D3DXMATRIXA16 GetMat()
	{
		return matW;
	}
	
};
#include "CamManager.h"
#include "MeshLoader.h"
#include "SceneManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "Render2DManager.h"
#include "Render3DManager.h"
#include "BoundingBox.h"
#include "Collision.h"
#include "GizmoManager.h"
#include "Collision.h"


