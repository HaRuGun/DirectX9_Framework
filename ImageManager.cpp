#include "stdafx.h"


void texture::DrawImage(float x, float y, float angle, int alpha)
{
	IMAGEMANAGER->DrawImage(this, x, y, angle, alpha);
}


//


ImageManager::ImageManager()
{
	Init();
}

ImageManager::~ImageManager()
{
	Release();
}

int ImageManager::Init()
{
	D3DXCreateSprite(lpd3dDevice, &lpd3dSprite);

	return 0;
}


int ImageManager::Release()
{
	SAFE_RELEASE(lpd3dSprite);
	return 0;
}


HRESULT ImageManager::Begin()
{
	return lpd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
}


void ImageManager::End()
{
	lpd3dSprite->End();
}


void ImageManager::LostDevice()
{
	if(lpd3dSprite != nullptr)
		lpd3dSprite->OnLostDevice();
}


void ImageManager::ResetDevice()
{
	if (lpd3dSprite != nullptr)
		lpd3dSprite->OnResetDevice();
}


texture* ImageManager::AddImage(LPCSTR lpPath)
{
	LPDIRECT3DTEXTURE9 lpd3dTex;
	D3DXIMAGE_INFO info;

	D3DXCreateTextureFromFileEx(lpd3dDevice, lpPath, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &lpd3dTex);
	
	texture* dest = new texture;
	dest->lpd3dTex = lpd3dTex;
	dest->info = info;

	return dest;
}


void ImageManager::DrawImage(texture* pTexture, float x, float y, float angle, int alpha)
{
	if (pTexture)
	{
		D3DXMATRIX matTrans;
		D3DXVECTOR3 Center = { (float)pTexture->info.Width / 2, (float)pTexture->info.Height / 2, 0.0f };
		
		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixAffineTransformation2D(&matTrans, 1.0f, nullptr, D3DXToRadian(angle), &D3DXVECTOR2(x, y));
		lpd3dSprite->SetTransform(&matTrans);

		lpd3dSprite->Draw(pTexture->lpd3dTex, nullptr, &Center, nullptr, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, alpha));
	}
}


void ImageManager::DrawFrameImage(texture* pTexture, int wc, int hc, int wi, int hi, float x, float y, float angle, int alpha)
{
	if (pTexture)
	{
		float width = (float)pTexture->info.Width;
		float height = (float)pTexture->info.Height;

		RECT image = { width / wc * wi, height / hc * hi, width / wc * (wi + 1), height / hc * (hi + 1) };
		D3DXMATRIX matTrans;
		D3DXVECTOR3 Center = { width / wc / 2, height / hc / 2, 0.0f };

		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixAffineTransformation2D(&matTrans, 1.0f, nullptr, D3DXToRadian(angle), &D3DXVECTOR2(x, y));
		lpd3dSprite->SetTransform(&matTrans);

		lpd3dSprite->Draw(pTexture->lpd3dTex, &image, &Center, nullptr, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, alpha));
	}
}