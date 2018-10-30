#include "stdafx.h"
#include "DrawLandscape.h"
#include "../Landscape/Terrain.h"
DrawLandscape::DrawLandscape(ExecuteValues * values)
	:Execute(values)
{
	//Create Terrain
	{
		wstring heightMap = Contents + L"HeightMaps/HeightMap256.png";
		Material* material = new Material(Shaders + L"010_Terrain.hlsl");
		material->SetDiffuseMap(Textures + L"Dirt2.png");

		terrain = new Terrain(material, heightMap);
	}
}

DrawLandscape::~DrawLandscape()
{
	SAFE_DELETE(terrain);
}

void DrawLandscape::Update()
{
	terrain->Update();
}

void DrawLandscape::PreRender()
{

}

void DrawLandscape::Render()
{
	terrain->Render();
}

void DrawLandscape::PostRender()
{

}

void DrawLandscape::ResizeScreen()
{
}
