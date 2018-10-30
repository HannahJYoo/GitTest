#include "stdafx.h"
#include "TestAmbient.h"

#include "./Objects/MeshPlane.h"
#include "./Objects/MeshCube.h"
#include "./Objects/MeshSphere.h"
#include "./Objects/MeshBunny.h"


TestAmbient::TestAmbient(ExecuteValues * values)
	:Execute(values)
{
	shader = new Shader(Shaders + L"045_Lighting.hlsl");

	plane = new MeshPlane();
	plane->SetShader(shader);
	plane->SetDiffuse(1, 1, 1);
	plane->Scale(10, 1, 10);

	cube = new MeshCube();
	cube->SetShader(shader);
	cube->SetDiffuse(0, 1, 0);

	//cube->Position(-10, 1.5f, 0);
	//cube->Scale(3,3,3);
	cube->Position(0, 10.0f, 0);
	cube->Scale(1, 1, 1);

	sphere = new MeshSphere();
	sphere->SetShader(shader);
	sphere->SetDiffuse(0, 0, 1);

	sphere->Position(10, 1.5f, 0);
	sphere->Scale(3, 3, 3);

	sphere2 = new MeshSphere();
	sphere2->SetShader(shader);
	sphere2->SetDiffuse(1, 1, 1);
		  
	sphere2->Position(10, 1.5f, 10);
	sphere2->Scale(3, 3, 3);

	bunny = new MeshBunny();
	bunny->SetShader(shader);
	bunny->SetDiffuse(1, 1, 1);
	bunny->SetDiffuseMap(Textures + L"White.png");

	bunny->Scale(0.02f, 0.02f, 0.02f);
	bunny->Position(0, 5.0f, 0);
	//Create LightBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		/*
			D3D11_USAGE_DEFAULT = 0		-> gpu, cpu 모두에서 읽고 쓰기 가능.
			D3D11_USAGE_IMMUTABLE = 1	-> gpu에서만 읽기만 가능, cpu에서 접근금지.
			D3D11_USAGE_DYNAMIC = 2		-> gpu에서는 읽기만 가능, cpu에서는 쓰기만 가능, updatesubresource 허용안함.
			D3D11_USAGE_STAGING = 3		-> gpu에서 cpu로 값 전달이 필요할 때 (ex.shader에서 값을 리턴받아올 때)
		*/
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.ByteWidth = sizeof(LightData);

		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
		assert(SUCCEEDED(hr));
	}


}

TestAmbient::~TestAmbient()
{
	
	SAFE_DELETE(lightBuffer);
	SAFE_DELETE(shader);

	SAFE_DELETE(bunny);
	SAFE_DELETE(sphere2);
	SAFE_DELETE(sphere);
	SAFE_DELETE(cube);
	SAFE_DELETE(plane);
	
}

void TestAmbient::Update()
{
	plane->Update();
	sphere->Update();
	sphere2->Update();
	cube->Update();
	bunny->Update();
}

void TestAmbient::PreRender()
{
	
}


void TestAmbient::Render()
{ 
	/*ImGui::ColorEdit3("AmbientFloor", (float*)&ambientBuffer->Data.Floor);
	ImGui::ColorEdit3("AmbientCeil", (float*)&ambientBuffer->Data.Ceil);
	ImGui::ColorEdit3("DirectionColor", (float*)&ambientBuffer->Data.Color);
	ImGui::Separator();

	ImGui::SliderFloat("SpecularExp",(float*) &specularBuffer->Data.Exp, 1, 100);
	ImGui::SliderFloat("SpecularIntensityp", (float*)&specularBuffer->Data.Intensity, 0, 10);
	ImGui::Separator();

	ImGui::SliderFloat3("PointLightPosition", (float*)&pointLightBuffer->Data.Position, -50, 50);
	ImGui::SliderFloat("PointLightRange", (float*)&pointLightBuffer->Data.Range, 0, 100);
	ImGui::ColorEdit3("PointColor", pointLightBuffer->Data.Color); 
	ImGui::Separator();*/

	
	/*ImGui::SliderFloat3("SpotLightPosition", (float*)&spotLightBuffer->Data.Position, -50, 50);
	ImGui::SliderFloat("SpotLightRange", (float*)&spotLightBuffer->Data.Range, 0, 100);
	ImGui::ColorEdit3("SpotLightColor", spotLightBuffer->Data.Color);
	ImGui::SliderFloat3("SpotLightDirection", (float*)&spotLightBuffer->Data.Direction, -1, 1);
	ImGui::SliderFloat("SpotLightInner", (float*)&spotLightBuffer->Data.Inner, 0, 180);
	ImGui::SliderFloat("SpotLightOuter", (float*)&spotLightBuffer->Data.Outer, 0, 180);
	*/
	ImGui::SliderFloat3("Position", (float*)&capsuleLightBuffer->Data.Position, -50, 50);
	ImGui::SliderFloat("Range", (float*)&capsuleLightBuffer->Data.Range, 0, 100);
	ImGui::ColorEdit3("Color", capsuleLightBuffer->Data.Color);
	ImGui::SliderFloat3("Direction", (float*)&capsuleLightBuffer->Data.Direction, -1, 1);
	ImGui::SliderFloat("Length", (float*)&capsuleLightBuffer->Data.Length, 0, 180);


	lightBuffer->SetPSBuffer(10);
	
	capsuleLightBuffer->SetPSBuffer(9);
	plane->Render();
	sphere->Render();
	sphere2->Render();
	cube->Render();
	bunny->Render();
	
}

void TestAmbient::PostRender()
{

}
