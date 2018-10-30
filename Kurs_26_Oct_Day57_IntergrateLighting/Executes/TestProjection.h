#pragma once
#include "Execute.h"

class TestProjection : public Execute
{

public:
	TestProjection(ExecuteValues* values);
	~TestProjection();

	// Execute��(��) ���� ��ӵ�
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen() {}




private:
	Shader* hanjoShader;
	Shader* planeShader;
	class GameAnimModel* hanjo;
	class MeshPlane* plane;

	class Projection* projection;
};