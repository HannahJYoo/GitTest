#include "stdafx.h"
#include "BillboardTree.h"
#include "../Model/ModelMeshPart.h"
#include "Billboard.h"

BillboardTree::BillboardTree(ExecuteValues * values, wstring shaderFile, wstring diffuseFile)
	:GameModel(Materials + L"Meshes/", L"Quad.material", Models + L"Meshes/", L"Quad.mesh")
	, values(values)
{
	for (Material* material : model->Materials()) {
		material->SetShader(shaderFile);
		material->SetDiffuseMap(diffuseFile);
	}

	cullMode[0] = new RasterizerState();
	cullMode[1] = new RasterizerState();
	cullMode[1]->FrontCounterClockwise(true);


	D3DXMATRIX R;

	GameModel* _tree = new Billboard(values, shaderFile, diffuseFile);
	trees.push_back(_tree);

	_tree = new Billboard(values, shaderFile, diffuseFile);
	((Billboard *)_tree)->SetTreeAxis(0, Math::ToRadian(360 - 45), 0);
	trees.push_back(_tree);

	_tree = new Billboard(values, shaderFile, diffuseFile);
	((Billboard *)_tree)->SetTreeAxis(0, Math::ToRadian(45), 0);
	trees.push_back(_tree);

	SetBoundingBox();
}

BillboardTree::~BillboardTree()
{
	for (GameModel* tree : trees)
		SAFE_DELETE(tree);
}

void BillboardTree::Update()
{
	
	
	__super::Update();
	for (GameModel* tree : trees)
	{
		tree->Position(Position());
		tree->Scale(Scale());
		tree->Update();
	}
}

void BillboardTree::Render()
{
	cullMode[1]->RSSetState();

	for (GameModel* tree : trees)
		tree->Render();

	cullMode[0]->RSSetState();
}


void BillboardTree::SetBoundingBox()
{
	float min = -std::numeric_limits<float>().infinity(), max = std::numeric_limits<float>().infinity();
	D3DXVECTOR3 vecMin(max, max, max), vecMax(min, min, min);

	for (ModelMesh* modelMesh : model->Meshes())
	{
		ModelBone* bone = modelMesh->ParentBone();
		D3DXMATRIX w = bone->Global();
		for (ModelMeshPart* part : modelMesh->Meshs())
		{
			vector<VertexTextureNormalTangentBlend> vertices = part->Vertices();
			for (VertexTextureNormalTangentBlend data : vertices)
			{
				D3DXVECTOR3 pos = data.Position;
				D3DXVec3TransformCoord(&pos, &pos, &w);
				if (vecMin.x > pos.x) vecMin.x = pos.x;
				if (vecMax.x < pos.x) vecMax.x = pos.x;

				if (vecMin.y > pos.y) vecMin.y = pos.y;
				if (vecMax.y < pos.y) vecMax.y = pos.y;

				if (vecMin.z > pos.z) vecMin.z = pos.z;
				if (vecMax.z < pos.z) vecMax.z = pos.z;
			}
		}
	}

	this->vecMin = vecMin;
	this->vecMax = vecMax;
	center = (vecMax + vecMin) / 2.0f;

	D3DXVECTOR3 temp = vecMax + center;
	if (temp.x < 0) temp.x *= -1;
	if (temp.y < 0) temp.y *= -1;
	if (temp.z < 0) temp.z *= -1;
	radius = max(temp.x, temp.y);
	radius = max(radius, temp.z);
	boundSize = temp * 2.0f;

	boundingBox.push_back(D3DXVECTOR3(vecMin.x, vecMin.y, vecMin.z));
	boundingBox.push_back(D3DXVECTOR3(vecMin.x, vecMax.y, vecMin.z));
	boundingBox.push_back(D3DXVECTOR3(vecMax.x, vecMin.y, vecMin.z));
	boundingBox.push_back(D3DXVECTOR3(vecMax.x, vecMax.y, vecMin.z));
	boundingBox.push_back(D3DXVECTOR3(vecMin.x, vecMin.y, vecMax.z));
	boundingBox.push_back(D3DXVECTOR3(vecMin.x, vecMax.y, vecMax.z));
	boundingBox.push_back(D3DXVECTOR3(vecMax.x, vecMin.y, vecMax.z));
	boundingBox.push_back(D3DXVECTOR3(vecMax.x, vecMax.y, vecMax.z));

	UINT indices[36]{ 0,1,2,2,1,3, 2,3,6,6,3,7, 6,7,5,5,7,4, 4,5,0,0,5,1, 1,5,3,3,5,7, 4,0,6,6,0,2 };

	for (int i = 0; i < 36; i++)
	{
		boundingvertex.push_back(boundingBox[indices[i]]);
	}
}
