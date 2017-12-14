#pragma once
#include "Singleton.h"


struct texture
{
	LPDIRECT3DTEXTURE9 lpd3dTex;
	D3DXIMAGE_INFO info;

	void DrawImage(float x, float y, float angle = 0.0f, int alpha = 255.0f);
};


class ImageManager : public Singleton<ImageManager>
{
private:
	LPD3DXSPRITE lpd3dSprite;

	int Init();
	int Release();

public:
	HRESULT Begin();
	void End();

	void LostDevice();
	void ResetDevice();

	texture* AddImage(LPCSTR lpPath);
	void DrawImage(texture* pTexture, float x, float y, float angle = 0.0f, int alpha = 255.0f);
	void DrawFrameImage(texture* pTexture, int wc, int hc, int wi, int hi, float x, float y, float angle = 0.0f, int alpha = 255.0f);

	ImageManager();
	virtual ~ImageManager();
};

#define IMAGEMANAGER ImageManager::GetSingleton()