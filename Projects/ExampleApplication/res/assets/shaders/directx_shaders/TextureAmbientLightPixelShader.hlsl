Texture2D tex;

SamplerState sampl;

struct PS_INPUT
{
	float4 position : SV_Position;
	float3 normal : Normal;
	float3 tangent : Tangent;
	float3 binormal : Binormal;
	float2 texcoord : TextureCoordinate;
	float3 worldPosition : WorldPosition;
};

cbuffer ViewProjectionCB : register(b1)
{
	matrix projection;
	matrix view;
};

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

cbuffer EnvironmentCB : register(b3)
{
	float3 lightPosition;
	float ambientIntensity;
	
	float3 lightColor;
	float diffuseIntensity;
};

float4 main(PS_INPUT input) : SV_Target
{
	float3 samplerColor = tex.Sample(sampl, input.texcoord).xyz * color.xyz;
	
	float3 ambientLight = lightColor * ambientIntensity;

	float3 vetorToLight = normalize(lightPosition - input.worldPosition);
	float3 diffuse = max(dot(vetorToLight, input.normal), 0);
	float3 diffuseLight = diffuse * (lightColor * diffuseIntensity);
	
	float3 reflectionDirection = reflect(vetorToLight, input.normal);
	float spec = pow(max(dot(-reflectionDirection, vetorToLight), 0.0f), 32.0f);
	float3 specularLight = lightColor * (spec * float3(1.0f, 1.0f, 1.0f));
	
	float3 light = ambientLight + diffuseLight + specularLight;
	
	return float4(samplerColor * light, 1.0);
}