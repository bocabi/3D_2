#pragma once
#include "singleton.h"

class Render2DManager : public singleton<Render2DManager>
{
private:
	LPD3DXFONT Font = nullptr;
	LPD3DXSPRITE Sprite = nullptr;
	CDXUTTimer* timer;
public:
	Render2DManager();
	~Render2DManager();
public:
	void Begin();
	void End();
	void ResetDevice();
	void LostDevice();
	void TextDrawn(string str, Vec2 pos, float size, bool Center, D3DCOLOR color);

	void BillRender(Texture *  texturePtr, Transform ts);

	void Render(Texture* texturePtr, Vec2 Pos, Vec2 size = Vec2(1, 1), float rot = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(Texture * texturePtr,Vec2 Pos , Vec2 size = Vec2(1,1),float rot = 0,D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));
	//void AnimeRender(MultiTexture* texturePtr, Vec2 Pos, Vec2 size = Vec2(1, 1), float rot = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255),float frame = 0);

};

#define RENDER2D Render2DManager::GetInstance()