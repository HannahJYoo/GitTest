#pragma once
#include "GameModel.h"

class MeshSphere : public GameModel
{
public:
	MeshSphere();
	~MeshSphere();

	void Update() override;
	void Render() override;
	void GetBoundVertex(std::vector<D3DXVECTOR3>& boundBoxTries) { boundBoxTries.assign(this->boundingvertex.begin(), this->boundingvertex.end()); }

private:
	std::vector<D3DXVECTOR3> boundingBox;
	std::vector<D3DXVECTOR3> boundingvertex;
	//Bound_Type boundType;
	D3DXVECTOR3 center;
	D3DXVECTOR3 boundSize;
	D3DXVECTOR3 vecMin, vecMax;
	float radius;

	void SetBoundingBox();

};