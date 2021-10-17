Texture2D tex;

SamplerState sampl;

float4 main(float2 texcoord : TextureCoordinate, float3 normal : Normal) : SV_Target
{
	return tex.Sample(sampl, texcoord);
}