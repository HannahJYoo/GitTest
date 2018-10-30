#include "stdafx.h"
#include "Billboard.h"
#include "../Model/ModelMeshPart.h"

Billboard::Billboard(ExecuteValues * values, wstring shaderFile, wstring diffuseFile)
	:GameModel(Materials + L"Meshes/", L"Quad.material", Models + L"Meshes/", L"Quad.mesh")
	, values(values), treeAxis(0, 0, 0)
{
	for (Material* material : model->Materials()) {
		material->SetShader(shaderFile);
		material->SetDiffuseMap(diffuseFile);
	}

	/*cullMode[0] = new RasterizerState();
	cullMode[1] = new RasterizerState();
	cullMode[1]->FrontCounterClockwise(true);*/


}

Billboard::~Billboard()
{
}

void Billboard::Update()
{
	
	D3DXMATRIX R;
	values->MainCamera->Matrix(&R);

	D3DXMatrixInverse(&R, NULL, &R);

	float x = asin(-R._32);
	float y = atan2(R._31, R._33);
	float z = atan2(R._12, R._22);

	if (bFixedY == true)
		Rotation(x, 0, z);
	else
		Rotation(0 + treeAxis.x, y + treeAxis.y, 0 + treeAxis.z);
	//	Rotation(x, y, z);


	__super::Update();

}

void Billboard::Render()
{
	//cullMode[1]->RSSetState();

	__super::Render();

	//cullMode[0]->RSSetState();
}

void Billboard::SetTreeAxis(float x, float y, float z)
{

	treeAxis.x = x;
	treeAxis.y = y;
	treeAxis.z = z;

}

