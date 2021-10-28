Texture2D tex;

SamplerState sampl;

struct PS_INPUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float3 tangent : Tangent;
	float3 binormal : Binormal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

struct DirectionaLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 direction;
};

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

cbuffer DirectionalLightCB : register(b3)
{
	DirectionaLight directionalLight;
};

float4 main(PS_INPUT input) : SV_Target
{
	float3 samplerColor = tex.Sample(sampl, input.texcoord).xyz * color.xyz;

	return float4(samplerColor, 1.0);
}