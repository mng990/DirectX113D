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

// Filter = 확대 / 축소가 일어났을 때 중간 값을 처리하는 방식
// Address = UV가 1보다 클 때, 나머지 부분을 처리하는 방식

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

///////////
// Macro //
///////////

#define PASS_VP(name, vs, ps)                     \
pass name                                         \
{                                                 \
    SetVertexShader(CompileShader(vs_5_0, vs())); \
    SetPixelShader(CompileShader(ps_5_0, ps()));  \
}


//////////////
// Function //
//////////////

float3 CameraPosition()
{
    return -V._41_42_43;
}


///////////
// Const //
///////////

static const float PI = 3.14159265f;


#endif

