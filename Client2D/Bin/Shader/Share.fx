
// DirectX11�� RenderTarget�� �ִ� 8������ �Ѳ����� ����� �� �ִ�.
// SV_TARGET0 �� 0�� ����Ÿ�ٿ� ����Ѵ�.
struct PS_OUTPUT_SINGLE
{
    float4 Color : SV_TARGET;
};

// ������۴� 16����Ʈ ������ ����� �Ѵ�.
cbuffer Transform : register(b0)
{
    matrix  g_matWorld;
    matrix  g_matView;
    matrix  g_matProj;
    matrix  g_matWVP;
    float3  g_Pivot;
    float3  g_MeshSize;
    float2  g_TransformEmpty;
};