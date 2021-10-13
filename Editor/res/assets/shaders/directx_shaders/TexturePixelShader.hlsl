Texture2D tex;

SamplerState sampl;

cbuffer Texture2DCB : register(b2) {
	float4 color;
};

float4 main(float2 texcoord : TextureCoordinate, float3 normal : Normal) : SV_Target
{
	return tex.Sample(sampl, texcoord) * color;
}