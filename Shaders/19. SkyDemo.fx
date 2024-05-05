#include "00. Light.fx"
#define MAX_MODEL_TRANSFORMS 500
#define MAX_MODEL_KEYFRAMES 500

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTexture input)
{    
    VS_OUT output;

    // Local -> World -> View -> Proj
    float4 viewPos = mul(float4(input.position.xyz, 0), V);
    float4 clipPos = mul(viewPos, P);
    
    output.position = clipPos.xyzw;
    output.position.z = output.position.w;
    
    output.uv = input.uv;
    
    return output;
}


float4 PS(VertexTexture input) : SV_TARGET
{      
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
    //float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    
    return color;
}

float4 PS_RED(VertexOutput input) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);
}

technique11 T0
{
    pass P0
    {
        SetRasterizerState(FrontCouterClockWiseTrue);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};