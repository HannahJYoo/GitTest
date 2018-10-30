#include "stdafx.h"
#include "LineDraw.h"

LineDraw::ColorBuffer* LineDraw::colorBuffer = NULL;
bool LineDraw::isColorBufferIn = false;
bool LineDraw::isVisible = true;

LineDraw::LineDraw()
	:indexCount(0), vertexCount(0), isBufferOpen(false), vertexBuffer(NULL), indexBuffer(NULL)
{
	shader = new Shader(Shaders + L"003_Color.hlsl");
	worldBuffer = new WorldBuffer();

	if(colorBuffer == NULL)
		colorBuffer = new ColorBuffer();
}

LineDraw::~LineDraw()
{
	if (inputVertexBuffer.size() != 0)
		inputVertexBuffer.clear();
	if (inputIndexBuffer.size() != 0)
		inputIndexBuffer.clear();

	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);

	SAFE_DELETE_ARRAY(indices);
	SAFE_DELETE_ARRAY(vertices);

	if (colorBuffer != NULL)
		SAFE_DELETE(colorBuffer);

	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(shader);
}

void LineDraw::BufferOpen()
{
	if (isBufferOpen == true)
		return;
	isBufferOpen = true;

	if (inputVertexBuffer.size() != 0)
		inputVertexBuffer.clear();
	if (inputIndexBuffer.size() != 0)
		inputIndexBuffer.clear();

	if (indexCount != 0)
		SAFE_RELEASE(indexBuffer);
	if (vertexCount != 0)
		SAFE_RELEASE(vertexBuffer);

	vertexCount = 0;
	indexCount = 0;
}

void LineDraw::BufferClose()
{
	if (isBufferOpen == false)
		return;
	isBufferOpen = false;

	vertices = new Vertex[vertexCount];
	for (size_t i = 0; i < vertexCount; i++)
		vertices[i].Position = inputVertexBuffer[i];

	indices = new UINT[indexCount];
	for (size_t i = 0; i < indexCount; i++)
		indices[i] = inputIndexBuffer[i];
		

	//	CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//	CreateIndexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = indices;

		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer);
		assert(SUCCEEDED(hr));
	}
}


void LineDraw::AddVertex(D3DXVECTOR3 & val)
{
	if (isBufferOpen == false)
		return;

	inputVertexBuffer.push_back(val);

	vertexCount++;
}

void LineDraw::ConnectVertex(UINT start, UINT end)
{
	if (isBufferOpen == false)
		return;

	inputIndexBuffer.push_back(start);
	inputIndexBuffer.push_back(end);

	indexCount += 2;
}

void LineDraw::AutoConnectVertex_Cube()
{
	this->ConnectVertex(0, 2);
	this->ConnectVertex(2, 3);
	this->ConnectVertex(3, 1);
	this->ConnectVertex(1, 0);

	this->ConnectVertex(4, 6);
	this->ConnectVertex(6, 7);
	this->ConnectVertex(7, 5);
	this->ConnectVertex(5, 4);

	this->ConnectVertex(0, 4);
	this->ConnectVertex(1, 5);
	this->ConnectVertex(2, 6);
	this->ConnectVertex(3, 7);
}

void LineDraw::Draw(D3DXMATRIX & world)
{
	if (isVisible == false)
		return;

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	worldBuffer->SetMatrix(world);
	worldBuffer->SetVSBuffer(1);

	if (isColorBufferIn == false)
	{
		colorBuffer->SetPSBuffer(2);
		isColorBufferIn = true;
	}

	shader->Render();

	D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
}

void LineDraw::Color(D3DXCOLOR & val)
{
	colorBuffer->Data.Color = val;
	isColorBufferIn = false;
}

D3DXCOLOR & LineDraw::Color()
{
	return colorBuffer->Data.Color;
}

void LineDraw::Visible(bool & val)
{
	isVisible = val;
}

bool & LineDraw::Visible()
{
	return isVisible;
}

void LineDraw::Delete()
{
	if (colorBuffer)
		SAFE_DELETE(colorBuffer);
}
