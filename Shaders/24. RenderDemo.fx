#include "00. Render.fx"
#include "00. Light.fx"


float4 PS(MeshOutput input) : SV_TARGET
{
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);

}

technique11 T0
{
	PASS_VP(P0, VS_MESH, PS)
    PASS_VP(P1, VS_MODEL, PS)
    PASS_VP(P2, VS_ANIMATION, PS)
    PASS_VRP(P3, VS_MESH, FillModeWireFrame, PS_RED)
};
