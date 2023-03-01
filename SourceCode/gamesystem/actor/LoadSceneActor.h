#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
/// タイトルシーン
class LoadSceneActor : public BaseActor {
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
	void SpriteDraw();
	void MoveLoad();
private:
	//定数
	static const int Now_Max = 4;
	static const int Load_Max = 5;
private://メンバ変数
	array<unique_ptr<IKESprite>, Now_Max> nowsprite;
	array<unique_ptr<IKESprite>, Load_Max> loadsprite;
	XMFLOAT2 m_Position = { 640.0f,320.0f };
	XMFLOAT2 m_Size = { 1028.0f,128.0f };
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
	//どのテキストを出すか
	int m_LoadNumber = 0;
	enum TitleSelect {
		Pause,
		Soul
	};

	//アニメーション
	int m_LoadAnimeTimer = 0;
	int m_LoadAnimeCount = 0;
	//ローディング画面のタイマー
	int m_LoadTimer = 0;
	int m_LoadChackCount = 0;

	float m_Angle = 0.0f;
	float m_Angle2 = 0.0f;
};