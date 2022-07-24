
// DirectX11은 RenderTarget을 최대 8개까지 한꺼번에 사용할 수 있다.
// SV_TARGET0 은 0번 렌더타겟에 출력한다.
struct PS_OUTPUT_SINGLE
{
    float4 Color : SV_TARGET;
};