struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float2 tex : TEXCOORD0;
};

struct VS_OUT
{
    float4 pos  : SV_POSITION;
    float4 posw : POSITION0;
    float4 norw : NORMAL0;
    float2 tex  : TEXCOORD0;
};

cbuffer ConstantBuffer
{
    float4x4 world;         // ���[���h�ϊ��s��
    float4x4 view;          // �r���[�ϊ��s��
    float4x4 projection;    // �����ˉe�ϊ��s��
    float4   Light;
}

VS_OUT vs_main(VS_IN input)
{
   

    VS_OUT output;
    float3 nor;
    float  col;

    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    output.posw = mul(input.pos, world);
    output.norw = mul(input.nor, world);

    output.tex = input.tex;

    return output;
}