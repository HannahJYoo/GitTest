#include "stdafx.h"
#include "TestBlend.h"
#include "../Landscape/Sky.h"
#include "../Landscape/TerrainRender.h"
#include "../Landscape/Water.h"
#include "../Objects/MeshQuad.h"



TestBlend::TestBlend(ExecuteValues * values)
	:Execute(values)
{
	shader = new Shader(Shaders + L"041_BaseTexture.hlsl");

	quad = new MeshQuad();
	quad->SetShader(shader);
	quad->Scale(10, 10, 1);

	quad->SetDiffuseMap(Textures + L"Floor.png");
	quad->SetNormalMap(Textures + L"Dirt.png");

	quad2 = new MeshQuad();
	quad2->SetShader(shader);
	quad2->Scale(10, 10, 1);
	quad2->Position(0, 0, -1);
	quad2->SetDiffuseMap(Textures + L"BlendTest.png");

	buffer = new Buffer();

	blendState[0] = new BlendState();
	blendState[1] = new BlendState();
	blendState[1]->BlendEnable(true);

	blendState[2] = new BlendState();
	blendState[2]->BlendEnable(true);   
	blendState[2]->AlphaToCoverageEnable(true);

	//µ¡¼À
	blendState[3] = new BlendState();
	blendState[3]->BlendEnable(true);
	blendState[3]->DestBlend(D3D11_BLEND_ONE);
	blendState[3]->SrcBlend(D3D11_BLEND_SRC_ALPHA);
	blendState[3]->BlendOp(D3D11_BLEND_OP_ADD);

	//»¬¼À
	blendState[4] = new BlendState();
	blendState[4]->BlendEnable(true);
	blendState[4]->DestBlend(D3D11_BLEND_ONE);
	blendState[4]->SrcBlend(D3D11_BLEND_SRC_ALPHA);
	blendState[4]->BlendOp(D3D11_BLEND_OP_REV_SUBTRACT);

	//°ö¼À
	blendState[5] = new BlendState();
	blendState[5]->BlendEnable(true);
	blendState[5]->DestBlend(D3D11_BLEND_SRC_COLOR);
	blendState[5]->SrcBlend(D3D11_BLEND_ZERO);
	blendState[5]->BlendOp(D3D11_BLEND_OP_ADD);

	//Á¦°ö
	blendState[6] = new BlendState();
	blendState[6]->BlendEnable(true);
	blendState[6]->DestBlend(D3D11_BLEND_DEST_COLOR);
	blendState[6]->SrcBlend(D3D11_BLEND_ZERO);
	blendState[6]->BlendOp(D3D11_BLEND_OP_ADD);

	//³×°ÅÆ¼³×ÀÌ¼Ç Æ÷ÁöÆ¼ºê
	blendState[7] = new BlendState();
	blendState[7]->BlendEnable(true);
	blendState[7]->DestBlend(D3D11_BLEND_ZERO);
	blendState[7]->SrcBlend(D3D11_BLEND_INV_DEST_COLOR);
	blendState[7]->BlendOp(D3D11_BLEND_OP_ADD);

	//texture1
	blendState[8] = new BlendState();
	blendState[8]->BlendEnable(true);
	blendState[8]->DestBlend(D3D11_BLEND_ONE);
	blendState[8]->SrcBlend(D3D11_BLEND_ZERO);
	blendState[8]->BlendOp(D3D11_BLEND_OP_ADD);

	//texture2
	blendState[9] = new BlendState();
	blendState[9]->BlendEnable(true);
	blendState[9]->DestBlend(D3D11_BLEND_ZERO);
	blendState[9]->SrcBlend(D3D11_BLEND_ONE);
	blendState[9]->BlendOp(D3D11_BLEND_OP_ADD);


}

TestBlend::~TestBlend()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(quad);
	SAFE_DELETE(quad2);
	SAFE_DELETE(buffer);
	

}

void TestBlend::Update()
{
	quad->Update();
	quad2->Update();
}

void TestBlend::PreRender()
{

}


void TestBlend::Render()
{
	string str[] = { "","Default","AlphaToCoverage","Plus","Minus","Multiple","Qa","NegatinationPositiv","Tex1","Tex2" };
	
	ImGui::SliderInt("AlphaBlend", &buffer->Data.Selected, 0, 9);
	ImGui::Text(str[buffer->Data.Selected].c_str());
	
	quad->Render();

	blendState[buffer->Data.Selected]->OMSetBlendState();

	quad2->Render();

	blendState[0]->OMSetBlendState();

}

void TestBlend::PostRender()
{
	
}
