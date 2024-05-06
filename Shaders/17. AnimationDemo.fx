#include "00. Light.fx"
#include "00. Render.fx"


cbuffer KeyframeBuffer
{
    KeyframeDesc Keyframes;
};

/*
matrix GetAnimationMatrix(VertexTextureTangentNormalBlend input)
{
    float indices[4] = { input.blendIndices.x, input.blendIndices.y, input.blendIndices.z, input.blendIndices.w };
    float weight[4] = { input.blendWeight.x, input.blendWeight.y, input.blendWeight.z, input.blendWeight.w };

    int animIndex = Keyframes.animIndex;
    int currFrame = Keyframes.currFrame;
    int nextFrame = Keyframes.nextFrame;
    
    float4 c0, c1, c2, c3;
    
    matrix curr = 0;
    matrix transform = 0;
    
    for (int i = 0; i < 4; i++)
    {
        c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currFrame, animIndex, 0));
        c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currFrame, animIndex, 0));
        c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currFrame, animIndex, 0));
        c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currFrame, animIndex, 0));
        
        curr = matrix(c0, c1, c2, c3);
        transform += mul(weight[i], curr);
    }
    
    return transform;
}
*/

matrix GetAnimationMatrix(VertexTextureTangentNormalBlend input)
{
    float indices[4] = { input.blendIndices.x, input.blendIndices.y, input.blendIndices.z, input.blendIndices.w };
    float weight[4] = { input.blendWeight.x, input.blendWeight.y, input.blendWeight.z, input.blendWeight.w };

    int animIndex = Keyframes.animIndex;
    int currFrame = Keyframes.currFrame;
    int nextFrame = Keyframes.nextFrame;
    float ratio = Keyframes.ratio;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    matrix curr = 0;
    matrix next = 0;
    matrix transform = 0;
    
    for (int i = 0; i < 4; i++)
    {
        c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currFrame, animIndex, 0));
        c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currFrame, animIndex, 0));
        c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currFrame, animIndex, 0));
        c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currFrame, animIndex, 0));
        
        curr = matrix(c0, c1, c2, c3);
        
        n0 = TransformMap.Load(int4(indices[i] * 4 + 0, currFrame, animIndex, 0));
        n1 = TransformMap.Load(int4(indices[i] * 4 + 1, currFrame, animIndex, 0));
        n2 = TransformMap.Load(int4(indices[i] * 4 + 2, currFrame, animIndex, 0));
        n3 = TransformMap.Load(int4(indices[i] * 4 + 3, currFrame, animIndex, 0));
        next = matrix(n0, n1, n2, n3);
        
        matrix result = lerp(curr, next, ratio);
        
        transform += mul(weight[i], result);

    }
    
    return transform;
}


MeshOutput VS(VertexTextureTangentNormalBlend input){
    
    MeshOutput output;
        
    matrix m = GetAnimationMatrix(input);
    
    output.position = mul(input.position, m);
    output.position = mul(output.position, W);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, VP);
    
    output.uv = input.uv;
    output.normal = mul(input.normal, (float3x3)W);
    output.tangent = mul(input.tangent, (float3x3) W);
    
    return output;
}


float4 PS(MeshOutput input) : SV_TARGET
{      
    //ComputeNormalMapping(input.normal, input.tangent, input.uv);
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
    PASS_VP(P0, VS, PS)
    PASS_VRP(P1, VS, FillModeWireFrame, PS_RED)
};