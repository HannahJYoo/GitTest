#pragma once
#include "GameModel.h"

class MeshCube : public GameModel
{
public:
	MeshCube();
	~MeshCube();

	void Update() override;
	void Render() override;

	//enum Bound_Type
	//{
	//	BOUND_TYPE_SPHERE = 0,
	//	BOUND_TYPE_BOX,
	//	BOUND_TYPE_MAX
	//};


	void GetBoundingBox(std::vector<D3DXVECTOR3>& boundBox) { boundBox.assign(boundingBox.begin(), boundingBox.end()); }
	void GetBoundVertex(std::vector<D3DXVECTOR3>& boundBoxTries) { boundBoxTries.assign(this->boundingvertex.begin(), this->boundingvertex.end()); }
	void GetAABB(std::vector<D3DXVECTOR3>& aabbBox);

	D3DXVECTOR3 GetMinVertice() { return vecMin; }
	D3DXVECTOR3 GetMaxVertice() { return vecMax; }

protected:
	class LineMake* box;
	class LineMake* boxAABB;
	std::vector<D3DXVECTOR3> boundingBox;
	std::vector<D3DXVECTOR3> boundingvertex;
	//Bound_Type boundType;
	D3DXVECTOR3 center;
	D3DXVECTOR3 boundSize;
	D3DXVECTOR3 vecMin, vecMax;
	float radius;

	void SetBoundingBox();
};