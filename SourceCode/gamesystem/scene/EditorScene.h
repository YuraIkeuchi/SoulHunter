#pragma once
#include "BaseScene.h"
#include "EditorSceneActor.h"
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
};