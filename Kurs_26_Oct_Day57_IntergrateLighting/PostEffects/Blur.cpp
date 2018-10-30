#include "stdafx.h"
#include "Blur.h"

Blur::Blur(ExecuteValues * values)
	:Render2D(values, Shaders + L"022_Blur.hlsl")
{
	buffer = new Buffer();
	
	
}

Blur::~Blur()
{
	SAFE_DELETE(buffer);
}

void Blur::Render()
{
	ImGui::Separator();
	ImGui::SliderInt("Blur Count", &buffer->Data.Count, 1, 20);

	D3DXVECTOR2 scale = Scale();
	buffer->Data.Width = (int)scale.x;
	buffer->Data.Height = (int)scale.y;

	buffer->SetPSBuffer(10);
	__super::Render();
}
