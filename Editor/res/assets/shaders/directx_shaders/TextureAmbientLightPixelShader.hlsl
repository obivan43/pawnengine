Texture2D tex;

SamplerState sampl;

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

cbuffer EnvironmentCB : register(b3)
{
	float3 ambientLightColor;
	float ambientLightIntensity;
};

float4 main(float2 texcoord : TextureCoordinate) : SV_Target
{
	float4 samplerColor = tex.Sample(sampl, texcoord) * color;
	float4 ambientLight = float4(ambientLightColor * ambientLightIntensity, 1.0);
	
	return samplerColor * ambientLight;
}