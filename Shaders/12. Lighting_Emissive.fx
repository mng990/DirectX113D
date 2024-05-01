#include "00. Global.fx"


float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
    MeshOutput output;
    output.position = mul(input.position, W);
    output.worldPosition = input.position;

    output.position = mul(output.position, VP);
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)W);
    
    return output;
}

// Emissive
// 외곽선을 구할 때 사용

float4 PS(MeshOutput input) : SV_TARGET
{       
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
    
    float value = saturate(dot(E, input.normal)); // clamp(0~1)
    float emissive = 1.0f - value;
    
    emissive = smoothstep(0.f, 1.f, emissive);
    
    emissive = pow(emissive, 3);
    
    float4 color = MaterialEmissive * emissive;
       
    return color;
}


technique11 T0
{
    PASS_VP(p0, VS, PS)
};