cbuffer TransformationCB : register(b0) {
	matrix transformation;
};

cbuffer ViewProjectionCB : register(b1) {
	matrix  projection;
	matrix  view;
};

struct VS_OUT {
	float2 texcoord : TextureCoordinate;
	float3 normal : Normal;
	float4 position : SV_Position;
};

VS_OUT main(float3 position : Position, float3 normal : Normal, float2 texcoord : TextureCoordinate) {
	matrix tView = transpose(view);
	matrix tProjection = transpose(projection);
	matrix tTransformation = transpose(transformation);

	matrix MVP = mul(tTransformation, mul(tView, tProjection));
	VS_OUT result;
	result.position = mul(float4(position, 1.0f), MVP);
	result.texcoord = texcoord;
	result.normal = normal;
	
	return result;
}