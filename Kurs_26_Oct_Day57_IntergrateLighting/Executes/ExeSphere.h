#pragma once
#include "Execute.h"

class ExeSphere : public Execute
{
private:
	class ColorBuffer;

public:
	ExeSphere(ExecuteValues* values);
	~ExeSphere();

	// Execute을(를) 통해 상속됨
	 void Update() ;
	 void PreRender() ;
	 void Render() ;
	 void PostRender() ;
	 void ResizeScreen() ;


private:
	Shader * shader;
	WorldBuffer* worldBuffer;

	UINT width, height;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount, indexCount;

	VertexTextureNormal* vertices;
	UINT* indices;


	int fillModeNumber;
	ID3D11RasterizerState* fillMode[3];

private:
	class ColorBuffer : public ShaderBuffer {
	public:
		ColorBuffer()
			:ShaderBuffer(&Data,sizeof(Data))
		{
			Data.Color = D3DXCOLOR(0,0,0,0);
		}
		~ColorBuffer() 
		{
		
		}
		struct Struct {
			D3DXCOLOR Color;
		} Data;
	};

};