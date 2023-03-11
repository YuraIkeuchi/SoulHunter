#pragma once
#include"IKESprite.h"
#include <memory>
#include "Helper.h"
using namespace std;         //  名前空間指定
//マップ変更時のクラス
class MapChange {
public:
	MapChange();
	void Update();//更新
	void Finalize();//解放
	const void Draw();//描画

	//void EaseScale();

	bool AddBlack();//暗くなる

	bool SubBlack();//明るくなる

	float GetScale() { return m_scale; }

	int GetTimer() { return m_Timer; }

	void SetAddStartChange(const bool& m_AddStartChange) { this->m_AddStartChange = m_AddStartChange; }
	void SetSubStartChange(const bool& m_SubStartChange) { this->m_SubStartChange = m_SubStartChange; }
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private://静的メンバ変数
	static XMFLOAT4 s_color;
private:
	unique_ptr<Helper> helper;
	//シーン切り替え(縮小の方)
	unique_ptr<IKESprite> change = nullptr;
	XMFLOAT2 m_pos = { 640.0f,360.0f, };

	float m_scale = 1.0f;
	bool m_AddStartChange = false;
	bool m_SubStartChange = false;
	int m_Timer = 0;

	int m_BlackNumber = 0;
	enum BlackColor {
		Add,
		Sub,
	};
};

