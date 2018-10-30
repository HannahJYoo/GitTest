#include "stdafx.h"
#include "ExportAnim.h"
#include "../Fbx/Exporter.h"

ExportAnim::ExportAnim(ExecuteValues * values)
	: Execute(values)
{
	Fbx::Exporter* exporter = NULL;

	////Kachujin Mesh
	exporter = new Fbx::Exporter(Assets + L"Kachujin/Mesh.fbx");
	exporter->ExportMaterial(Models + L"Kachujin/", L"Kachujin.material");
	exporter->ExportMesh(Models + L"Kachujin/", L"Kachujin.mesh");
	SAFE_DELETE(exporter);

	exporter = new Fbx::Exporter(Assets + L"Kachujin/Samba_Dancing.fbx");
	exporter->ExportAnimation(Models + L"Kachujin/", L"Samba_Dance.anim", 0);
	SAFE_DELETE(exporter);

	exporter = new Fbx::Exporter(Assets + L"Kachujin/Taunt.fbx");
	exporter->ExportAnimation(Models + L"Kachujin/", L"Taunt.anim", 0);
	SAFE_DELETE(exporter);

	exporter = new Fbx::Exporter(Assets + L"Kachujin/Running.fbx");
	exporter->ExportAnimation(Models + L"Kachujin/", L"Running.anim", 0);
	SAFE_DELETE(exporter);
}

ExportAnim::~ExportAnim()
{
	
}

void ExportAnim::Update()
{
	
}

void ExportAnim::PreRender()
{
	
}

void ExportAnim::Render()
{
	
}

void ExportAnim::PostRender()
{
	
}

void ExportAnim::ResizeScreen()
{
}

