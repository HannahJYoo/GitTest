#pragma once
#include "../Objects/GameModel.h"

enum DebugDrawType
{
	DebugDrawType_Sphere,
	DebugDrawType_Cube,
	DebugDrawType_None
};
class DebugDraw : public GameModel
{
public:
	DebugDraw(ExecuteValues* values,D3DXVECTOR3 pos, D3DXVECTOR3 s, D3DXCOLOR color,  UINT objNum = 0);
	DebugDraw(UINT objNum = 0);
	~DebugDraw();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();

	void ChangeObj(UINT objNum);

	D3DXCOLOR GetColor();
	void SetColor(D3DXCOLOR& color);

	/*D3DXVECTOR3 Position() { return position; }
	void Position(D3DXVECTOR3& pos) { position = pos; }

	D3DXVECTOR3 Scale() { return scale; }
	void Scale(D3DXVECTOR3& scl) { scale = scl; }

	D3DXVECTOR3 Rotation() { return rotation; }
	void Rotation(D3DXVECTOR3& rot) { rotation = rot; }
*/
private:
	/*D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;*/

	class LineMake* line;

	vector<VertexTextureNormal>* vTargetVertices;
	vector<UINT>* vTargetIndices;

private:
	UINT objNum;
	DebugDrawType eDrawType;
	vector<VertexTextureNormal> vSphereVertices;
	vector<UINT> vSphereIndices;
	vector<VertexTextureNormal> vCubeVertices;
	vector<UINT> vCubeIndices;

	void SettingObj();
};