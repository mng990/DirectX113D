matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.uv = input.uv;
    
    return output;
}

// Filter = Ȯ�� / ��Ұ� �Ͼ�� �� �߰� ���� ó���ϴ� ���
// Address = UV�� 1���� ���� ��, ������ �κ��� ó���ϴ� ���

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_TARGET
{   
    return Texture0.Sample(SamplerAddressWrap, input.uv);
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