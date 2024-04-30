matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;

float3 LightDir;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)World);
    
    return output;
}

// Filter = 확대 / 축소가 일어났을 때 중간 값을 처리하는 방식
// Address = UV가 1보다 컸을 때, 나머지 부분을 처리하는 방식

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.normal);
    float3 light = -LightDir;
 
    return float4(0.f, 1.f, 0.f, 1.f) * dot(light, normal);
}

RasterizerState FillModeWireFrame
{
    FillMode = Wireframe;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader (CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetRasterizerState(FillModeWireFrame);
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};