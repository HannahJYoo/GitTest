#include "stdafx.h"
#include "GameTank.h"

GameTank::GameTank()
	:GameModel(Models+L"Tank/", L"Tank.material", Models + L"Tank/", L"Tank.mesh")
{
	shader = new Shader(Shaders + L"HA003_Model.hlsl");

	lbWheelBone = model->BoneByName(L"l_back_wheel_geo");
	lbWheel = lbWheelBone->Local();
	
	rbWheelBone = model->BoneByName(L"r_back_wheel_geo");
	rbWheel = rbWheelBone->Local();
	
	lfWheelBone = model->BoneByName(L"l_front_wheel_geo");
	lfWheel = lfWheelBone->Local();
	
	rfWheelBone = model->BoneByName(L"r_front_wheel_geo");
	rfWheel = rfWheelBone->Local();

	turretBone = model->BoneByName(L"turret_geo");
	turret = turretBone->Local();

}

GameTank::~GameTank()
{
}

void GameTank::Update()
{
	__super::Update();	//__super ; 바로 위 부모호출

						//Tank Bewegung
	{
		D3DXVECTOR3 pos = this->Position();
		D3DXVECTOR3 dir = this->Direction();
		float speed = 10.0f;
		float rotSpeed = 90.0f;
		float radian = 90.0f;
		D3DXVECTOR3 up = this->Up();
		D3DXMATRIX matRotation;
		D3DXMATRIX R;

		if (Keyboard::Get()->Press(VK_UP)) {
			this->Position(pos - (dir * speed * Time::Get()->Delta()));
			//D3DXMatrixRotationX(&R, sinf(Time::Get()->Running()*2.0f)*0.25f);	//각도*속도
			D3DXMatrixRotationX(&R, Math::ToRadian(Time::Get()->Running()*-rotSpeed));	//각도*속도

			lbWheelBone->Local(R*lbWheel);
			rbWheelBone->Local(R*rbWheel);
			lfWheelBone->Local(R*lfWheel);
			rfWheelBone->Local(R*rfWheel);

		}
		else if (Keyboard::Get()->Press(VK_DOWN)) {
			this->Position(pos + (dir * speed * Time::Get()->Delta()));
			//D3DXMatrixRotationX(&R, sinf(Time::Get()->Running()*2.0f)*0.25f);	//각도*속도
			D3DXMatrixRotationX(&R, Math::ToRadian(Time::Get()->Running()*rotSpeed));	//각도*속도

			lbWheelBone->Local(R*lbWheel);
			rbWheelBone->Local(R*rbWheel);
			lfWheelBone->Local(R*lfWheel);
			rfWheelBone->Local(R*rfWheel);


		}
		if (Keyboard::Get()->Press(VK_LEFT)) {
			D3DXMatrixRotationAxis(&matRotation, &-up, Math::ToRadian(radian)*Time::Get()->Delta());
			//rotate wheel
			//D3DXMatrixRotationY(&R, Math::ToRadian(Time::Get()->Running()*-10));	//각도*속도
			//lbWheelBone->Local(R*lbWheel);

			this->World(matRotation* this->World());
		}
		else if (Keyboard::Get()->Press(VK_RIGHT)) {
			D3DXMatrixRotationAxis(&matRotation, &up, Math::ToRadian(radian)*Time::Get()->Delta());
			//rotate wheel
			//D3DXMatrixRotationY(&R, Math::ToRadian(Time::Get()->Running()*30));	//각도*속도
			//lbWheelBone->Local(R*lbWheel);


			this->World(matRotation* this->World());
		}

		if (Keyboard::Get()->Press('Z')) {
			D3DXMatrixRotationY(&R, Math::ToRadian(Time::Get()->Running()*rotSpeed));
			turretBone->Local(R*turret);
			turret = turretBone->Local();

		}
		else if (Keyboard::Get()->Press('X')) {
			D3DXMatrixRotationY(&R, Math::ToRadian(Time::Get()->Running()*-rotSpeed));
			turretBone->Local(R*turret);
			turret = turretBone->Local();



		}

	
	

	}

	

}

void GameTank::Render()
{
	__super::Render();
}
