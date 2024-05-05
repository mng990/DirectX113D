#include "00. Global.fx"
#include "00. Light.fx"

#define MAX_MODEL_TRANSFORMS 500

cbuffer BoneBuffer
{
    matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};

uint BoneIndex;

struct VS_IN
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLEND_INDICES;
    float4 blendWeights : BLEND_WEIGHTS;
    // INSTANCING
    matrix world : INST;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

/*
VS_OUT VS(VS_IN input)
{
    VS_OUT output;

    output.position = mul(input.position, W);
    output.worldPosition = output.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = input.normal;

    return output;
}
*/

VS_OUT VS(VS_IN input)
{
    VS_OUT output;

    output.position = mul(input.position, BoneTransforms[BoneIndex]); // Model Global
    output.position = mul(output.position, input.world); // W
    output.worldPosition = input.position;
    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = input.normal;

    return output;
}


float4 PS(VS_OUT input) : SV_TARGET
{
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

float4 PS_RED(VS_OUT input) :SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);

}
technique11 T0
{
	PASS_VP(P0, VS, PS)
    PASS_VRP(P1, VS, FillModeWireFrame, PS_RED)
};
