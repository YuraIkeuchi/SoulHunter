#pragma once
#include "BaseActor.h"
#include "ImGuiEditor.h"
/// タイトルシーン
class EditorSceneActor : public BaseActor {
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
	void FrontDraw(DirectXCommon* dxCommon);
	void BackDraw(DirectXCommon* dxCommon);
	void ImGuiDraw(DirectXCommon* dxCommon);
	void PostImGuiDraw(DirectXCommon* dxCommon);
	//マップの切り替えの関数
	void StageMapChange(int StageNumber,LightGroup* lightgroup);
	//マップの初期化
	void MapInitialize();
	//更新処理関数わけ
	//各クラスの更新
	void AllUpdate(DebugCamera* camera);
	//ライトの設置
	void LightSet(LightGroup* lightgroup);
	//シーンチェンジなど
	void ChangeUpdate();
	//エディタ関係
	void EditorUpdate();
private:
	//エディタ
	unique_ptr<ImGuiEditor> imguieditor;
	bool m_EnemyDelete = false;
	bool m_ObjDelete = false;

	bool m_MapChange = false;
};