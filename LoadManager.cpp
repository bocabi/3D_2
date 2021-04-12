#include "DXUT.h"
#include "LoadManager.h"

LoadManager::LoadManager()
{
	Loader = new cMeshLoader;

}

LoadManager::~LoadManager()
{
	for (auto iter : m_Texture)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();
	for (auto iter : m_Mesh)
	{
		SAFE_DELETE(iter.second);
	}
	m_Mesh.clear();
	for (auto iter : m_MultiMesh)
	{
		SAFE_DELETE(iter.second);
	}
	m_MultiMesh.clear();
	for (auto iter : m_MultiTexture)
	{
		SAFE_DELETE(iter.second);
	}
	m_MultiTexture.clear();
	SAFE_DELETE(Loader);
}

Texture* LoadManager::AddImage(const string& key, const string& path)
{
	auto find = m_Texture.find(key);
	if (find == m_Texture.end())
	{
		D3DXIMAGE_INFO info;
		IDirect3DTexture9* texturePtr;
		if (D3DXCreateTextureFromFileExA(Device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			Texture* text = new Texture(texturePtr, info);
			m_Texture[key] = text;
			return text;
		}
		return nullptr;
	}
	return find->second;
}

MultiTexture* LoadManager::AddImages(const string& key, const string& Folder, int count)
{

	auto find = m_MultiTexture.find(key);
	if (find == m_MultiTexture.end())
	{
		MultiTexture* Multi = new MultiTexture();

		for (int i = 0; i < count; i++)
		{
			D3DXIMAGE_INFO info;
			LPDIRECT3DTEXTURE9 texturePtr;
			string a;
			a = Folder;
			a.push_back(to_string(i).at(0));
			a.push_back('.');
			a.push_back('p');
			a.push_back('n');
			a.push_back('g');
			if (D3DXCreateTextureFromFileExA(Device, a.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
			{
				Texture* text = new Texture(texturePtr, info);
				Multi->v_Text.push_back(text);
				cout << a;
			}
		}
		m_MultiTexture[key] = Multi;

		return m_MultiTexture[key];
	}
	return find->second;
}

Texture* LoadManager::FindImage(const string& key)
{
	auto find = m_Texture.find(key);
	if (find == m_Texture.end())
	{
		return nullptr;
	}
	return find->second;
}

MultiTexture* LoadManager::FindImages(const string& key)
{
	auto find = m_MultiTexture.find(key);
	if (find == m_MultiTexture.end())
	{
		return nullptr;
	}
	return find->second;
}


Mesh* LoadManager::AddMesh(const string& key, string strFilename)
{
	auto find = m_Mesh.find(key);
	if (find != m_Mesh.end())
	{
		return find->second;
	}

	Mesh* mesh = new Mesh;
	Loader->ObjLoad(mesh, strFilename);
	m_Mesh[key] = mesh;
	return m_Mesh[key];
}

MultiMesh* LoadManager::AddMeshs(const string& key, string strFilename, int count)
{
	auto find = m_MultiMesh.find(key);
	if (find != m_MultiMesh.end())
	{
		return find->second;
	}

	MultiMesh* meshs = new MultiMesh;
	for (int i = 1; i <= count; i++)
	{
		Mesh* mesh = new Mesh;
		string path = strFilename;
		if (i < 10)
		{
			path.push_back('0');
			path.push_back(to_string(i).at(0));
		}
		else
		{
			path.push_back(to_string(i).at(0));
			path.push_back(to_string(i).at(1));
		}

		path.push_back('.');
		path.push_back('o');
		path.push_back('b');
		path.push_back('j');


		cout << path;

		Loader->ObjLoad(mesh, path);


		meshs->v_mesh.push_back(mesh);
	}
	m_MultiMesh.insert(make_pair(key, meshs));


	return m_MultiMesh[key];
}

Mesh* LoadManager::FindMesh(const string& key)
{
	auto find = m_Mesh.find(key);
	if (find == m_Mesh.end())
	{
		return nullptr;
	}
	return find->second;
}

MultiMesh * LoadManager::FindMeshs(const string& key)
{
	auto find = m_MultiMesh.find(key);
	if (find == m_MultiMesh.end())
	{
		return nullptr;
	}
	return find->second;
}

