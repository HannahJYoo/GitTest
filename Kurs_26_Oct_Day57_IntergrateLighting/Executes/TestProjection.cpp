#include "stdafx.h"
#include "TestProjection.h"

#include "../Objects/GameAnimModel.h"
#include "../Objects/MeshPlane.h"
#include "../Lights/Projection.h"


TestProjection::TestProjection(ExecuteValues * values)
	:Execute(values)
{
	hanjoShader = new Shader(Shaders + L"025_Animation.hlsl");
	planeShader = new Shader(Shaders + L"042_Plane.hlsl");

	hanjo = new GameAnimModel(Models + L"Kachujin/", L"Kachujin.material", Models + L"Kachujin/", L"Kachujin.mesh");
	hanjo->SetShader(hanjoShader);
	
	hanjo->Scale(0.025f, 0.025f, 0.025f);

	hanjo->AddClip(Models + L"Kachujin/Samba_Dance.anim");
	hanjo->Play(0,true,0,10.0f);

	plane = new MeshPlane();
	plane->SetShader(planeShader);
	plane->Scale(10, 1, 10);
	plane->SetDiffuse(0, 1, 1, 1);
	//plane->SetDiffuseMap(Textures + L"Floor.png");

	projection = new Projection(values);
	//projection->Add(hanjo);
	projection->Add(plane);

}

TestProjection::~TestProjection()
{
	SAFE_DELETE(projection);
	SAFE_DELETE(planeShader);
	SAFE_DELETE(plane);
	SAFE_DELETE(hanjoShader);
	SAFE_DELETE(hanjo);
	
}

void TestProjection::Update()
{
	projection->Update();
	//plane->Update();
	hanjo->Update();
}

void TestProjection::PreRender()
{

}


void TestProjection::Render()
{
	projection->Render();
	//plane->Render();
	hanjo->Render();
}

void TestProjection::PostRender()
{

}
