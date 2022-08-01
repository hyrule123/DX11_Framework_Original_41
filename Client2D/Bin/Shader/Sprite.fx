
#include "Share.fx"

/*
�Է·�������, ��·�������, �����������, �ӽ÷�������
VertexShader������ ��������

�������ʹ� �̸� + ��ȣ�� ��������� �ȴ�.
���� ��� POSITION �������Ͷ�� POSITION0 ~ 15 ������ �̿��� �����ϴ�.
0���� ��� ��ȣ ������ �����ؼ� POSITION �̶�� �ϸ� 0�� �������͸� �ǹ��Ѵ�.

�Է·������� : ����ϴ� �޽��� ���������� �� �ְ� �ȴ�.
�޽��� ����Ҷ� ������ � ������ ������� ���������� ������ �Ŀ� �����
�ϰ� �ȴ�.

��·������� : Shader���� ������ �������� �Ŀ� ������� �����صα� ����
���������̴�. VertexShader�� ��� ����� �������������� ��ġ ������ �־��شٴ���
�ƴϸ� �ٸ� Shader���� �ʿ�� �ϴ� �߰����� �����鵵 ��·������� �־�θ�
���� Shader���� �������� ����� �� �ִ�.

����������� : C++�ڵ尡 ������ �ִ� ������ Shader�� �Ѱ��ٶ� ����Ѵ�.

�ӽ÷������� : C++����ó�� �����Ҷ� �ʿ��� ���������̴�.
*/

// float : �Ǽ�Ÿ�� float2 : x, y�� ������ �ִ� Vector2, float3, float4 �� ��.
// int : ����Ÿ�� int2 : x, y�� intŸ������ ������ �ִ� Vector2 Ÿ��
// Semantic : �������͸� �����Ѵ�.

// �Ʒ�ó�� �����ϸ� �Է·��������� POSITION0, COLOR0 �������Ϳ� ����ִ�
// ���� �����ͼ� ����ϰڴٴ� ���̴�.
struct VS_INPUT_COLOR
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

// SV : System Value�� ���Ǵ� ������ ��·������Ϳ��� ����� �� �ִ�.
// ��·������Ϳ� �Ʒ�ó�� SV_POSITION �� ������ ���� �������������� ��ġ��
// �����ϴ°����� �� ���� �̿��ؼ� ȭ���� ��� ��������� �����Ѵ�.
// SV ���� �ٸ� Shader���� ����� �ǵ帮�� �ȵȴ�.
struct VS_OUTPUT_COLOR
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

// ���ڷ� VS_INPUT_COLOR�� ���� �� ����ü�� ������ �Է� �������Ϳ��� ����
// �����ͼ� ����ϹǷ� ���ڸ� ���� �־��� �ʿ䰡 ����.
VS_OUTPUT_COLOR SpriteColorVS(VS_INPUT_COLOR input)
{
    VS_OUTPUT_COLOR output = (VS_OUTPUT_COLOR) 0;

    float3  Pos = input.Pos - g_Pivot * g_MeshSize;
    
    // mul : ��� ��. g_matWVP �� World * View * Proj �̹Ƿ� ������ ���⿡ ���ϰ� �Ǹ�
    // ���� �������� ��ȯ�� ������ ��ġ�� ���´�.
    output.Pos = mul(float4(Pos, 1.f), g_matWVP);
    output.Color = input.Color;
    
    return output;
}

PS_OUTPUT_SINGLE SpriteColorPS(VS_OUTPUT_COLOR input)
{
    PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE) 0;
    
    output.Color = input.Color;
    
    return output;
}

