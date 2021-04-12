#pragma once
#include "Scene.h"
#include "singleton.h"
class SceneManager : public singleton<SceneManager>
{
private :
	Scene* nowScene = nullptr;
	Scene* NextScene = nullptr;
	map< string,Scene*> m_scene;
public:
	SceneManager();
	~SceneManager();
public :
	Scene * AddScene(string key,Scene* newScene);
	void ChangeScene(string key);
	void Update();
	void Render();
	void UIRender();
	void Release();
};

#define SCENE SceneManager::GetInstance()