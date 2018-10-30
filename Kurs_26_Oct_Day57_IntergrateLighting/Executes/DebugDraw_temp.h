#pragma once

enum DebugDrawType
{
	DebugDrawType_Sphere,
	DebugDrawType_Cube,
	DebugDrawType_None
};
class DebugDraw_temp : public Execute
{
public:
	DebugDraw_temp(ExecuteValues* values, UINT objNum=0);
	~DebugDraw_temp();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();

	void ChangeObj(UINT objNum);

	D3DXCOLOR GetColor();
	void SetColor(D3DXCOLOR& color);

	D3DXVECTOR3 Position() { return position; }
	void Position(D3DXVECTOR3& pos) { position = pos; }

	D3DXVECTOR3 Scale() { return scale; }
	void Scale(D3DXVECTOR3& scl) { scale = scl; }

	D3DXVECTOR3 Rotation() { return rotation; }
	void Rotation(D3DXVECTOR3& rot) { rotation = rot; }

private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;

	class LineDraw* line;

	vector<VertexTextureNormal>* vTargetVertices;
	vector<UINT>* vTargetIndices;

private:
	UINT objNum;
	DebugDrawType eDrawType;
	vector<VertexTextureNormal> vSphereVertices;
	vector<UINT> vSphereIndices;
	vector<VertexTextureNormal> vCubeVertices;
	vector<UINT> vCubeIndices;
	D3DXMATRIX S, R, T, W;
	void SettingObj();
};