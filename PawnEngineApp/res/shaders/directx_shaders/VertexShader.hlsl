struct VS_OUT {
	float2 texcoord : TextureCoordinates;
	float4 position : SV_Position;
};

VS_OUT main(float2 position : Position, float2 texcoord : TextureCoordinates) {
	VS_OUT result;
	result.position = float4(position.x, position.y, 0.0f, 1.0f);
	result.texcoord = texcoord;
	return result;
}