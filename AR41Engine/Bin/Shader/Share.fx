
// DirectX11은 RenderTarget을 최대 8개까지 한꺼번에 사용할 수 있다.
// SV_TARGET0 은 0번 렌더타겟에 출력한다.
struct PS_OUTPUT_SINGLE
{
    float4 Color : SV_TARGET;
};

// 상수버퍼는 16바이트 단위로 맞춰야 한다.
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