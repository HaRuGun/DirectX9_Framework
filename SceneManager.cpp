#include "stdafx.h"


void SceneManager::Init()
{
	pCurrentScene = &sMain;
	sMain.Init();
}


void SceneManager::Release()
{
	pCurrentScene->Release();
}


void SceneManager::Update(double deltaTime)
{
	pCurrentScene->Update(deltaTime);
}


void SceneManager::Render()
{
	pCurrentScene->Render();
}


// Custom


void SceneManager::ChageScene(Scene* pScene)
{
	if (pScene)
	{
		pCurrentScene->Release();
		pCurrentScene = pScene;
		pScene->Init();
	}
	return;
}