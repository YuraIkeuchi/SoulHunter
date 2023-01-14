cbuffer cbuff0 : register(b0)
{
	float4 color; // �F(RGBA)
	matrix mat; // �R�c�ϊ��s��
	float addsepia;
	int ToneType;//�g�[���^�C�v
	int ColorSpace;//�o�͐F���
	float BaseLuminance;//��P�x
	float MaxLuminance;//�ő�P�x
};

//���_�V�F�[�_�[����̏o�͍\����
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};