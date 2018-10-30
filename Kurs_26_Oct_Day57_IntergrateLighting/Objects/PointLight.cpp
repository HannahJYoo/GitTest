#include "stdafx.h"
#include "PointLight.h"
#include "./Aufgaben/DebugDraw.h"

PointLight::PointLight(ExecuteValues * values)
	:values(values), plIndex(-1)
{
	buffer = new Buffer();
	PointLightInfos info;
	pointlights.assign(32, info);
}

PointLight::~PointLight()
{
	for (UINT i = 0; i < pointlights.size(); i++)
		SAFE_DELETE(pointlights[i].debugDraw);
	SAFE_DELETE(buffer);
}

void PointLight::Update()
{
	D3DXVECTOR3 start;
	values->MainCamera->Position(&start);

	D3DXVECTOR3 direction = values->MainCamera->Direction(values->Viewport, values->Perspective);
	D3DXVECTOR3 pickedPos;

	bool isClick = false;
	bool isPick = false;

	if (Keyboard::Get()->Press(VK_LSHIFT) && Mouse::Get()->Down(0))
		isClick = true;

	for (UINT i = 0; i < pointlights.size(); i++) {
		if (pointlights[i].debugDraw == NULL)
			continue;
		if (isClick) {
			if (!isPick) {
				if (pointlights[i].debugDraw->bModelPick(start, direction, pickedPos)) {
					plIndex = i;
					isPick = true;
				}
			}
		}

		UINT idx = pointlights[i].idx;
		pointlights[i].debugDraw->Position(pointlights[i].desc.Position);

		float s = pointlights[i].desc.Range;
		pointlights[i].debugDraw->Scale(s, s, s);

		D3DXVECTOR3 dc = pointlights[i].desc.Color;
		D3DXCOLOR dcolor = D3DXCOLOR(dc.x, dc.y, dc.z, 1);
		pointlights[i].debugDraw->SetColor(dcolor);

		pointlights[i].debugDraw->Update();

		buffer->Data.Lights[idx] = pointlights[i].desc;
	}

	if (isClick)
	{
		plIndex = isPick ? plIndex : -1;
	}
}

void PointLight::Render()
{
	buffer->SetPSBuffer(2);
	for (UINT i = 0; i < pointlights.size(); i++)	{
		if (pointlights[i].debugDraw == NULL)
			continue;
		pointlights[i].debugDraw->Render();
	}
}

void PointLight::PostRender()
{
	if (plIndex >= 0)
	{
		ImGui::Begin("Point Light");
		{
			ImGui::LabelText("", "%d Light", plIndex + 1);
			ImGui::SliderFloat3("Position", (float *)&pointlights[plIndex].desc.Position, 0, 256);
			ImGui::SliderFloat3("Color", (float *)&pointlights[plIndex].desc.Color, 0, 1);
			ImGui::SliderFloat("Range", &pointlights[plIndex].desc.Range, 0, 20);
			ImGui::SliderFloat("Intensity", &pointlights[plIndex].desc.Intensity, 0.001f, 5.0f);
		}
		ImGui::End();
	}
}

void PointLight::Add(Desc & desc)
{
	int count = buffer->Data.Count;
	buffer->Data.Lights[count] = desc;

	PointLightInfos info;
	info.idx = count;
	info.desc = desc;
	info.debugDraw = new DebugDraw();
	info.debugDraw->Position(desc.Position);
	info.debugDraw->Scale(D3DXVECTOR3(desc.Range, desc.Range, desc.Range));
	info.debugDraw->Update();
	pointlights[count] = info;

	buffer->Data.Count++;
}
