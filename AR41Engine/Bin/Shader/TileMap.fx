
#include "Share.fx"

struct VS_INPUT_UV
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
    uint InstanceID : SV_InstanceID;
};

struct VS_OUTPUT_UV
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    float2 OriginUV : TEXCOORD1;
    float4 Color : COLOR;
    float Opacity : TEXCOORD2;
};

cbuffer TileMapCBuffer : register(b10)
{
    float2 g_TileImageSize;
    float2 g_TileStart;
    float2 g_TileEnd;
    float2 g_TileSize;
    matrix g_TilematWVP;
    int    g_TileFrame;
    float3 g_TileEmpty;
};


struct TileInfo
{
    matrix matWVP;
    float2 Start;
    float2 End;
    float4 TypeColor;
    float Opacity;
    int AnimationType;
    int Frame;
    float Empty;
};

StructuredBuffer<TileInfo> g_TileInfoArray : register(t40);



VS_OUTPUT_UV TileMapVS(VS_INPUT_UV input)
{
    VS_OUTPUT_UV output = (VS_OUTPUT_UV) 0;

    float3 Pos = input.Pos - g_Pivot * g_MeshSize;
    
    // mul : 행렬 곱. g_matWVP 는 World * View * Proj 이므로 정점을 여기에 곱하게 되면
    // 투영 공간으로 변환된 정점의 위치가 나온다.
    output.Pos = mul(float4(Pos, 1.f), g_matWVP);
    output.UV = UpdateAnimation2D(input.UV);
    
    return output;
}

PS_OUTPUT_SINGLE TileMapPS(VS_OUTPUT_UV input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;

    float4 TextureColor = g_BaseTexture.Sample(g_PointSmp, input.UV);
    
    output.Color.rgb = TextureColor.rgb * g_MtrlBaseColor.rgb;

    output.Color.a = TextureColor.a * g_MtrlOpacity;
    
    return output;
}