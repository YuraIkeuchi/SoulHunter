#pragma once
#include "BaseScene.h"
#include "ImGuiEditor.h"
#include "EnemyEdit.h"
#include "ObjEdit.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

//ゲームプレイシーン
class EditorScene : public BaseScene
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
	void EnemyDelete();
	void ObjDelete();
	//マップの初期化
	void MapInitialize();
	//マップの切り替えの関数
	void StageMapChange(int StageNumber);
	//プレイヤーとステージの読み書き
	void SaveGame();
	void LoadGame();


	//更新処理関数わけ
	//各クラスの更新
	void AllUpdate();
	//ライトの設置
	void LightSet();
	//シーンチェンジなど
	void ChangeUpdate();
	//エディタ関係
	void EditorUpdate();
private:
	//エディタ
	unique_ptr<ImGuiEditor> imguieditor;
	EnemyEdit* enemyedit = nullptr;
	ObjEdit* objedit = nullptr;
};