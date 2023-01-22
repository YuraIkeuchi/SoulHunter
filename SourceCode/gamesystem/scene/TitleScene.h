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
	void PartsMove();//タイトルの文字の動き
	void PartsBirth();//タイトルの文字が浮かびだす
private://メンバ変数
	//スプライト
	unique_ptr<IKESprite> TitleSprite;
	array<unique_ptr<IKESprite>,3> TitlePartsSprite;
	unique_ptr<IKETexture> backtex;
	//Json読み込みのクラス
	static TitleObj* titleobj;
	//シーン遷移のためのもの
	int m_TitleSelect = 0;
	//タイトルのパーツに必要なもの
	array<float, 2> m_Angle;
	array<float, 2> m_Angle2;
	array<XMFLOAT2, 3> m_PartsPos;
	array<XMFLOAT2, 3> m_PartsSize;
	enum TitleSelect {
		NewGame,
		LoadGame,
		SelectGame
	};

	//段々と色が浮かび上がる演出
	int m_TitleTimer = 0;
	XMFLOAT4 m_TitleColor = { 1.0f,1.0f,1.0f,0.0 };
	float m_Frame = 0.0f;

	//ライトの変数
	XMFLOAT3 m_LightPos = { 0.0f,0.0f,0.0f };

	static bool m_TitleNew;
};

