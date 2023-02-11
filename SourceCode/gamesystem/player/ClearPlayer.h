#pragma once
#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"

class ClearPlayer :
	public ObjCommon
{
public:
	ClearPlayer();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;

	void StateInitialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

	//動き
	void ClearMove(int Timer);

private:

	//アニメーションタイマー用
	struct AnimationTimer {
		int MoveAnimation = 0;
		int NotAnimation = 0;
		int FallAnimation = 0;
	};

	AnimationTimer m_AnimationTimer;
};