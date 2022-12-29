#pragma once
#include "BaseScene.h"
#include <array>       // ヘッダファイルインクルード
#include "BossAppObj.h"
#include "BossSceneChange.h"
#include "BossEndObj.h"
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
	void NormalDraw(DirectXCommon* dxCommon);//普通の描画
	void BossAppDraw(DirectXCommon* dxCommon);//ボス登場シーンの描画
	void BossEndDraw(DirectXCommon* dxCommon);//ボス登場シーンの描画
	void NormalUpdate();//普通の更新
	void BossAppUpdate();//ボス登場シーンの更新
	void BossEndUpdate();//ボス終了シーンの更新
	void ImGuiDraw(DirectXCommon* dxCommon);
	
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
private:
	//ボス登場シーンのクラス
	unique_ptr<BossAppObj> bossappobj = nullptr;
	//ボス終了シーンのクラス
	unique_ptr<BossEndObj> bossendobj = nullptr;
	//ボス登場シーンの画面暗転
	unique_ptr<BossSceneChange> bossscenechange = nullptr;
};