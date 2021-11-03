#pragma pack_matrix(row_major)

cbuffer TransformationCB : register(b0)
{
	matrix transformation;
	matrix inverseTransposeTransformation;
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
	matrix MVP = mul(transformation, mul(view, projection));
	
	VS_OUT result;

	result.tangent = tangent;
	result.binormal = binormal;
	result.texcoord = texcoord;
	
	result.position = mul(float4(position, 1.0f), MVP);
	result.normal = normalize(mul(float4(normal, 1.0f), inverseTransposeTransformation)).xyz;
	result.worldPosition = mul(float4(position, 1.0f), transformation).xyz;
	
	return result;
}