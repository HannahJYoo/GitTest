#include "stdafx.h"
#include "GausianBlur.h"

GausianBlur::GausianBlur(ExecuteValues * values, string psName)
	:Render2D(values, Shaders + L"023_GausianBlur.hlsl", "VS", psName)
{
	buffer = new Buffer();
	
	
}

GausianBlur::~GausianBlur()
{
	SAFE_DELETE(buffer);
}

void GausianBlur::Render()
{
	ImGui::Separator();
	
	ImGui::SliderInt("GausianBlur Count", &buffer->Data.Count, 1, 6);

	D3DXVECTOR2 scale = Scale();
	buffer->Data.Width = (int)scale.x;
	buffer->Data.Height = (int)scale.y;

	buffer->SetPSBuffer(10);
	__super::Render();
}
