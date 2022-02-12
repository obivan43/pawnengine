Texture2D tex2D : register(t0);
Texture2D font : register(t1);

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

cbuffer ASCIISize : register(b4)
{
	int asciiWidth;
	int asciiHeight;
};

void ComputeDirectionalLight(
	DirectionalLight light,
	float3 normal,
	float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	float3 lightVec = normalize(-light.direction.xyz);
	ambient = float4(light.ambient * light.ambientIntensity, 0.0f);
	
	float diffuseFactor = max(dot(lightVec, normal), 0.0f);
	diffuse = float4(diffuseFactor * light.diffuseIntensity * light.diffuse, 1.0f);
		
	float3 v = reflect(-lightVec, normal);
	float specFactor = diffuseFactor * pow(max(dot(v, toEye), 0.0f), 16.0f);
	spec = float4(specFactor * light.specularIntensity * light.specular, 1.0f);
}

#define mod(x,y) (x-y*floor(x/y))

#define P(id,a,b,c,d,e,f,g,h) if( id == int(pos.y) ){ int pa = a+2*(b+2*(c+2*(d+2*(e+2*(f+2*(g+2*(h))))))); cha = floor(mod(float(pa)/pow(2.,float(pos.x)-1.),2.)); }

float gray(float4 _i)
{
	return _i.x * 0.299 + _i.y * 0.587 + _i.z * 0.114;
}


float4 ComputeASCII(float4 inputPosition, float2 TextureCoordinate)
{
	/* first variant */
	/*float4 texelColor = tex.Sample(sampl, TextureCoordinate) * color; 
	
	int gray = (texelColor) * 256 / 16;
	float g = gray;
	
	float x = mod((TextureCoordinate.x * (asciiWidth / 128)).x, 1);
	float y = mod((TextureCoordinate.y * (asciiHeight / 128)).x, 1);
	
	return (1 - font.Sample(sampl, float2(mod(x + g / 16, 1), y))) * texelColor;*/
	
	/* second variant */
	float4 tex = tex2D.Sample(sampl, TextureCoordinate); 
	int2 pos = int2(mod(inputPosition.x/1., 8.), mod(inputPosition.y/1., 12.));
	float g = gray(tex2D.Sample(sampl, TextureCoordinate) * color);
	float cha = 0.;
	
	if (g < .125)
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 0, 0, 0, 0, 0);
		P(9, 0, 0, 0, 0, 0, 0, 0, 0);
		P(8, 0, 0, 0, 0, 0, 0, 0, 0);
		P(7, 0, 0, 0, 0, 0, 0, 0, 0);
		P(6, 0, 0, 0, 0, 0, 0, 0, 0);
		P(5, 0, 0, 0, 0, 0, 0, 0, 0);
		P(4, 0, 0, 0, 0, 0, 0, 0, 0);
		P(3, 0, 0, 0, 0, 0, 0, 0, 0);
		P(2, 0, 0, 0, 0, 0, 0, 0, 0);
		P(1, 0, 0, 0, 0, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .25) // .
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 0, 0, 0, 0, 0);
		P(9, 0, 0, 0, 0, 0, 0, 0, 0);
		P(8, 0, 0, 0, 0, 0, 0, 0, 0);
		P(7, 0, 0, 0, 0, 0, 0, 0, 0);
		P(6, 0, 0, 0, 0, 0, 0, 0, 0);
		P(5, 0, 0, 0, 0, 0, 0, 0, 0);
		P(4, 0, 0, 0, 1, 1, 0, 0, 0);
		P(3, 0, 0, 0, 1, 1, 0, 0, 0);
		P(2, 0, 0, 0, 0, 0, 0, 0, 0);
		P(1, 0, 0, 0, 0, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .375) // ,
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 0, 0, 0, 0, 0);
		P(9, 0, 0, 0, 0, 0, 0, 0, 0);
		P(8, 0, 0, 0, 0, 0, 0, 0, 0);
		P(7, 0, 0, 0, 0, 0, 0, 0, 0);
		P(6, 0, 0, 0, 0, 0, 0, 0, 0);
		P(5, 0, 0, 0, 0, 0, 0, 0, 0);
		P(4, 0, 0, 0, 1, 1, 0, 0, 0);
		P(3, 0, 0, 0, 1, 1, 0, 0, 0);
		P(2, 0, 0, 0, 0, 1, 0, 0, 0);
		P(1, 0, 0, 0, 1, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .5) // -
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 0, 0, 0, 0, 0);
		P(9, 0, 0, 0, 0, 0, 0, 0, 0);
		P(8, 0, 0, 0, 0, 0, 0, 0, 0);
		P(7, 0, 0, 0, 0, 0, 0, 0, 0);
		P(6, 1, 1, 1, 1, 1, 1, 1, 0);
		P(5, 0, 0, 0, 0, 0, 0, 0, 0);
		P(4, 0, 0, 0, 0, 0, 0, 0, 0);
		P(3, 0, 0, 0, 0, 0, 0, 0, 0);
		P(2, 0, 0, 0, 0, 0, 0, 0, 0);
		P(1, 0, 0, 0, 0, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .625) // +
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 0, 0, 0, 0, 0);
		P(9, 0, 0, 0, 1, 0, 0, 0, 0);
		P(8, 0, 0, 0, 1, 0, 0, 0, 0);
		P(7, 0, 0, 0, 1, 0, 0, 0, 0);
		P(6, 1, 1, 1, 1, 1, 1, 1, 0);
		P(5, 0, 0, 0, 1, 0, 0, 0, 0);
		P(4, 0, 0, 0, 1, 0, 0, 0, 0);
		P(3, 0, 0, 0, 1, 0, 0, 0, 0);
		P(2, 0, 0, 0, 0, 0, 0, 0, 0);
		P(1, 0, 0, 0, 0, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .75) // *
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 0, 1, 0, 0, 0, 0);
		P(9, 1, 0, 0, 1, 0, 0, 1, 0);
		P(8, 0, 1, 0, 1, 0, 1, 0, 0);
		P(7, 0, 0, 1, 1, 1, 0, 0, 0);
		P(6, 0, 0, 0, 1, 0, 0, 0, 0);
		P(5, 0, 0, 1, 1, 1, 0, 0, 0);
		P(4, 0, 1, 0, 1, 0, 1, 0, 0);
		P(3, 1, 0, 0, 1, 0, 0, 1, 0);
		P(2, 0, 0, 0, 1, 0, 0, 0, 0);
		P(1, 0, 0, 0, 0, 0, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else if (g < .875) // #
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 1, 0, 0, 1, 0, 0);
		P(9, 0, 0, 1, 0, 0, 1, 0, 0);
		P(8, 1, 1, 1, 1, 1, 1, 1, 0);
		P(7, 0, 0, 1, 0, 0, 1, 0, 0);
		P(6, 0, 0, 1, 0, 0, 1, 0, 0);
		P(5, 0, 1, 0, 0, 1, 0, 0, 0);
		P(4, 0, 1, 0, 0, 1, 0, 0, 0);
		P(3, 1, 1, 1, 1, 1, 1, 1, 0);
		P(2, 0, 1, 0, 0, 1, 0, 0, 0);
		P(1, 0, 1, 0, 0, 1, 0, 0, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else // @
	{
		P(11, 0, 0, 0, 0, 0, 0, 0, 0);
		P(10, 0, 0, 1, 1, 1, 1, 0, 0);
		P(9, 0, 1, 0, 0, 0, 0, 1, 0);
		P(8, 1, 0, 0, 0, 1, 1, 1, 0);
		P(7, 1, 0, 0, 1, 0, 0, 1, 0);
		P(6, 1, 0, 0, 1, 0, 0, 1, 0);
		P(5, 1, 0, 0, 1, 0, 0, 1, 0);
		P(4, 1, 0, 0, 1, 0, 0, 1, 0);
		P(3, 1, 0, 0, 1, 1, 1, 1, 0);
		P(2, 0, 1, 0, 0, 0, 0, 0, 0);
		P(1, 0, 0, 1, 1, 1, 1, 1, 0);
		P(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	
	float3 col = tex.xyz / max(tex.x, max(tex.y, tex.z));
	return float4(cha * col, 1.);
}

float4 main(PS_INPUT input) : SV_Target 
{
		float3 toEye = normalize(eyePosition.xyz - input.worldPosition);
		float4 samplerColor = ComputeASCII(input.position, input.texcoord);

		float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
		ComputeDirectionalLight(directionalLight, input.normal, toEye, A, D, S);
	
		float4 resultLight = A + D + S;
	
		return samplerColor * saturate(resultLight);
}
