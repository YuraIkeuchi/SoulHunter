#include "SingleColor.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	//�F
	float4 shadecolor = color;

	//shadecolor.a = 1.0f;
	//�o��
	return shadecolor;

	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	//return color;

	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
}