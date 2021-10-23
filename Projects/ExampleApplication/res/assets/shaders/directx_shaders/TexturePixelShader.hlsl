Texture2D tex;

SamplerState sampl;

struct PS_INPUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

float4 main(PS_INPUT input) : SV_Target
{
	return tex.Sample(sampl, input.texcoord) * color;
}