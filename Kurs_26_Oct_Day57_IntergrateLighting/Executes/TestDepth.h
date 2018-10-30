#pragma once
#include "Execute.h"

class TestDepth : public Execute
{

public:
	TestDepth(ExecuteValues* values);
	~TestDepth();

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
	class MeshPlane* plane;
	class MeshSphere* sphere;
	class MeshCube* cube[2];

	RenderTarget* renderTarget[2];

	Render2D* postEffect;

	

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