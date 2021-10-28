cbuffer TransformationCB : register(b0)
{
	matrix transformation;
};

cbuffer ViewProjectionCB : register(b1) 
{
	matrix  projection;
	matrix  view;
};

struct VS_OUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float3 tangent : Tangent;
	float3 binormal : Binormal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

VS_OUT main(
	float3 position : Position,
	float3 normal : Normal,
	float3 tangent : Tangent,
	float3 binormal : Binormal,
	float2 texcoord : TextureCoordinate
) {
	matrix tView = transpose(view);
	matrix tProjection = transpose(projection);
	matrix tTransformation = transpose(transformation);

	matrix MVP = mul(tTransformation, mul(tView, tProjection));
	VS_OUT result;
	result.position = mul(float4(position, 1.0f), MVP);
	result.normal = normalize(mul(float4(normal, 0.0f), tTransformation)).xyz;
	result.tangent = tangent;
	result.binormal = binormal;
	result.texcoord = texcoord;
	result.worldPosition = mul(float4(position, 1.0f), tTransformation).xyz;
	
	return result;
}