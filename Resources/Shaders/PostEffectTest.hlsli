cbuffer cbuff0 : register(b0)
{
	float4 color; // 色(RGBA)
	matrix mat; // ３Ｄ変換行列
	float addsepia;
	int ToneType;//トーンタイプ
	int ColorSpace;//出力色空間
	float BaseLuminance;//基準輝度
	float MaxLuminance;//最大輝度
};

//頂点シェーダーからの出力構造体
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};