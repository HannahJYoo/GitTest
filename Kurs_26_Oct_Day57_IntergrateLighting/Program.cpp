#include "stdafx.h"
#include "Program.h"
#include "./Viewer/Freedom.h"
#include "./Viewer/OrbitCamera.h"

#include "./Executes/ExportMesh.h"
#include "./Executes/ExportAnim.h"

#include "./Executes/DrawLandscape.h"
#include "./Executes/TestLandscape.h"
#include "./Executes/TestAmbient.h"



Program::Program()
{
	
	D3DDesc desc;
	D3D::GetDesc(&desc);

	values = new ExecuteValues();
	values->ViewProjection = new ViewProjectionBuffer();
	values->GlobalLight = new LightBuffer();
	values->Perspective = new Perspective(desc.Width, desc.Height);
	values->Viewport = new Viewport(desc.Width, desc.Height);

	orbitCamera = new OrbitCamera(100.0f, 100.0f, 2.5f, 0);
	freeCamera = new Freedom(50.0f,2.5f);

	values->MainCamera = freeCamera;
	values->MainCamera->Position(0.0f, 25.0f, -50.0f);
	//values->MainCamera->Position(220.0f, 70.0f, 14.0f);

	freeCamera->RotationDegree(30.0f, 0.0f);
	//freeCamera->Position(137, 97, -100.0f);
	orbitCamera->Position(0, 0, -100.0f);

	values->GlobalLight->Data.Direction = D3DXVECTOR3(-1, -1, 0);

	//executes.push_back(new ExportMesh(values));
	//executes.push_back(new ExportAnim(values));

	//executes.push_back(new DrawLandscape(values));
	//executes.push_back(new TestLandscape(values));
	//executes.push_back(new TestBlend(values));
	executes.push_back(new TestAmbient(values));
	//executes.push_back(new TestMultiTexture(values));
	
	


	isOrbit = false;

}

Program::~Program()
{
	for (Execute* exe : executes)
		SAFE_DELETE(exe);

	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values->GlobalLight);
	SAFE_DELETE(values->ViewProjection);
	SAFE_DELETE(values->Perspective);
	SAFE_DELETE(values->Viewport);
	SAFE_DELETE(values);

	
}

void Program::Update()
{
	
	if (isOrbit == true)
		values->MainCamera = orbitCamera;
	else
		values->MainCamera = freeCamera;

	values->MainCamera->Update();

	for (Execute* exe : executes)
		exe->Update();

	if (Keyboard::Get()->Down(VK_ESCAPE))
		PostQuitMessage(0);
}

void Program::PreRender()
{
	D3DXMATRIX view, projection;
	values->MainCamera->Matrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);
	values->ViewProjection->SetVSBuffer(0);

	for (Execute* exe : executes)
		exe->PreRender();
}

void Program::Render()
{
	D3DXMATRIX view, projection;
	values->MainCamera->Matrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);
	values->ViewProjection->SetVSBuffer(0);
	values->GlobalLight->SetPSBuffer(0);
	values->Viewport->RSSetViewport();

	for (Execute* exe : executes)
		exe->Render();

	//ImGui::Begin("Info");
	{
		//ImGui::Text("FPS : %f", Time::Get()->FPS());
		//ImGui::Separator();
		////ImGui::Checkbox("Orbit_Sphere", &isOrbit);
		////ImGui::Separator();

		ImGui::SliderFloat3("GlobalLightDirection", (float*)&values->GlobalLight->Data.Direction, -1, 1);
		ImGui::Separator();
		/*D3DXVECTOR3 vec;
		values->MainCamera->Position(&vec);
		ImGui::LabelText("CameraPos", "%.2f, %.2f, %.2f", vec.x, vec.y, vec.z);

		D3DXVECTOR2 rot;
		values->MainCamera->RotationDegree(&rot);
		ImGui::LabelText("CameraRot", "%.2f, %.2f", rot.x, rot.y);*/

	}
	//ImGui::End();
}

void Program::PostRender()
{
	for (Execute* exe : executes)
		exe->PostRender();
	
	wstring str = String::Format(L"FPS : %.2f", ImGui::GetIO().Framerate);
	
	RECT rect = { 0,0,300,300 };
	DirectWrite::RenderText(str, rect, 12);

	D3DXVECTOR3 vec;
	values->MainCamera->Position(&vec);
	str = String::Format(L"CameraPos : %.2f, %.2f, %.2f", vec.x, vec.y, vec.z);

	rect.top += 12;
	DirectWrite::RenderText(str, rect, 12);
	
	D3DXVECTOR2 rot;
	values->MainCamera->RotationDegree(&rot);
	str = String::Format(L"CameraRot : %.2f, %.2f", rot.x, rot.y);

	rect.top += 12;
	DirectWrite::RenderText(str, rect, 12);
	
}

void Program::ResizeScreen()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	values->Perspective->Set(desc.Width, desc.Height);
	values->Viewport->Set(desc.Width, desc.Height);

	for (Execute* exe : executes)
		exe->ResizeScreen();
}