#pragma once
#include "Execute.h"

class TestShadow : public Execute
{

public:
	TestShadow(ExecuteValues* values);
	~TestShadow();

	// Execute을(를) 통해 상속됨
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

	class Shadow* shadow;

};