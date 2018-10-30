#pragma once
#include "Execute.h"

class DrawNormalLine;
class DrawLandscape : public Execute
{

public:
	DrawLandscape(ExecuteValues* values);
	~DrawLandscape();

	// Execute��(��) ���� ��ӵ�
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();


private:
	class Terrain* terrain;
};