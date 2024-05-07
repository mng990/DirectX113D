#include "00. Render.fx"
#include "00. Light.fx"

struct ComputeInput
{
    uint3 groupID : SV_GroupID;
    uint3 groupThreadID : SV_GroupThreadID;
    uint3 dispatchTheadID : SV_DispatchThreadID;
    uint groupIndex : SV_GroupIndex;
};


Texture2DArray<float4> Input; // SRV
RWTexture2DArray<float4> Output; // UAV


[numthreads(32, 32, 1)]
void CS(uint3 id : SV_DispatchThreadID)
{
    float4 color = Input.Load(int4(id, 0));
    
    Output[id] = color;
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);
        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
};
