
struct VertexInput
{
    float4 position : POSITION;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = input.position;
    
    return output;
}

float4 PS0(VertexOutput input) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);
}

float4 PS1(VertexOutput input) : SV_TARGET
{
    return float4(0.f, 1.f, 0.f, 1.f);
}

float4 PS2(VertexOutput input) : SV_TARGET
{
    return float4(0.f, 0.f, 1.f, 1.f);
}


technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS0()));

    }
    
    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS1()));
    }
};

technique11 T1
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS2()));
    }
};