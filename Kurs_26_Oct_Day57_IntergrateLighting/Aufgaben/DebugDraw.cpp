#include "stdafx.h"
#include "DebugDraw.h"
#include "../Aufgaben/LineMake.h"

DebugDraw::DebugDraw(ExecuteValues * values, D3DXVECTOR3 pos, D3DXVECTOR3 s, D3DXCOLOR color, UINT objNum)
	: GameModel(Materials + L"Meshes/", L"Cube.material", Models + L"Meshes/", L"Cube.mesh")
	, objNum(objNum)
{
	line = new LineMake();

	SettingObj();
	ChangeObj(objNum);
	Position(pos);
	Scale(s);
	SetColor(color);
}

DebugDraw::DebugDraw(UINT objNum)
	: GameModel(Materials + L"Meshes/", L"Cube.material", Models + L"Meshes/", L"Cube.mesh")
	, objNum(objNum)
{
	line = new LineMake();

	SettingObj();
	ChangeObj(objNum);
}

DebugDraw::~DebugDraw()
{
	SAFE_DELETE(line);
}

void DebugDraw::Update()
{
	__super::Update();
	line->SetWorld(World());
}

void DebugDraw::PreRender()
{

}

void DebugDraw::Render()
{
	line->Render();
}

void DebugDraw::PostRender()
{

}

void DebugDraw::ResizeScreen()
{
}

void DebugDraw::ChangeObj(UINT objNum)
{
	switch (objNum)
	{
	default:
		break;
	case 0:
		vTargetVertices = &vSphereVertices;
		vTargetIndices = &vSphereIndices;
		break;
	case 1:
		vTargetVertices = &vCubeVertices;
		vTargetIndices = &vCubeIndices;
		break;
	
	}

	vector<D3DXVECTOR3> _vTmpVertices;
	for (UINT i = 0; i < vTargetVertices->size(); i++)
		_vTmpVertices.push_back((*vTargetVertices)[i].Position);

	line->MeshData(_vTmpVertices, *vTargetIndices, objNum);
	line->SetColor(D3DXCOLOR(1, 0, 0, 1));
}

D3DXCOLOR DebugDraw::GetColor()
{
	return line->GetColor();
}

void DebugDraw::SetColor(D3DXCOLOR & color)
{
	line->SetColor(color);
}

void DebugDraw::SettingObj()
{

	//Draw Cube
	{
		vector<D3DXVECTOR3> tempPos;
		for (UINT i = 0; i < 2; i++)
		{
			for (UINT j = 0; j < 4; j++)
			{
				D3DXVECTOR3 tmp;
				tmp.x = (j < 2) ? -1 : 1;
				tmp.y = (j % 2 == 0) ? -1 : 1;
				tmp.z = (i < 1) ? -1 : 1;
				tempPos.push_back(tmp);
			}
		}

		for (UINT i = 0; i < tempPos.size(); i++)
		{
			VertexTextureNormal temp;
			temp.Position = tempPos[i];
			vCubeVertices.push_back(temp);
		}

		vCubeIndices.assign(36, 0);
		vCubeIndices = {
			0,1,2, 3,2,1,
			2,3,6, 7,6,3,
			6,7,4, 5,4,7,
			4,5,0, 1,0,5,
			1,5,3, 7,3,5,
			4,0,6, 2,6,0
		};
	}

	//Draw Sphere
	{
		UINT latitudeBands = 30;
		UINT longitudeBands = 30;
		float radius = 1.0f;

		for (UINT lat = 0; lat <= latitudeBands; lat++)
		{
			float theta = (float)lat * Math::PI / (float)latitudeBands;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);

			for (UINT lng = 0; lng <= longitudeBands; lng++)
			{
				VertexTextureNormal data;

				float phi = (float)lng * 2.0f * Math::PI / (float)longitudeBands;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);

				D3DXVECTOR3 norm;
				norm.x = cosPhi * sinTheta;
				norm.y = cosTheta;
				norm.z = sinPhi * sinTheta;

				D3DXVECTOR2 uv;
				uv.x = 1.0f - ((float)lng / (float)longitudeBands);
				uv.y = (float)lat / (float)latitudeBands;

				D3DXVECTOR3 pos;
				pos = norm * radius;

				data.Position = pos;
				data.Normal = norm;
				data.Uv = uv;
				vSphereVertices.push_back(data);
			}
		}


		for (UINT lat = 0; lat < latitudeBands; lat++)
		{
			for (UINT lng = 0; lng < longitudeBands; lng++)
			{
				UINT first = (lat * (longitudeBands + 1)) + lng;
				UINT second = first + longitudeBands + 1;

				vSphereIndices.push_back(first);
				vSphereIndices.push_back(first + 1);
				vSphereIndices.push_back(second);
				vSphereIndices.push_back(second);
				vSphereIndices.push_back(first + 1);
				vSphereIndices.push_back(second + 1);
			}
		}
	}
}

