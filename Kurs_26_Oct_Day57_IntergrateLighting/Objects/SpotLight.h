#pragma once

class SpotLight 
{
public:
	SpotLight(ExecuteValues * values);
	~SpotLight();

	void Update();
	void Render();
	void PostRender();

public:
	struct Desc
	{
		D3DXVECTOR3 Position;
		float InnerAngle;
		D3DXVECTOR3 Color;
		float OuterAngle;
		D3DXVECTOR3 Direction;
		float Padding;

	};
	int plIndex;
	float s = 1;

private:
	ExecuteValues * values;

	struct SpotLightInfos
	{
		UINT idx;
		Desc desc;
		class DebugDraw* debugDraw;

		SpotLightInfos()
		{
			idx = 0;
			debugDraw = NULL;
		}
	};
	vector<SpotLightInfos> spotlights;

private:
	class Buffer : public ShaderBuffer
	{
	public:
		Buffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			for (int i = 0; i < 32; i++) {
				Data.Lights[i].Position = D3DXVECTOR3(0, 0, 0);
				Data.Lights[i].InnerAngle = 0.0f;
				Data.Lights[i].Color = D3DXVECTOR3(0, 0, 0);
				Data.Lights[i].OuterAngle = 0.0f;
				Data.Lights[i].Direction = D3DXVECTOR3(0, 0, 0);
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