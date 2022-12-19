#include"PostEffectTest.hlsli"
Texture2D<float4> tex : register(t0);	//0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);		//0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float density = 50;
	float4 col = tex.Sample(smp, floor(input.uv * density) / density);
	return col;
}