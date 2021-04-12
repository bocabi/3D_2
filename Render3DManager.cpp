#include "DXUT.h"
#include "Render3DManager.h"

Render3DManager::Render3DManager()
{
	Device->CreateVertexBuffer(sizeof(sVerTex) * 4, D3DUSAGE_WRITEONLY, sVerTex::FVF, D3DPOOL_DEFAULT, &vb, NULL);


	sVerTex* pVerTices = nullptr;

	vb->Lock(0, 0, (void**)&pVerTices, 0);

	pVerTices[0].Pos = Vec3(-0.5, 0.5, 0);
	pVerTices[1].Pos = Vec3(0.5, 0.5, 0);
	pVerTices[2].Pos = Vec3(-0.5, -0.5, 0);
	pVerTices[3].Pos = Vec3(0.5, -0.5, 0);

	pVerTices[0].uv = Vec2(0, 0);
	pVerTices[1].uv = Vec2(1, 0);
	pVerTices[2].uv = Vec2(0, 1);
	pVerTices[3].uv = Vec2(1, 1);
	
	pVerTices[0].normal = Vec3(0, 0, 0);
	pVerTices[1].normal = Vec3(0, 0, 0);
	pVerTices[2].normal = Vec3(0, 0, 0);
	pVerTices[3].normal = Vec3(0, 0, 0);
	
	vb->Unlock();

	

	Device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, NULL);
	void* pIndice = NULL;

	WORD idx[] = { 1,2,0,1,3,2 };

	ib->Lock(0, 0, &pIndice, 0);
	memcpy(pIndice, idx, sizeof(WORD) * 6);
	ib->Unlock();


	DWORD* Attribute = nullptr;

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Device->SetFVF(sVerTex::FVF);
	Device->SetStreamSource(0, vb, 0, sizeof(sVerTex));
	Device->SetIndices(ib);

	D3DXMatrixOrthoLH(&matProj, WINSIZEX, WINSIZEY, 0, 100);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60), 16.f / 9.f, 1.f, 50000.f);
	Device->SetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 10), &D3DXVECTOR3(0.f, 1.f, 0.f));
	Device->SetTransform(D3DTS_WORLD, &matView);

}

Render3DManager::~Render3DManager()
{
	SAFE_DELETE(timer);
	ib->Release();
	vb->Release();
}

void Render3DManager::BoxRender(Transform ts)
{
	LPD3DXMESH  mesh;
	LPD3DXBUFFER bf;
	
	D3DXCreateBox(Device,ts.Size.x, ts.Size.y, ts.Size.z, &mesh,&bf);
	Device->SetTransform(D3DTS_WORLD,&ts.GetMat());
	Device->SetTexture(0,0);
	mesh->DrawSubset(0);
	mesh->Release();
	
	bf->Release();
}

void Render3DManager::Render(Mesh* mesh, Transform transform)
{
	Device->SetTransform(D3DTS_WORLD, &transform.matW);

	int i = 0;
	for (int i = 0; i < mesh->vMaterial.size(); ++i)
	{
		auto mat = mesh->vMaterial[i];


		Device->SetMaterial(&mat->material);

		if (mat->DiffuseMap != nullptr)
			Device->SetTexture(0, mat->DiffuseMap->texturePtr);
		else
			Device->SetTexture(0, nullptr);

		mesh->lpD3DXMesh->DrawSubset(i);
	}

}

void Render3DManager::BackRender(Mesh* mesh, Transform transform)
{
	Device->SetTransform(D3DTS_WORLD, &transform.matW);


	int i = 0;
	for (int i = 0; i < mesh->vMaterial.size(); ++i)
	{
		auto mat = mesh->vMaterial[i];


		Device->SetMaterial(&mat->material);

		if (mat->DiffuseMap != nullptr)
			Device->SetTexture(0, mat->DiffuseMap->texturePtr);
		else
			Device->SetTexture(0, nullptr);

		mesh->lpD3DXMesh->DrawSubset(i);
	}

}

