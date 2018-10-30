#pragma once

class PointLight 
{
public:
	PointLight(ExecuteValues * values);
	~PointLight();

	void Update();
	void Render();
	void PostRender();

public:
	struct Desc
	{
		D3DXVECTOR3 Position;
		float Range;
		D3DXVECTOR3 Color;
		float Intensity;
	};
	int plIndex;

private:
	ExecuteValues * values;

	struct PointLightInfos
	{
		UINT idx;
		Desc desc;
		class DebugDraw* debugDraw;

		PointLightInfos()
		{
			idx = 0;
			debugDraw = NULL;
		}
	};
	vector<PointLightInfos> pointlights;

private:
	class Buffer : public ShaderBuffer
	{
	public:
		Buffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			for (int i = 0; i < 32; i++) {
				Data.Lights[i].Position = D3DXVECTOR3(0, 0, 0);
				Data.Lights[i].Color = D3DXVECTOR3(0, 0, 0);
				Data.Lights[i].Intensity = 0;
				Data.Lights[i].Range = 0;
			}
			Data.Count = 0;
		}

		struct Struct
		{
			Desc Lights[32];
			UINT Count;
			float Padding[3];
		}Data;
	};

	Buffer* buffer;

public:
	void Add(Desc& desc);
};