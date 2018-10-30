#include "stdafx.h"
#include "ExeSphere.h"

ExeSphere::ExeSphere(ExecuteValues * values)
	:Execute(values)
{
	

	shader = new Shader(Shaders + L"HA002_Sphere.hlsl");
	worldBuffer = new WorldBuffer();


	//Create VertexData
	{
		ifstream fin;
		char input;

		fin.open(Contents + L"Model/sphere.txt");
		fin.get(input);
		while (input != ':')
		{
			fin.get(input);
		}

		fin >> vertexCount;
		indexCount = vertexCount;

		fin.get(input);
		while (input != ':')
		{
			fin.get(input);
		}
		fin.get(input);
		fin.get(input);

		vertices = new VertexTextureNormal[vertexCount];
		indices = new UINT[indexCount];
		

		for (int i = 0; i < vertexCount; i++)
		{
			fin >> vertices[i].Position.x >> vertices[i].Position.y >> vertices[i].Position.z;
			fin >> vertices[i].Uv.x >> vertices[i].Uv.y;
			fin >> vertices[i].Normal.x >> vertices[i].Normal.y >> vertices[i].Normal.z;

			indices[i] = i;	
		}
		fin.close();
	}

	
	
	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexTextureNormal) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;
		
		HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create IndexBuffer
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

	{
		fillModeNumber = 0;
		D3D11_RASTERIZER_DESC desc;
		States::GetRasterizerDesc(&desc);
		States::CreateRasterizer(&desc, &fillMode[0]);

		desc.FillMode = D3D11_FILL_WIREFRAME;
		States::CreateRasterizer(&desc, &fillMode[1]);

		desc.CullMode = D3D11_CULL_NONE;
		//desc.FillMode = D3D11_FILL_WIREFRAME;
		States::CreateRasterizer(&desc, &fillMode[2]);
	}
}

ExeSphere::~ExeSphere()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);

	SAFE_DELETE_ARRAY(indices);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(shader);
}

void ExeSphere::Update()
{
	
}

void ExeSphere::PreRender()
{

}

void ExeSphere::Render()
{
	UINT stride = sizeof(VertexTextureNormal);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	D3D::GetDC()->RSSetState(fillMode[fillModeNumber]);

	worldBuffer->SetVSBuffer(1);	//register num
	shader->Render();

	D3D::GetDC()->DrawIndexed(indexCount, 0, 0);
		
}

void ExeSphere::PostRender()
{
	ImGui::Begin("SphereInfo");
	ImGui::SliderInt("Wireframe", &fillModeNumber, 0, 2);
	ImGui::End();
}

void ExeSphere::ResizeScreen()
{
}
