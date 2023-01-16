#include "Basic.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float2 offsetscroll = float2(offset.x,offset.y);
	//float2 offset = float2(0.0f, );
	float4 texcolor = tex.Sample(smp, input.uv * Tiling + offsetscroll);


	// 光沢度
	const float shininess = 4.0f;
	// 頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	// 環境反射光
	float3 ambient = m_ambient;

	// シェーディングによる色
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	float4 disolvecolor = float4(ambientColor * ambient, m_alpha);
	//ライトの影響を受けるか
	if (LightEffect) {
		// 平行光源
		for (int i = 0; i < DIRLIGHT_NUM; i++) {
			if (dirLights[i].active) {
				// ライトに向かうベクトルと法線の内積
				float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
				// 反射光ベクトル
				float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
				// 拡散反射光
				float3 diffuse = dotlightnormal * m_diffuse;
				// 鏡面反射光
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				// 全て加算する
				shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
			}
			//ディゾルブのために別計算
			// ライトに向かうベクトルと法線の内積
			float3 dotlightnormal2 = dot(dirLights[i].lightv, input.normal);
			// 反射光ベクトル
			float3 reflect2 = normalize(-dirLights[i].lightv + 2 * dotlightnormal2 * input.normal);
			// 拡散反射光
			float3 diffuse2 = dotlightnormal2 * m_diffuse;
			// 鏡面反射光
			float3 specular2 = pow(saturate(dot(reflect2, eyedir)), shininess) * m_specular;
			disolvecolor.rgb = shadecolor.rgb += (diffuse2 + specular2) * dirLights[i].lightcolor;
		}

		// 点光源
		for (i = 0; i < POINTLIGHT_NUM; i++) {
			if (pointLights[i].active) {
				// ライトへの方向ベクトル
				float3 lightv = pointLights[i].lightpos - input.worldpos.xyz;
				float d = length(lightv);
				lightv = normalize(lightv);

				// 距離減衰係数
				float atten = 1.0f / (pointLights[i].lightatten.x + pointLights[i].lightatten.y * d + pointLights[i].lightatten.z * d * d);

				// ライトに向かうベクトルと法線の内積
				float3 dotlightnormal = dot(lightv, input.normal);
				// 反射光ベクトル
				float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
				// 拡散反射光
				float3 diffuse = dotlightnormal * m_diffuse;
				// 鏡面反射光
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				// 全て加算する
				shadecolor.rgb += atten * (diffuse + specular) * pointLights[i].lightcolor;

				//if (tone >= 2.0f) {
				//	shadecolor.rgb = float3(0, 0, 0);
				//}
			}
		}

		// スポットライト
		for (i = 0; i < SPOTLIGHT_NUM; i++) {
			if (spotLights[i].active) {
				// ライトへの方向ベクトル
				float3 lightv = spotLights[i].lightpos - input.worldpos.xyz;
				float d = length(lightv);
				lightv = normalize(lightv);

				// 距離減衰係数
				float atten = saturate(1.0f / (spotLights[i].lightatten.x + spotLights[i].lightatten.y * d + spotLights[i].lightatten.z * d * d));

				// 角度減衰
				float cos = dot(lightv, spotLights[i].lightv);
				// 減衰開始角度から、減衰終了角度にかけて減衰
				// 減衰開始角度の内側は1倍 減衰終了角度の外側は0倍の輝度
				float angleatten = smoothstep(spotLights[i].lightfactoranglecos.y, spotLights[i].lightfactoranglecos.x, cos);
				// 角度減衰を乗算
				atten *= angleatten;

				// ライトに向かうベクトルと法線の内積
				float3 dotlightnormal = dot(lightv, input.normal);
				// 反射光ベクトル
				float3 reflect = normalize(-lightv + 2 * dotlightnormal * input.normal);
				// 拡散反射光
				float3 diffuse = dotlightnormal * m_diffuse;
				// 鏡面反射光
				float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

				// 全て加算する
				shadecolor.rgb += atten * (diffuse + specular) * spotLights[i].lightcolor;
			}
		}
	}
	else {
		for (int i = 0; i < DIRLIGHT_NUM; i++) {
			// ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
			// 反射光ベクトル
			float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
			// 拡散反射光
			float3 diffuse = dotlightnormal * m_diffuse;
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

			// 全て加算する
			shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;

			//ディゾルブのために別計算
		// ライトに向かうベクトルと法線の内積
			float3 dotlightnormal2 = dot(dirLights[i].lightv, input.normal);
			// 反射光ベクトル
			float3 reflect2 = normalize(-dirLights[i].lightv + 2 * dotlightnormal2 * input.normal);
			// 拡散反射光
			float3 diffuse2 = dotlightnormal2 * m_diffuse;
			// 鏡面反射光
			float3 specular2 = pow(saturate(dot(reflect2, eyedir)), shininess) * m_specular;
			disolvecolor.rgb = shadecolor.rgb += (diffuse2 + specular2) * dirLights[i].lightcolor;
		}
	}

	// 丸影
	for (int i = 0; i < CIRCLESHADOW_NUM; i++) {
		if (circleShadows[i].active) {
			// オブジェクト表面からキャスターへのベクトル
			float3 casterv = circleShadows[i].casterPos - input.worldpos.xyz;
			// 光線方向での距離
			float d = dot(casterv, circleShadows[i].dir);

			// 距離減衰係数
			float atten = saturate(1.0f / (circleShadows[i].atten.x + circleShadows[i].atten.y * d + circleShadows[i].atten.z * d * d));
			// 距離がマイナスなら0にする
			atten *= step(0, d);

			// ライトの座標
			float3 lightpos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
			//  オブジェクト表面からライトへのベクトル（単位ベクトル）
			float3 lightv = normalize(lightpos - input.worldpos.xyz);
			// 角度減衰
			float cos = dot(lightv, circleShadows[i].dir);
			// 減衰開始角度から、減衰終了角度にかけて減衰
			// 減衰開始角度の内側は1倍 減衰終了角度の外側は0倍の輝度
			float angleatten = smoothstep(circleShadows[i].factorAngleCos.y, circleShadows[i].factorAngleCos.x, cos);
			// 角度減衰を乗算
			atten *= angleatten;

			// 全て減算する
			shadecolor.rgb -= atten;
		}
	}

	//ディゾルブ
	float l_Disolve = Disolve;
	float blackarea = Disolve + 0.2f;
	float a = disolvecolor.r * 0.5 + disolvecolor.g * 0.5 + disolvecolor.b * 0.5;

	//消えるときに少し黒くなって消える
	if (ChangeColor) {
		if (a < blackarea) {
			texcolor.r = texcolor.r - Addcolor.r;
			texcolor.g = texcolor.g - Addcolor.g;
			texcolor.b = texcolor.b - Addcolor.b;
		}
	}

	//だんだん消える
	if (a > l_Disolve) {
		shadecolor.a = 1.0f;
	}
	else {
		shadecolor.a = 0.0f;
	}


	//フォグ部分
	float4 normalcolor = { 0.1,0.1,0.1,0 };//cameraPos付近の色
	float4 c = { 0.4,0.4,0.4,0 };//
	//cameraPosとあるが今は固定座標
	float dist = length(cameraPos - input.worldpos);
	float4 addcol = float4(lerp(normalcolor.rgb, c.rgb, dist / 50), 0.0);
	//暗闇にするため
	addcol = addcol * -0.5f;

	float4 pixcolor;
	//fogかかかってるかかかってないか
	if (Fog) {
		pixcolor = shadecolor * texcolor * color + (addcol);
	}
	else {
		pixcolor = shadecolor * texcolor * color;
	}

	// シェーディングによる色で描画
	return pixcolor;
}