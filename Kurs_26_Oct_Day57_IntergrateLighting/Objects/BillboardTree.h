#pragma once
#include "GameModel.h"

class BillboardTree : public GameModel
{
public:
	
	BillboardTree(ExecuteValues* values, wstring shaderFile, wstring diffuseFile);
	~BillboardTree();

	void FixedY(bool val) { bFixedY = val; }

	void Update();
	void Render();

	void GetBoundingBox(std::vector<D3DXVECTOR3>& boundBox) { boundBox.assign(boundingBox.begin(), boundingBox.end()); }
	void GetBoundVertex(std::vector<D3DXVECTOR3>& boundBoxTries) { boundBoxTries.assign(this->boundingvertex.begin(), this->boundingvertex.end()); }
	
	D3DXVECTOR3 GetMinVertice() { return vecMin; }
	D3DXVECTOR3 GetMaxVertice() { return vecMax; }

private:
	ExecuteValues* values;
	RasterizerState* cullMode[2];
	
	bool bFixedY;

	std::vector<D3DXVECTOR3> boundingBox;
	std::vector<D3DXVECTOR3> boundingvertex;
	D3DXVECTOR3 center;
	D3DXVECTOR3 boundSize;
	D3DXVECTOR3 vecMin, vecMax;
	vector<GameModel*> trees;

	float radius;

	void SetBoundingBox();
	
};