#pragma once
#include "BaseScene.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

//ゲームプレイシーン
class FirstStage : public BaseScene
{
private://メンバ変数

public:
	//初期化
	void Initialize(DirectXCommon* dxCommon) override;
	//更新
	void Update(DirectXCommon* dxCommon) override;
	//描画
	void Draw(DirectXCommon* dxCommon) override;
	//開放
	void Finalize() override;
	void ModelDraw(DirectXCommon* dxCommon);
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);

	//要素全削除
	void AllDelete();
	//マップの初期化
	void MapInitialize();

	//更新処理関数わけ
	//各クラスの更新
	void AllUpdate();
	//ライトの設置
	void LightSet();
	//ボス部屋の更新
	void BossRoomUpdate();
	//シーンチェンジなど
	void ChangeUpdate();
	//ゴール判定
	void GoalHit();
public:
};