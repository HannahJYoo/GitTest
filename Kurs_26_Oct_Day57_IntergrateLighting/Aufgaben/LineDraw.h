#pragma once

class LineDraw
{
private:
	class ColorBuffer;

public:
	LineDraw();
	~LineDraw();

	void BufferOpen();
	void BufferClose();

	void SetWorld(D3DXMATRIX& mat) { 
		matWorld = mat;
		worldBuffer->SetMatrix(matWorld);
	}

	void AddVertex(D3DXVECTOR3& val);

	void ConnectVertex(UINT start, UINT end);

	void AutoConnectVertex_Cube();

	void Draw(D3DXMATRIX& world);
	
	static void Color(D3DXCOLOR& val);
	static D3DXCOLOR& Color();

	static void Visible(bool& val);
	static bool& Visible();

	static void Delete();

private:
	Shader* shader;
	WorldBuffer* worldBuffer;

	UINT width, height;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	UINT vertexCount, indexCount;

	Vertex* vertices;
	UINT* indices;

	static ColorBuffer* colorBuffer;
	static bool isColorBufferIn;
	static bool isVisible;
	
	vector<D3DXVECTOR3> inputVertexBuffer;
	vector<UINT> inputIndexBuffer;

	bool isBufferOpen;

	list<pair<D3DXVECTOR3, D3DXVECTOR3>> m_lineList;

	D3DXMATRIX matWorld;

private:
	class ColorBuffer : public ShaderBuffer
	{
	public:
		ColorBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXCOLOR(1, 1, 1, 1);
		}
		~ColorBuffer() {}

		struct Struct
		{
			D3DXCOLOR Color;
		} Data;
	};
};