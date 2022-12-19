cbuffer cbuff0 : register(b0)
{
	float4 color; // 色(RGBA)
	matrix mat; // ３Ｄ変換行列
	float addsepia;
};

//頂点シェーダーからの出力構造体
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv :TEXCOORD;
};