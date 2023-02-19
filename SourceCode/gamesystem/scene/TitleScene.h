#pragma once
#include "BaseScene.h"
#include "TitleObj.h"

/// タイトルシーン
class TitleScene : public BaseScene {
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
	void FrontDraw();
	void ChangePostEffect(int PostType);
	void SelectGameMode();//ゲームやモードを選択
	void TitleMove();//タイトルの文字の動き
	void ModeMove();//モードの文字の動き
	void ColorChange();//モード変える際の色の変更
private:
	static const int TITLE_MAX = 3;//タイトルパーツの最大数
	static const int MODE_MAX = 3;//モードパーツの最大数
	static const int EXPLAIN_MAX = 3;//説明文の最大数
private://メンバ変数
	//スプライト
	unique_ptr<IKESprite> TitleSprite;
	unique_ptr<IKESprite> ModeSprite;
	array<unique_ptr<IKESprite>, TITLE_MAX> TitlePartsSprite;
	array<unique_ptr<IKESprite>, MODE_MAX> ModePartsSprite;
	array<unique_ptr<IKESprite>, EXPLAIN_MAX> ModeEplainSprite;
	unique_ptr<IKETexture> backtex;
	//Json読み込みのクラス
	static TitleObj* titleobj;
	//シーン遷移のためのもの
	int m_TitleSelect = 0;
	int m_ModeSelect = 0;
	//タイトルのパーツに必要なもの
	array<float, 3> m_Angle;
	array<float, 3> m_Angle2;
	array<XMFLOAT2, TITLE_MAX> m_PartsPos;
	array<XMFLOAT2, TITLE_MAX> m_PartsSize;
	enum TitleSelect {
		NewGame,
		LoadGame,
		SelectGame
	};

	//モードセレクトに必要なもの
	array<XMFLOAT2, TITLE_MAX> m_ModePartsPos;
	array<XMFLOAT2, TITLE_MAX> m_ModePartsSize;

	array<XMFLOAT2, EXPLAIN_MAX> m_ExplainSize;
	enum ModeSelect {
		EasyMode,
		NormalMode,
		SelectMode
	};

	//段々と色が浮かび上がる演出
	XMFLOAT4 m_TitleColor = { 1.0f,1.0f,1.0f,1.0 };
	XMFLOAT4 m_ModeColor = { 1.0f,1.0f,1.0f,0.0 };

	//イージングのため
	float m_AfterTitleAlpha = 0.0f;
	float m_AfterModeAlpha = 0.0f;
	bool m_ModeChange = false;
	float m_Frame = 0.0f;

	//ライトの変数
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };

	static bool m_TitleNew;

	int m_SelectType = 0;
	//選択しているもの
	enum SelectType {
		Game,
		Mode,
	};
};

