Texture2D tex;

SamplerState sampl;

float4 main(float2 texcoord : TextureCoordinate) : SV_Target
{
	return tex.Sample(sampl, texcoord);
}