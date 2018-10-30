#pragma once
#include "Execute.h"

class TestFrustum : public Execute
{

public:
	TestFrustum(ExecuteValues* values);
	~TestFrustum();

	// Execute을(를) 통해 상속됨
	void Update();
	void PreRender() {}
	void Render();
	void PostRender() {}
	void ResizeScreen() {}




private:
	Shader* shader;
	UINT drawCount;
	vector<D3DXVECTOR3> positions;

	class MeshPlane* plane;
	class MeshSphere* sphere;

	class Frustum* frustum;
	class Camera* camera;
	class Perspective* projection;
};