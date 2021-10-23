Texture2D tex;

SamplerState sampl;

struct PS_INPUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

cbuffer EnvironmentCB : register(b3)
{
	float3 ambientLightColor;
	float ambientLightIntensity;
	
	float3 directionalLightColor;
	float directionalLightIntensity;
	float4 directionalLightPosition;
};

float4 main(PS_INPUT input) : SV_Target
{
	float3 samplerColor = tex.Sample(sampl, input.texcoord).xyz * color.xyz;
	float3 ambientLight = ambientLightColor * ambientLightIntensity;

	float3 vetorToLight = normalize(directionalLightPosition.xyz - input.worldPosition);
	float3 diffuseLightIntensity = max(dot(vetorToLight, input.normal), 0);
	float3 diffuseLight = diffuseLightIntensity * directionalLightIntensity * directionalLightColor;
	
	float3 light = ambientLight + diffuseLight;
	
	return float4(samplerColor * light, 1.0);
}