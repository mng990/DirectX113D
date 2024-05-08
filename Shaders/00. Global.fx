#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

/////////////////
// Const Buffer//
/////////////////

cbuffer GlobalBuffer
{
    matrix V;  // View
    matrix P;  // Projection
    matrix VP; // (View * Projection)
    matrix VInv; // View Inverse
};

cbuffer TransformBuffer
{
    matrix W; // World
};


/////////////////
//Vertex Buffer//
/////////////////

struct Vertex
{
    float4 position : POSITION;
};


struct VertexTexture
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};


struct VertexColor
{
    float4 Position : POSITION;
    float4 Color : COLOR;
};


struct VertexTextureNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VertexTextureTangentNormal
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};


struct VertexTextureTangentNormalBlend
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 blendIndices : BLENDINDICES;
    float4 blendWeight : BLENDWEIGHT;
};


/////////////////
//Vertex Output//
/////////////////


struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};


/////////////////
//Sampler State//
/////////////////

// Filter = Ȯ�� / ��Ұ� �Ͼ�� �� �߰� ���� ó���ϴ� ���
// Address = UV�� 1���� Ŭ ��, ������ �κ��� ó���ϴ� ���

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState PointSampler
{
    Filter = MIN_MAG_MIP_Point;
    AddressU = Wrap;
    AddressV = Wrap;
};

/////////////////////
// RasterizerState //
/////////////////////

RasterizerState FillModeWireFrame
{
    FillMode = WireFrame;
};

RasterizerState FrontCounterClockwiseTrue
{
    FrontCounterClockwise = true;
};

////////////////
// BlendState //
////////////////

BlendState AlphaBlend
{
    AlphaToCoverageEnable = false;

    BlendEnable[0] = true;
    SrcBlend[0] = SRC_ALPHA;
    DestBlend[0] = INV_SRC_ALPHA;
    BlendOp[0] = ADD;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = Zero;
    BlendOpAlpha[0] = Add;

    RenderTargetWriteMask[0] = 15;
};

BlendState AlphaBlendAlphaToCoverageEnable
{
    AlphaToCoverageEnable = true;

    BlendEnable[0] = true;
    SrcBlend[0] = SRC_ALPHA;
    DestBlend[0] = INV_SRC_ALPHA;
    BlendOp[0] = ADD;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = Zero;
    BlendOpAlpha[0] = Add;

    RenderTargetWriteMask[0] = 15;
};

BlendState AdditiveBlend
{
    AlphaToCoverageEnable = true;

    BlendEnable[0] = true;
    SrcBlend[0] = One;
    DestBlend[0] = One;
    BlendOp[0] = ADD;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = Zero;
    BlendOpAlpha[0] = Add;

    RenderTargetWriteMask[0] = 15;
};

BlendState AdditiveBlendAlphaToCoverageEnable
{
    AlphaToCoverageEnable = true;

    BlendEnable[0] = true;
    SrcBlend[0] = One;
    DestBlend[0] = One;
    BlendOp[0] = ADD;

    SrcBlendAlpha[0] = One;
    DestBlendAlpha[0] = Zero;
    BlendOpAlpha[0] = Add;

    RenderTargetWriteMask[0] = 15;
};

///////////
// Macro //
///////////

#define PASS_VP(name, vs, ps)                     \
pass name                                         \
{                                                 \
    SetVertexShader(CompileShader(vs_5_0, vs())); \
    SetPixelShader(CompileShader(ps_5_0, ps()));  \
}

#define PASS_VRP(name, vs, rs, ps)                \
pass name                                         \
{                                                 \
    SetVertexShader(CompileShader(vs_5_0, vs())); \
    SetRasterizerState(rs);                       \
    SetPixelShader(CompileShader(ps_5_0, ps()));  \
}

#define PASS_VBP(name, vs, bs, ps)                \
pass name                                         \
{                                                 \
    SetVertexShader(CompileShader(vs_5_0, vs())); \
    SetBlendState(bs, float4(0,0,0,0), 0xFF);     \
    SetPixelShader(CompileShader(ps_5_0, ps()));  \
}


//////////////
// Function //
//////////////

float3 CameraPosition()
{
    return VInv._41_42_43;
}


///////////
// Const //
///////////

static const float PI = 3.14159265f;


#endif

