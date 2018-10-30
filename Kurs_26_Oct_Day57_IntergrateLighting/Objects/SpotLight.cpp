#include "stdafx.h"
#include "SpotLight.h"
#include "./Aufgaben/DebugDraw.h"

SpotLight::SpotLight(ExecuteValues * values)
	:values(values), plIndex(-1)
{
	buffer = new Buffer();
	SpotLightInfos info;
	spotlights.assign(32, info);
}

SpotLight::~SpotLight()
{
	for (UINT i = 0; i < spotlights.size(); i++)
		SAFE_DELETE(spotlights[i].debugDraw);
	SAFE_DELETE(buffer);
}

void SpotLight::Update()
{
	D3DXVECTOR3 start;
	values->MainCamera->Position(&start);

	D3DXVECTOR3 direction = values->MainCamera->Direction(values->Viewport, values->Perspective);
	D3DXVECTOR3 pickedPos;

	bool isClick = false;
	bool isPick = false;

	if (Keyboard::Get()->Press(VK_LSHIFT) && Mouse::Get()->Down(0))
		isClick = true;

	for (UINT i = 0; i < spotlights.size(); i++) {
		if (spotlights[i].debugDraw == NULL)
			continue;
		if (isClick) {
			if (!isPick) {
				if (spotlights[i].debugDraw->bModelPick(start, direction, pickedPos)) {
					plIndex = i;
					isPick = true;
				}
			}
		}

		UINT idx = spotlights[i].idx;
		spotlights[i].debugDraw->Position(spotlights[i].desc.Position);
		
		if ((spotlights[i].desc.OuterAngle - spotlights[i].desc.InnerAngle) > 0)
			 s = spotlights[i].desc.OuterAngle - spotlights[i].desc.InnerAngle;
		else
			 s = spotlights[i].desc.InnerAngle - spotlights[i].desc.OuterAngle;
		spotlights[i].debugDraw->Scale(s, s, s);

		D3DXVECTOR3 dc = spotlights[i].desc.Color;
		D3DXCOLOR dcolor = D3DXCOLOR(dc.x, dc.y, dc.z, 1);
		spotlights[i].debugDraw->SetColor(dcolor);

		spotlights[i].debugDraw->Update();

		buffer->Data.Lights[idx] = spotlights[i].desc;
	}

	if (isClick)
	{
		plIndex = isPick ? plIndex : -1;
	}
}

void SpotLight::Render()
{
	buffer->SetPSBuffer(3);
	for (UINT i = 0; i < spotlights.size(); i++)	{
		if (spotlights[i].debugDraw == NULL)
			continue;
		spotlights[i].debugDraw->Render();
	}
}

void SpotLight::PostRender()
{
	if (plIndex >= 0)
	{
		ImGui::Begin("Spot Light");
		{
			ImGui::LabelText("", "%d Light", plIndex + 1);
			ImGui::SliderFloat3("Position", (float *)&spotlights[plIndex].desc.Position, 0, 256);
			ImGui::SliderFloat3("Color", (float *)&spotlights[plIndex].desc.Color, 0, 1);
			ImGui::SliderFloat("InnerAngle", &spotlights[plIndex].desc.InnerAngle, 0.1f, 20.0f);
			ImGui::SliderFloat("OuterAngle", &spotlights[plIndex].desc.OuterAngle, 0.1f, 20.0f);
			ImGui::SliderFloat3("Derection", (float*)&spotlights[plIndex].desc.Direction, -1.0f, 1.0f);
		}
		ImGui::End();
	}
}

void SpotLight::Add(Desc & desc)
{
	int count = buffer->Data.Count;
	buffer->Data.Lights[count] = desc;

	SpotLightInfos info;
	info.idx = count;
	info.desc = desc;
	info.debugDraw = new DebugDraw();
	info.debugDraw->Position(desc.Position);

	if ((desc.OuterAngle - desc.InnerAngle) > 0)
		s = desc.OuterAngle - desc.InnerAngle;
	else
		s = desc.InnerAngle - desc.OuterAngle;
	
	info.debugDraw->Scale(D3DXVECTOR3(s, s, s));
	info.debugDraw->Update();
	spotlights[count] = info;

	buffer->Data.Count++;
}
