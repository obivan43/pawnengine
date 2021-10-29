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

struct DirectionalLight
{
	float3 ambient;
	float ambientIntensity;
	float3 diffuse;
	float diffuseIntensity;
	float3 specular;
	float specularIntensity;
	float4 direction;
};

cbuffer Texture2DCB : register(b2)
{
	float4 color;
};

cbuffer LightCB : register(b3)
{
	DirectionalLight directionalLight;
	float4 eyePosition;
};

void ComputeDirectionalLight(
	DirectionalLight light,
	float3 normal,
	float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
) {
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = -light.direction.xyz;
	ambient = float4(light.ambient * light.ambientIntensity, 0.0f);
	
	float diffuseFactor = dot(lightVec, normal);
[flatten]
	if (diffuseFactor > 0.0f)
	{
		diffuse = float4(diffuseFactor * light.diffuseIntensity * light.diffuse, 0.0f);
		
		//float3 v = reflect(-lightVec, normal);
		//float specFactor = pow(max(dot(v, toEye), 0.0f), 32.0f);
		//spec = float4(specFactor * light.specularIntensity * light.specular, 0.0f);
	}
}

float4 main(PS_INPUT input) : SV_Target
{
	float3 toEye = normalize(eyePosition.xyz - input.worldPosition);
	float4 samplerColor = tex.Sample(sampl, input.texcoord) * color;

	float4 A, D, S;
	ComputeDirectionalLight(directionalLight, input.normal, toEye, A, D, S);
	
	float4 resultLight = A + D + S;
	
	return samplerColor * resultLight;
}