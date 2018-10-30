#include "stdafx.h"
#include "DebugDraw_temp.h"
#include "../Aufgaben/LineDraw.h"

DebugDraw_temp::DebugDraw_temp(ExecuteValues * values, UINT objNum)
	: Execute(values)
	, position(0, 0, 0), scale(1, 1, 1), rotation(0, 0, 0)
{
	line = new LineDraw();

	SettingObj();
	ChangeObj(objNum);

}

DebugDraw_temp::~DebugDraw_temp()
{
	SAFE_DELETE(line);
}

void DebugDraw_temp::Update()
{
	
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	W = S * R * T;
	line->SetWorld(W);
}

void DebugDraw_temp::PreRender()
{

}

void DebugDraw_temp::Render()
{
	line->Draw(W);
}

void DebugDraw_temp::PostRender()
{

}

void DebugDraw_temp::ResizeScreen()
{
}

void DebugDraw_temp::ChangeObj(UINT objNum)
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

D3DXCOLOR DebugDraw_temp::GetColor()
{
	return line->GetColor();
}

void DebugDraw_temp::SetColor(D3DXCOLOR & color)
{
	line->SetColor(color);
}

void DebugDraw_temp::SettingObj()
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

