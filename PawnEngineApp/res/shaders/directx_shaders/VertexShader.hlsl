struct VS_OUT {
	float3 color : Color;
	float4 position : SV_Position;
};

cbuffer Transformation {
	row_major matrix transformation;
};

VS_OUT main(float2 position : Position, float3 color : Color)
{
	VS_OUT result;
	result.position = mul(float4(position.x, position.y, 0.0f, 1.0f), transformation);
	result.color = color;
	return result;
}