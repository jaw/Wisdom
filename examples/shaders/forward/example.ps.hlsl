//#include "../headers/3dlut.hlsli"

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct PSOutput
{
    float4 color : SV_TARGET0;
    float4 color2 : SV_TARGET1;
};

static const float3 lut3d[3 * 3 * 3] =
{
    float3(0, 0, 0),
    float3(0.5, 0, 0),
    float3(1, 0, 0),
    
    float3(0, 0.5, 0),
    float3(0.5, 0.5, 0),
    float3(1, 0.5, 0),
    
    float3(0, 1, 0),
    float3(0.5, 1, 0),
    float3(1, 1, 0),
    
    float3(0, 0, 0.5),
    float3(0.5, 0, 0.5),
    float3(1, 0, 0.5),
    
    float3(0, 0.5, 0.5),
    float3(0.5, 0.5, 0.5),
    float3(1, 0.5, 0.5),
    
    float3(0, 1, 0.5),
    float3(0.5, 1, 0.5),
    float3(1, 1, 0.5),
    
    float3(0, 0, 1),
    float3(0.5, 0, 1),
    float3(1, 0, 1),
    
    float3(0, 0.5, 1),
    float3(0.5, 0.5, 1),
    float3(1, 0.5, 1),
    
    float3(0, 1, 1),
    float3(0.5, 1, 1),
    float3(1, 1, 1),
};

float4 SampleCubeX(float3 xsample, float3 dims)
{
    float3 c = xsample * (dims - 1.0f);
    int index = int(c.z * dims.x * dims.y + c.y * dims.x + c.x);
    return float4(lut3d[index], 1.0f);
}

float4 cscApplyLut3DTetra(const float3 color, const float3 dims)
{
    // make cube
    float3 re_color = color * float3(0.998f, 0.998f, 0.998f) + float3(0.001f, 0.001f, 0.001f); //clamp to 1.0)
    float3 re_dims = dims - float3(1.0f, 1.0f, 1.0f);
    float3 restored = re_color * re_dims; //restore position in table
    
    float3 black = floor(re_color);
    float3 white = black + float3(1.0f, 1.0f, 1.0f);
    
    float3 fracts = frac(restored); // get normalized fractions
    
    float3 blackf = black / re_dims;
    float3 whitef = white / re_dims;
    
    // select tetrahedron
    bool3 cmp = fracts.rgb >= fracts.gbr; // (r>g, g>b, b>r)
    int res = int(cmp.x) * 4 + int(cmp.y) * 2 + int(cmp.z) - 1;
    
    // variants:
    // r<g, g<b, b>r t2 (001) // B C          c.z  c.z + c.y
    // r>g, g<b, b<r t6 (010) // G Y  -1- G   c.y  c.y + c.x
    // r<g, g>b, b>r t3 (011) // G C          c.y  c.y + c.z
    // r>g, g<b, b<r t4 (100) // R M  1-- R   c.x  c.x + c.z
    // r>g, g<b, b>r t1 (101) // B M  --1 B   c.z  c.z + c.x
    // r>g, g>b, b<r t5 (110) // R Y          c.x  c.x + c.y
    
    float3 swizzle_rgb[6];
    swizzle_rgb[0] = float3(blackf.x, blackf.y, whitef.z);
    swizzle_rgb[1] = float3(blackf.x, whitef.y, blackf.z);
    swizzle_rgb[2] = float3(blackf.x, whitef.y, blackf.z);
    swizzle_rgb[3] = float3(whitef.x, blackf.y, blackf.z);
    swizzle_rgb[4] = float3(blackf.x, blackf.y, whitef.z);
    swizzle_rgb[5] = float3(whitef.x, blackf.y, blackf.z);
    
    float3 swizzle_cmy[6];
    swizzle_cmy[0] = float3(blackf.x, whitef.y, whitef.z);
    swizzle_cmy[1] = float3(whitef.x, whitef.y, blackf.z);
    swizzle_cmy[2] = float3(blackf.x, whitef.y, whitef.z);
    swizzle_cmy[3] = float3(whitef.x, blackf.y, whitef.z);
    swizzle_cmy[4] = float3(whitef.x, blackf.y, whitef.z);
    swizzle_cmy[5] = float3(whitef.x, whitef.y, blackf.z);
    
    float3 swizzle_xyz[6];
    swizzle_xyz[0] = float3(restored.z, restored.y, restored.x);
    swizzle_xyz[1] = float3(restored.y, restored.x, restored.z);
    swizzle_xyz[2] = float3(restored.y, restored.z, restored.x);
    swizzle_xyz[3] = float3(restored.x, restored.z, restored.y);
    swizzle_xyz[4] = float3(restored.z, restored.x, restored.y);
    swizzle_xyz[5] = float3(restored.x, restored.y, restored.z);
    
    float3 point_rgb = swizzle_rgb[res];
    float3 point_cmy = swizzle_cmy[res];
    float3 delta = swizzle_xyz[res];
     
    float4 s1 = SampleCubeX(blackf, dims); // lower diagonal
    float4 s2 = SampleCubeX(point_rgb, dims);
    float4 s3 = SampleCubeX(point_cmy, dims);
    float4 s4 = SampleCubeX(whitef, dims); // upper diagonal

    return (1.0f - delta.x) * s1 + (delta.x - delta.y) * s2 + (delta.y - delta.z) * s3 + delta.z * s4;
}



PSOutput main(PSInput input)
{
    PSOutput output;
    const float3 dims = float3(3.0f, 3.0f, 3.0f);
    output.color = /*input.color; //*/cscApplyLut3DTetra(input.color.rgb, dims);
    output.color2 = input.color;
    return output;
}