#pragma once

class Shadow
{
public:
	const float Width = 2048;
	const float Height = 2048;
	
public:
	Shadow(ExecuteValues* values);
	~Shadow();

	void Add(class GameModel* obj);

	void Update();
	void PreRender();
	void Render();

private:
	ExecuteValues* values;
	Shader* shaderDepth;
	Shader* shaderRender;
	RenderTarget* depthShadow;
	class Render2D* depthRender;

	vector<class GameModel* > objs;

	class Perspective* perspective;
	ViewProjectionBuffer* vpBuffer;

	SamplerState* samplerState[2];

private:
	class Buffer : public ShaderBuffer
	{
	public:
		Buffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Bias = 0.005f;
			Data.Selected = 0;
		}

		struct Struct
		{
			D3DXVECTOR2 Size;
			float Bias;
			int Selected;
			
		} Data;
	};
	Buffer* buffer;
};