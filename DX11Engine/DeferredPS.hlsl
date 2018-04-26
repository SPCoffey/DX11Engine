// Texture Variables
Texture2D diffuseTexture	: register(t0);
Texture2D normalTexture		: register(t1);
Texture2D roughnessTexture	: register(t2);
Texture2D metalTexture		: register(t3);
SamplerState basicSampler	: register(s0);

struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float2 uv			: TEXCOORD0;
	float depth			: TEXCOORD1;
};

struct PSOutput
{
	float4 color	: SV_TARGET0;
	float4 normals	: SV_TARGET1;
	float4 roughness: SV_TARGET2;
	float4 metal	: SV_TARGET3;
	float4 depth	: SV_TARGET4;
};

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
PSOutput main(VertexToPixel input)
{
	PSOutput OUT;

	// Fix for poor normals: re-normalizing interpolated normals
	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);

	float3 unpackedNormal = normalTexture.Sample(basicSampler, input.uv).rgb * 2.0f - 1.0f;

	float3 N = input.normal;
	float3 T = normalize(input.tangent - N * dot(input.tangent, N));
	float3 B = cross(T, N);

	float3x3 TBN = float3x3(T, B, N);

	input.normal = normalize(mul(unpackedNormal, TBN));

	OUT.normals = float4(input.normal, 1);

	float4 surfaceColor = diffuseTexture.Sample(basicSampler, input.uv);

	OUT.color = float4(pow(surfaceColor.rgb, 2.2), 1);

	float roughness = roughnessTexture.Sample(basicSampler, input.uv).r;
	OUT.roughness.r = roughness;

	float metal = metalTexture.Sample(basicSampler, input.uv).r;
	OUT.metal.r = metal;

	OUT.depth = float4(input.depth.x, input.depth.x, input.depth.x, 1);

	return OUT;
}