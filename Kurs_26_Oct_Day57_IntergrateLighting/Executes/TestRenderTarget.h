#pragma once
#include "Execute.h"

class TestRenderTarget : public Execute
{

public:
	TestRenderTarget(ExecuteValues* values);
	~TestRenderTarget();

	// Execute을(를) 통해 상속됨
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen() {}




private:
	Shader* shader;



	class Sky* sky;
	class MeshPlane* plane;
	class MeshSphere* sphere;
	class MeshCube* cube[2];

	RenderTarget* renderTarget[3];
	Render2D* render2D;
	Render2D* postEffect[3];

	class PointLight* pointLight;



private:
	class NormalBuffer : public ShaderBuffer
	{
	public:
		NormalBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.VisibleNormal = 1;
			
		}

		struct Struct
		{
			int VisibleNormal;
			

			float Padding[3];
		} Data;
	};
	NormalBuffer* buffer;

};