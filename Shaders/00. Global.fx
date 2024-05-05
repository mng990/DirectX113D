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

struct MeshOutput
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
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

