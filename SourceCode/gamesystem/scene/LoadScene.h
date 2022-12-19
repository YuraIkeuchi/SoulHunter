#pragma once
#include "BaseScene.h"
#include "IKESprite.h"
/// タイトルシーン
class LoadScene : public BaseScene {
public:
	/// 初期化
	void Initialize(DirectXCommon* dxCommon) override;
	/// 終了
	void Finalize() override;
	/// 毎フレーム更新
	void Update(DirectXCommon* dxCommon) override;
	/// 描画
	void Draw(DirectXCommon* dxCommon) override;
	void ModelDraw(DirectXCommon* dxCommon);
	void GameDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);
	void SpriteDraw();
	void ChangePostEffect(int PostType);
private://メンバ変数
	unique_ptr<IKESprite> nowsprite[4];
	unique_ptr<IKESprite> loadsprite[2];
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
};

