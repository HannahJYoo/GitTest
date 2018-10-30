#pragma once
#include "GameModel.h"

class Billboard : public GameModel
{
public:
	
	Billboard(ExecuteValues* values, wstring shaderFile, wstring diffuseFile);
	~Billboard();

	void FixedY(bool val) { bFixedY = val; }

	void Update();
	void Render();

	void SetTreeAxis(D3DXVECTOR3& args) { treeAxis = args; }
	void SetTreeAxis(float x, float y, float z);

private:
	ExecuteValues* values;
	RasterizerState* cullMode[2];
	
	bool bFixedY;

	D3DXVECTOR3 treeAxis;

	
	
};