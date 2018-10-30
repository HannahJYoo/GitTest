#pragma once
#include "GameModel.h"

class GameTank : public GameModel
{
public:
	GameTank();
	~GameTank();

	void Update() override;
	void Render() override;

private:
	ModelBone* lbWheelBone;
	ModelBone* rbWheelBone;
	ModelBone* lfWheelBone;
	ModelBone* rfWheelBone;
	D3DXMATRIX lbWheel;
	D3DXMATRIX rbWheel;
	D3DXMATRIX lfWheel;
	D3DXMATRIX rfWheel;

	ModelBone* turretBone;
	D3DXMATRIX turret;


};