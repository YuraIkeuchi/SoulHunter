#pragma once
#include "BaseActor.h"
#include "IKESprite.h"
#include "BossSceneChange.h"
#include "BossStagObj.h"

/// タイトルシーン
class PlaySceneActor : public BaseActor {
public:
	/// 初期化
	void Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 終了
	void Finalize() override;
	/// 毎フレーム更新
	void Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup) override;
	/// 描画
	void Draw(DirectXCommon* dxCommon) override;
	void PlaySceneInitialize();//プレイシーンのみの初期化
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
	void MapInitialize(LightGroup* lightgroup);

	//更新処理関数わけ
	//各クラスの更新
	void AllUpdate(DebugCamera* camera);
	//ライトの設置
	void LightSet(LightGroup* lightgroup);
	//ボス部屋の更新
	void BossRoomUpdate();
	//シーンチェンジなど
	void ChangeUpdate();
	//ゴール判定
	void GoalHit();
private:
	//ボス登場シーンのクラス
	unique_ptr<BossStagObj> bossstagobj = nullptr;
	//ボス登場シーンの画面暗転
	unique_ptr<BossSceneChange> bossscenechange = nullptr;

};