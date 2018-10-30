#pragma once
#include "Execute.h"

class TestLandscape : public Execute
{

public:
	TestLandscape(ExecuteValues* values);
	~TestLandscape();

	// Execute을(를) 통해 상속됨
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen() {}




private:
	Shader* shader;
	Shader* depthShader;


	class Sky* sky;
	class TerrainRender* terrain;
	class Water* water;
	
	


};