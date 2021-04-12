#pragma once
class Main
{
private:
	Mesh* mesh;
	Texture* text;
	float x=0;
	float y=0;
	Transform tts;
	MultiMesh* meshs;
	Transform ts;
public:
	Main();
	~Main();
public:
	void Init();
	void Update();
	void Render();
	void Release();
	void ResetDevice();
	void LostDevice();
};

