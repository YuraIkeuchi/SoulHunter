#include "Toon.hlsli"

Texture2D<float4> tex : register(t0);  // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	//�e�N�X�`���}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);

	//�V�F�[�f�B���O�ɂ��F
	float4 shadecolor;
	//����x
	const float shininess = 50.0f;
	//���_���王�_�ւ̃x�N�g��
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//�n�[�t�x�N�g��
	float3 halfvec = normalize(lightv + eyedir);
	//���C�g�Ɍ������x�N�g���Ɩ@���̓���
	float intensity = saturate(dot(normalize(input.normal), halfvec));
	//�����ˌ�
	float3 ambient = m_ambient;
	//a�l���ɐݒ肵�Ă�
	shadecolor.a = m_alpha;
	//smoothstep�p�ϐ�
	float _Threshold = 0.45;
	//�A�̕���
	float3 diffuse = m_diffuse * smoothstep(_Threshold, _Threshold + 0.1f, intensity);
	//���̕���
	float3 specular = m_specular * smoothstep(_Threshold, _Threshold + 0.1f, pow(intensity, shininess));
	//���ׂĉ��Z
	float3 ads = (ambient + diffuse + specular) * texcolor.rgb;
	//���邢�����̐F
	float3 light_color = ads;
	//�Â������̐F
	float3 dark_color = texcolor.rgb * 0.3;
	//�A�ƌ��̕����̔���
	shadecolor.rgb = smoothstep(_Threshold, _Threshold + 0.1f, intensity) * light_color + (1 - smoothstep(_Threshold, _Threshold + 0.1f, intensity)) * dark_color * lightcolor;

	//�o��
	return shadecolor * color;
}