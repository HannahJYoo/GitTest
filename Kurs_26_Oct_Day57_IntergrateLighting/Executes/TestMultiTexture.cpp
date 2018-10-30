#include "stdafx.h"
#include "TestMultiTexture.h"

#include "../Objects/MeshQuad.h"


TestMultiTexture::TestMultiTexture(ExecuteValues * values)
	:Execute(values)
{
	shader = new Shader(Shaders + L"041_MultiTexture.hlsl");
	quad = new MeshQuad();
	quad->SetShader(shader);
	quad->Scale(10, 10, 1);
	
	quad->SetDiffuseMap(Textures + L"Floor.png");
	quad->SetNormalMap(Textures + L"Dirt.png");

	buffer = new Buffer();
}

TestMultiTexture::~TestMultiTexture()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(quad);
	SAFE_DELETE(buffer);

}

void TestMultiTexture::Update()
{
	quad->Update();
}

void TestMultiTexture::PreRender()
{

}


void TestMultiTexture::Render()
{
	ImGui::SliderInt("Selected", &buffer->Data.Selected, -1, 11);
	buffer->SetPSBuffer(10);
	quad->Render();


}

void TestMultiTexture::PostRender()
{

}
