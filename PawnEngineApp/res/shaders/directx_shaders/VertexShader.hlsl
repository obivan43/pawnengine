cbuffer Transformation : register(b0) {
	matrix transformation;
};

cbuffer ViewProjection : register(b1) {
	matrix  projection;
	matrix  view;
};

struct VS_OUT {
	float2 texcoord : TextureCoordinates;
	float4 position : SV_Position;
};

VS_OUT main(float3 position : Position, float2 texcoord : TextureCoordinates) {
	matrix tView = transpose(view);
	matrix tProjection = transpose(projection);
	matrix tTransformation = transpose(transformation);

	matrix MVP = mul(mul(tView, tProjection), tTransformation);
	VS_OUT result;
	result.position = mul(float4(position, 1.0f), MVP);
	result.texcoord = texcoord;
	return result;
}