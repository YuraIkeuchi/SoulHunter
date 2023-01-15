#include"PostEffectTest.hlsli"
Texture2D<float4>tex0:register(t0);//0番スロットに設定されたテクスチャ
SamplerState smp:register(s0);


float4 ColorSpaceConvert(float4 color);
float4 ToneMapping(float4 color);
float4 ApplyOETF(float4 color);
float3 ReinhardTone(float3 color);
float3 GtTone(float3 color);
float3 OETF_BT709(float3 color);
float3 OETF_BT2100(float3 color);
float3 ToneMap(float3 mainColor, float2 toeColor, float2 linearColor);
float4 main(VSOutput input) : SV_TARGET
{

    //float4 colortex0 = tex0.Sample(smp,input.uv);

    //float4 l_color = colortex0;

    ////色空間の変換
    //l_color = ColorSpaceConvert(l_color);
    ////トーンマッピング
    //l_color = ToneMapping(l_color);

    ////OETF適用
    //l_color = ApplyOETF(l_color);

    //return float4(l_color.rgb, 1);


    //if(l_color)
    ////トーンマップ処理
    //float3 toneMapColor = ToneMap(float3(l_color.rgb), toeColor, linearColor);

    //return float4(toneMapColor.rgb, 1);

    float4 colortex0 = tex0.Sample(smp,input.uv);
    float4 color = colortex0;

    //トーンマップ処理
    float3 toneMapColor = ToneMap(float3(colortex0.rgb), toeColor, linearColor);

    //float a = color.r * 0.5 + color.g * 0.5 + color.b * 0.5;
    //if (a > 1.2f) {
    //    color = float4(colortex0.rgb - 0.5, 1);
    //}

     return float4(toneMapColor.rgb, 1);
}

//色変換
float4 ColorSpaceConvert(float4 color) {
    float4 result = 0;

    //switch (ColorSpace) {
    //    //そのまま色を返す
    //    case 0:
    //    {
    //        result = color;
    //    }
    //break;
    //    case 1:
    //    {

    //      
    //    }

    //    break;
    //}
    static const float3x3 conversion =
    {
        0.627404f,0.329283f,0.043313f,
        0.069097f,0.919540f,0.011362f,
        0.016391f,0.088013f,0.895595f,
    };
    result.rgb = mul(conversion, color.rgb);
    return float4(result.rgb, 1);
}

//トーンマッピング
float4 ToneMapping(float4 color) {
    float4 result = 0;

    result.rgb = ReinhardTone(color.rgb);
    //switch (ToneType) {
    //    //トーンなし
    //case 0:
    //    result.rgb = color.rgb;
    //    break;
    //case 1:
    //   
    //    break;
    //case 2:
    //    result.rgb = GtTone(color.rgb);
    //    break;
    //}

    return float4(result.rgb, 1);
}

//Reinhartトーン
float3 ReinhardTone(float3 color) {


    //float Lz = MaxLuminance / BaseLuminance;
    //float k = BaseLuminance * Lz / (BaseLuminance - Lz);

    //return float4(color.rgb * k / (color.rgb + float3(k, k, k)), 1);

    //return (1, 1, 1);

}

//GTトーン
float3 GtTone(float3 color) {
  /*  float k = MaxLuminance / BaseLuminance;
    float P = k;
    float a = 1.0f;
    float m = 0.22f;
    float l = 0.4f;
    float c = 1.33f;
    float b = 0.0f;

    float3 x = color.rgb;
    float l0 = ((P - m) * l) / a;
    float l1 = m - (m / a);
    float l2 = m + ((1.0f - m) / a);

    float s0 = m + l0;
    float s1 = m + a * l0;
    float c2 = (a * P) / (P - s1);
    float cp = -c2 / P;

    float3 w0 = 1.0f - smoothstep(0.0f, m, x);
    float3 w2 = step(m + l0, x);
    float3 w1 = 1.0f - w0 - w2;

    float3 T = m * pow(x / m, c) + b;
    float3 S = P - (P - s1) * exp(cp * (x - s0));
    float3 L = m + a * (x - m);

    return T * w0 + L * w1 + S * w2;*/
}

//OETF適用
float4 ApplyOETF(float4 color) {
    //float4 result = 0;

    //switch (ColorSpace) {
    //    //そのまま色を返す
    //case 0:
    //    result.rgb = OETF_BT709(color.rgb);
    //    break;
    //case 1:
    //    result.rgb = OETF_BT2100(color.rgb);
    //    break;
    //}
    //return float4(result.rgb, 1);
}

float3 OETF_BT709(float3 color) {
    float3 result;
    result.r = (color.r <= 0.018f) ? 4.500 * color.r : (1.0f + 0.099) * pow(abs(color.r), 0.45f) - 0.099f;
    result.g = (color.r <= 0.018f) ? 4.500 * color.g : (1.0f + 0.099) * pow(abs(color.g), 0.45f) - 0.099f;
    result.b = (color.r <= 0.018f) ? 4.500 * color.b : (1.0f + 0.099) * pow(abs(color.b), 0.45f) - 0.099f;
    
    return result;
}

float3 OETF_BT2100(float3 color) {
    float m1 = 2610.0 / 4096.0 / 4;
    float m2 = 2523.0 / 4096.0 * 128;
    float c1 = 3424.0 / 4096.0;
    float c2 = 2413.0 / 4096.0 * 32;
    float c3 = 2392.0 / 4096.0 * 32;

    float3 cp = pow(abs(color.rgb), m1);
    return pow((c1 + c2 * cp) / (1 + c3 * cp), m2);
}

float3 ToneMap(float3 mainColor, float2 toeColor, float2 linearColor)
{
    const float3 RGB2Y = float3(+0.29900f, +0.58700f, +0.11400f);
    const float3 RGB2Cb = float3(-0.16874f, -0.33126f, +0.50000f);
    const float3 RGB2Cr = float3(+0.50000f, -0.41869f, -0.08131f);
    const float3 YCbCr2R = float3(+1.00000f, +0.00000f, +1.40200f);
    const float3 YCbCr2G = float3(+1.00000f, -0.34414f, -0.71414f);
    const float3 YCbCr2B = float3(+1.00000f, +1.77200f, +0.00000f);

    float4 info = float4(toeColor, linearColor.x, linearColor.y);
    float3 texel = mainColor.rgb;

    float coeff = 0.18 * exp(-info.g);
    float l_max = coeff * info.r;

    // YCbCr系に変換
    float3 YCbCr;
    YCbCr.y = dot(RGB2Cb, texel);
    YCbCr.z = dot(RGB2Cr, texel);

    // 色の強さは補正
    float lum = coeff * dot(RGB2Y, texel);
    YCbCr.x = lum * (1.0f + lum / (l_max * l_max)) / (1.0f + lum);

    // RGB系にして出力
    float3 color;
    color.r = dot(YCbCr2R, YCbCr);
    color.g = dot(YCbCr2G, YCbCr);
    color.b = dot(YCbCr2B, YCbCr);

    //return color;

    float LuminousIntensity = dot(mainColor.rgb, float3(0.2125, 0.7154, 0.0712));
    float3 returnColor = mainColor * (1 - smoothstep(0.0, 1.0, LuminousIntensity)) + color * smoothstep(0.0, 1.0, LuminousIntensity);

    return returnColor;
}