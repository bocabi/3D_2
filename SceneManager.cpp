#include "DXUT.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	Release();
}

Scene * SceneManager::AddScene(string key, Scene* newScene)
{
	if (!newScene)
		return nullptr;
	if (m_scene.find(key) != m_scene.end())
		return nullptr;
	m_scene[key] = newScene;
	return newScene;
}

void SceneManager::ChangeScene(string key)
{
	auto find = m_scene.find(key);
	if (find == m_scene.end())
		return;
	NextScene = find->second;
}

void SceneManager::Update()
{
	if (NextScene)
	{
		if (nowScene)
		{
			nowScene->Release();
		}
		nowScene = NextScene;
		NextScene = nullptr;
		nowScene->init();
	}
	if (nowScene)
	{
		nowScene->Update();
	}
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

void SceneManager::UIRender()
{
	if (nowScene)
		nowScene->UIRender();
}

void SceneManager::Release()
{
	if (nowScene)
	{
		nowScene->Release();
	}
	for (auto iter : m_scene)
	{
		SAFE_DELETE(iter.second);
	}
	m_scene.clear();
}
