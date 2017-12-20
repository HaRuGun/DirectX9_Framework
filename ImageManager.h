#pragma once
#include "Singleton.h"


struct texture
{
	LPDIRECT3DTEXTURE9 lpd3dTex;
	D3DXIMAGE_INFO info;
};


struct matrix
{
public:
	float width, height;
	float x, y;
	float velocity, direction;
};


struct frameData
{
public:
	int wCount, hCount;
	int wIndex, hIndex;
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
	void DrawImage(texture* pTexture, matrix mat, int alpha = 255.0f);
	void DrawFrameImage(texture* pTexture, frameData frame, matrix mat, int alpha = 255.0f);

	ImageManager();
	virtual ~ImageManager();
};

#define IMAGEMANAGER ImageManager::GetSingleton()