struct PS_INPUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float3 tangent : Tangent;
	float3 binormal : Binormal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

float4 main(PS_INPUT input) : SV_Target
{
	float3 color = (input.normal + 1) * 0.5;
	return float4(color.rgb, 1.0f);
}