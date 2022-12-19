#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "IKEObject3d.h"
#include"IKEModel.h"
#include "Player.h"
#define DIRECTINPUT_VERSION 0x0800

//背景に置く
//基盤クラス
class BackObjCommon {
protected:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	/// 座標の取得
	const XMFLOAT3& GetPosition() { return  m_pos; }

	const XMFLOAT3& GetRotation() { return m_rot; }

	/// 座標の設定
	void SetPosition(const XMFLOAT3& m_pos) { this->m_pos = m_pos; }

	void SetRotation(const XMFLOAT3& m_rot) { this->m_rot = m_rot; }

	void SetScale(const XMFLOAT3& m_scale) { this->m_scale = m_scale; }
protected:
	//クラス
	unique_ptr<Player> player = nullptr;
	//OBJとモデル
	unique_ptr<IKEObject3d> object3d = nullptr;
	IKEModel* model = nullptr;
	//座標
	XMFLOAT3 m_pos = { 0,0,0 };
	XMFLOAT3 m_rot = { 0,0,0 };
	XMFLOAT3 m_scale = { 0.4f,0.4f,0.4f };
	enum ObjType {
		Piller,
		Rock,
		Wall
	};
public:
	virtual ~BackObjCommon() = default;
	//初期化
	virtual void Initialize() = 0;
	//更新
	void Update();
	//描画
	void Draw();

	virtual void SetObj() = 0;//配置
	virtual void specialDraw() = 0;//その他の描画

	bool UpdateCollide();//更新範囲

	bool DrawCollide();//描画範囲
};