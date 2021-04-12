#pragma once
#include "singleton.h"

class cMeshLoader : public singleton<cMeshLoader>
{
private:
	string objPath;
	vector<D3DXVECTOR3> Pos;
	vector<D3DXVECTOR2> TexCoord;
	vector<D3DXVECTOR3> Normal;
	vector<VERTEX> Ver;
	vector<DWORD> Index;
	vector<DWORD> Attribute;
	vector <CacheEntry*> VertexCache;
	string mtlPath;
public:
	cMeshLoader();
	~cMeshLoader();

	void Create(LPD3DXMESH* mesh);
	void MeshLoad(const string& key, Mesh* mesh, const string& mapPath = "None");
	DWORD AddVerTex(UINT hash, VERTEX* pVerTex);
	void ObjLoad(Mesh* mesh, const string& objpath, const string& mapPath = "None");
};