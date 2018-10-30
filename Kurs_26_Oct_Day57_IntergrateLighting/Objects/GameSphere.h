#pragma once
#include "Execute.h"

class DrawNormalLine;
class DrawLandscape : public Execute
{

public:
	DrawLandscape(ExecuteValues* values);
	~DrawLandscape();

	// Execute을(를) 통해 상속됨
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();


private:
	class Terrain* terrain;
};