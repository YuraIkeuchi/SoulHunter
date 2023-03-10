#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "IntroductionObj.h"
#include "IntroPlayer.h"
/// タイトルシーン
class IntroductionSceneActor : public BaseActor {
public:
	/// 初期化
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 終了
	void Finalize() override;
	/// 毎フレーム更新
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 描画
	void Draw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void GameDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void FrontDraw();
	//演出
	void Movie();
private://メンバ変数
	unique_ptr<IntroPlayer> introplayer = nullptr;
	//Json読み込みのクラス
	static IntroductionObj* Introductionobj;
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	unique_ptr<IKESprite> IntroSprite;
	//タイマー
	int m_Timer = 0;
	//ポストエフェクトの値
	float m_Sepia = 0.0f;
	//フレーム
	float m_Frame = 0.0f;
	//色
	XMFLOAT4 m_TextColor = { 1.0f,1.0f,1.0f,0.0f };
	int m_ChangeTimer = 0;

	static bool m_IntroNew;
};