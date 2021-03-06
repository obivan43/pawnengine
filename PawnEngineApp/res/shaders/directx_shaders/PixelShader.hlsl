float4 main(float2 texcoord : TextureCoordinate, float3 normal : Normal) : SV_Target
{
	float3 normolized = normalize(normal);
	float3 color = (normal + 1) * 0.5f;
	return float4(color.rgb, 1.0f);
}