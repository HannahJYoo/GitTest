#include "stdafx.h"
#include "MeshQuad.h"
#include "../Model/ModelMeshPart.h"


MeshQuad::MeshQuad()
	: GameModel(Materials + L"Bevor/", L"Quad.material", Models + L"Bevor/", L"Quad.mesh")
{
	/*shader = new Shader(Shaders + L"011_Sphere.hlsl");
	for (Material* material : model->Materials())
	{
		material->SetDiffuse(D3DXCOLOR(1, 0, 0, 1));
		material->SetShader(shader);
	}
*/
	rasterizerState[0] = new RasterizerState();
	rasterizerState[1] = new RasterizerState();
	rasterizerState[1]->FrontCounterClockwise(true);

}

MeshQuad::~MeshQuad()
{
	SAFE_DELETE(shader);
}

void MeshQuad::Update()
{
	__super::Update();
}

void MeshQuad::Render()
{
	rasterizerState[1]->RSSetState();
	__super::Render();
	rasterizerState[0]->RSSetState();

}
