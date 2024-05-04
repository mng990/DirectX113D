#include "00. Light.fx"
#define MAX_MODEL_TRANSFORMS 50


cbuffer BoneBuffer
{
    matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};

uint BoneIndex;


MeshOutput VS(VertexTextureTangentNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, BoneTransforms[BoneIndex]);
    
    output.position = mul(output.position, W);
    output.worldPosition = input.position.xyz;

    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3) W);
    
    return output;
}

// Emissive
// �ܰ����� ���� �� ���

float4 PS(MeshOutput input) : SV_TARGET
{      
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    //float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
       
    return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);
}

technique11 T0
{
    PASS_VP(P0, VS, PS)
    PASS_VRP(P1, VS, FillModeWireFrame, PS_RED)
};