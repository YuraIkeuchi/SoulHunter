#include "Particle.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(GSOutput input) : SV_TARGET
{
	float4 texcolor = tex.Sample(smp, input.uv);
	float4 color = (0.5f, 0.5f, 0.5f, 0.5f);
	return texcolor * color;
//return float4(1, 1, 1, 1);
}