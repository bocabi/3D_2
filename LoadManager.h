#pragma once
#include "singleton.h"
#include "Render2DManager.h"
#include "Render3DManager.h"
struct MultiMesh
{
public:
	CDXUTTimer* timer;
	MultiMesh() { timer = new CDXUTTimer; }
	~MultiMesh() { SAFE_DELETE(timer) for (auto iter : v_mesh)SAFE_DELETE(iter); v_mesh.clear(); };
	vector<Mesh*>v_mesh;
	int a = 1;
	int i = 0;

	void Render(float Frame, Transform ts)
	{
		if (a == 1)
		{
			timer->Start();
			a--;
		}
		RENDER3D->Render(v_mesh[i], ts);
		if (Frame < timer->GetTime())
		{
			timer->Reset();
			i++;
		}
		if (i >= v_mesh.size())
		{
			i = 0;
		}
	}


};
struct MultiTexture
{
public:
	list<Texture*> l_Texture;

public:
	CDXUTTimer* timer;
	vector<Texture*>v_Text;
	MultiTexture() 
	{ 
		timer = new CDXUTTimer; 
	}
	~MultiTexture() 
	{ 
		SAFE_DELETE(timer) 
			for (auto iter : v_Text)
			{
				(*iter).texturePtr->Release();
				SAFE_DELETE(iter);
			}

		v_Text.clear(); 
	};
	int a = 1;
	int i = 0;
	
	void Render(float Frame, Transform ts)
	{
		if (a == 1)
		{
			timer->Start();
			a--;
		}
		RENDER2D->BillRender(v_Text[i], ts);
		if (Frame < timer->GetTime())
		{
			timer->Reset();
			i++;
		}
		if (i >= v_Text.size())
		{
			i = 0;
		}
	}
};
class LoadManager :public singleton<LoadManager>
{
private:
	map <string, Texture*>m_Texture;
	map <string, MultiTexture*> m_MultiTexture;
	map <string, Mesh*> m_Mesh;
	map <string, MultiMesh*> m_MultiMesh;
	cMeshLoader* Loader;
public:
	LoadManager();
	~LoadManager();
public:
	Texture* AddImage(const string& key, const string& path);
	MultiTexture* AddImages(const string& key, const string& path, int count = 0);

	Texture* FindImage(const string& key);
	MultiTexture* FindImages(const string& key);

	Mesh* AddMesh(const string& key, string strFilename);
	MultiMesh* AddMeshs(const string& key, string strFilename, int count);
	Mesh* FindMesh(const string& key);
	MultiMesh* FindMeshs(const string& key);

};

#define LOADER LoadManager::GetInstance()
