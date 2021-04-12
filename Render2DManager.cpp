#include "DXUT.h"
#include "Render2DManager.h"

Render2DManager::Render2DManager()
{
	D3DXCreateSprite(Device, &Sprite);
	timer = new CDXUTTimer;
}

Render2DManager::~Render2DManager()
{
	Sprite->Release();
	SAFE_DELETE(timer);
}

void Render2DManager::Begin()
{
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Render2DManager::End()
{
	Sprite->End();
}

void Render2DManager::ResetDevice()
{
	Sprite->OnResetDevice();
}

void Render2DManager::LostDevice()
{
	Sprite->OnLostDevice();
}

void Render2DManager::TextDrawn(string str, Vec2 pos, float size, bool Center, D3DCOLOR color)
{
	D3DXMATRIXA16 mat;
	if (!Center)
	{
		D3DXCreateFontA(Device, size, 0, 10, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, "Comic Sans Ms", &Font);
		D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	}
	else
	{
		D3DXCreateFontA(Device, size, 0, 0, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, "Comic Sans Ms", &Font);
		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2.f, 0);
	}
	Sprite->SetTransform(&mat);
	Font->DrawTextA(Sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);
	SAFE_RELEASE(Font);
}

void Render2DManager::BillRender(Texture * texturePtr, Transform ts)
{
	ts.SetScale(Vec3(40,1,40));
	ts.SetRot(Vec3(0,90,0));
	ts.SetWorldMatrix();
	Device->SetTransform(D3DTS_WORLD, &ts.GetMat());
	Device->SetTexture(0, texturePtr->texturePtr);
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void Render2DManager::Render(Texture* texturePtr, Vec2 Pos, Vec2 size, float rot, D3DCOLOR color)
{
	D3DXMATRIXA16 mat;
	if (texturePtr == nullptr)
	{
		return;
	}
	else
	{
		D3DXMatrixTransformation2D(&mat, nullptr, 0, &size, nullptr, rot, &Pos);
		Sprite->SetTransform(&mat);
		Sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void Render2DManager::CenterRender(Texture* texturePtr, Vec2 Pos, Vec2 size, float rot, D3DCOLOR color)
{
	Render(texturePtr, Vec2(Pos.x - texturePtr->info.Width / 2, Pos.y - texturePtr->info.Height / 2), size, rot, color);
}

//void Render2DManager::AnimeRender(MultiTexture* texturePtr, Vec2 Pos, Vec2 size, float rot, D3DCOLOR color, float frame)
//{
//	timer->Start();
//
//	D3DXMATRIXA16 mat;
//	if (texturePtr == nullptr)
//	{
//		return;
//	}
//	else
//	{
//		D3DXMatrixTransformation2D(&mat, nullptr, 0, &size, nullptr, rot, &Pos);
//		Sprite->SetTransform(&mat);
//		for (auto iter = texturePtr->l_Texture.begin();  iter != texturePtr->l_Texture.end();)
//		{
//			Sprite->Draw((*iter)->texturePtr, nullptr, nullptr, nullptr, color);
//			if (timer->GetTime() > frame)
//			{
//				iter++;
//				timer->Reset();
//			}
//		}
//	}
//}

