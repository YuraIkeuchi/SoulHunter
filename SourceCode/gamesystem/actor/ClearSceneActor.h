#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "ClearObj.h"
#include "ClearPlayer.h"
#include "Helper.h"
/// タイトルシーン
class ClearSceneActor : public BaseActor {
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
	unique_ptr<Helper> helper;
	unique_ptr<ClearPlayer> clearplayer = nullptr;
	//Json読み込みのクラス
	static ClearObj* clearobj;
	array<unique_ptr<IKESprite>, 2> CurtainSprite;
	unique_ptr<IKESprite> SkipSprite;
	unique_ptr<IKESprite> ClearSprite;
	//タイマー
	int m_Timer = 0;
	int m_ResetTimer = 0;
	//ポストエフェクトの値
	float m_Sepia = 0.0f;
	//フレーム
	float m_Frame = 0.0f;
	//色
	XMFLOAT4 m_TextColor = { 1.0f,1.0f,1.0f,0.0f };
	//座標
	XMFLOAT2 m_ClearPos = { 0.0f,550.0f };
	int m_ChangeTimer = 0;
	//ライトの変数
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };

	static bool m_ClearNew;
};
