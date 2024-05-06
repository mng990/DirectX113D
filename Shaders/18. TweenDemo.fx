#include "00. Light.fx"
#include "00. Render.fx"

cbuffer TweenBufferDemo
{
    TweenFrameDesc TweenFrameDemo;
};

matrix GetAnimationMatrix(VertexTextureTangentNormalBlend input)
{
    float indices[4] = { input.blendIndices.x, input.blendIndices.y, input.blendIndices.z, input.blendIndices.w };
    float weight [4] = { input.blendWeight.x, input.blendWeight.y, input.blendWeight.z, input.blendWeight.w };

    int animIndex[2];
    int currFrame[2];
    int nextFrame[2];
    float ratio[2];
    
    animIndex[0] = TweenFrameDemo.curr.animIndex;
    currFrame[0] = TweenFrameDemo.curr.currFrame;
    nextFrame[0] = TweenFrameDemo.curr.nextFrame;
    ratio[0] = TweenFrameDemo.curr.ratio;
    
    animIndex[1] = TweenFrameDemo.next.animIndex;
    currFrame[1] = TweenFrameDemo.next.currFrame;
    nextFrame[1] = TweenFrameDemo.next.nextFrame;
    ratio[1] = TweenFrameDemo.next.ratio;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    matrix curr = 0;
    matrix next = 0;
    matrix transform = 0;
    
    for (int i = 0; i < 4; i++)
    {
        c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currFrame[0], animIndex[0], 0));
        c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currFrame[0], animIndex[0], 0));
        c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currFrame[0], animIndex[0], 0));
        c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currFrame[0], animIndex[0], 0));
        curr = matrix(c0, c1, c2, c3);
        
        n0 = TransformMap.Load(int4(indices[i] * 4 + 0, nextFrame[0], animIndex[0], 0));
        n1 = TransformMap.Load(int4(indices[i] * 4 + 1, nextFrame[0], animIndex[0], 0));
        n2 = TransformMap.Load(int4(indices[i] * 4 + 2, nextFrame[0], animIndex[0], 0));
        n3 = TransformMap.Load(int4(indices[i] * 4 + 3, nextFrame[0], animIndex[0], 0));
        next = matrix(n0, n1, n2, n3);
        
        matrix result = lerp(curr, next, ratio[0]);
        
        if(animIndex[1] >= 0)
        {
            c0 = TransformMap.Load(int4(indices[i] * 4 + 0, currFrame[1], animIndex[1], 0));
            c1 = TransformMap.Load(int4(indices[i] * 4 + 1, currFrame[1], animIndex[1], 0));
            c2 = TransformMap.Load(int4(indices[i] * 4 + 2, currFrame[1], animIndex[1], 0));
            c3 = TransformMap.Load(int4(indices[i] * 4 + 3, currFrame[1], animIndex[1], 0));
        
            curr = matrix(c0, c1, c2, c3);
        
            n0 = TransformMap.Load(int4(indices[i] * 4 + 0, nextFrame[1], animIndex[1], 0));
            n1 = TransformMap.Load(int4(indices[i] * 4 + 1, nextFrame[1], animIndex[1], 0));
            n2 = TransformMap.Load(int4(indices[i] * 4 + 2, nextFrame[1], animIndex[1], 0));
            n3 = TransformMap.Load(int4(indices[i] * 4 + 3, nextFrame[1], animIndex[1], 0));
            next = matrix(n0, n1, n2, n3);
        
            matrix nextResult = lerp(curr, next, ratio[1]);
            result = lerp(result, nextResult, TweenFrameDemo.tweenRatio);
        }
        
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