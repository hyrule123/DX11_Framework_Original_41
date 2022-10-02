
#include "Share.fx"

cbuffer UICBuffer : register(b10)
{
    float4 g_UITint;
    matrix g_UIWVP;
    float2 g_UIMeshSize;
    float2 g_UIPivot;
    int g_UITextureEnable;
    float g_UIOpacity;
    float2 g_UIEmpty;
};

struct VS_INPUT_UV
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_OUTPUT_UV
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};


// ���ڷ� VS_INPUT_COLOR�� ���� �� ����ü�� ������ �Է� �������Ϳ��� ����
// �����ͼ� ����ϹǷ� ���ڸ� ���� �־��� �ʿ䰡 ����.
VS_OUTPUT_UV UIVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float2 Pos = input.Pos.xy - g_UIPivot * g_UIMeshSize;
    
    // mul : ��� ��. g_matWVP �� World * View * Proj �̹Ƿ� ������ ���⿡ ���ϰ� �Ǹ�
    // ���� �������� ��ȯ�� ������ ��ġ�� ���´�.
    output.Pos = mul(float4(Pos, input.Pos.z, 1.f), g_UIWVP);
    
    if (g_UITextureEnable)
        output.UV = UpdateAnimation2D(input.UV);
    
    else
        output.UV = input.UV;
    
    return output;
}

PS_OUTPUT_SINGLE UIPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    if (g_UITextureEnable)
    {
        float4 TextureColor = g_BaseTexture.Sample(g_PointSmp, input.UV);
    
        output.Color.rgb = TextureColor.rgb * g_UITint.rgb;

        output.Color.a = TextureColor.a * g_UIOpacity;
    }
    
    else
    {
        output.Color.rgb = g_UITint.rgb;
        output.Color.a = g_UITint.a * g_UIOpacity;
        
    }
    
    return output;
}
