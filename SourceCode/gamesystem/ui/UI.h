#pragma once
#include"IKESprite.h"
#include"Player.h"
#include "InterBoss.h"
//UIのクラス
class UI {
public:
	UI(Player* player = nullptr, InterBoss* boss = nullptr);
	void Update(InterBoss* boss = nullptr);
	void Finalize();
	const void Draw();

private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//定数
	static const int HP_Max = 5;//HPの数
private:
	unique_ptr<Player> player = nullptr;
	unique_ptr<InterBoss> interboss = nullptr;
	array<unique_ptr<IKESprite>,HP_Max> PlayerHpSprite;//プレイヤーのHP
	unique_ptr<IKESprite> BossHpSprite;//ボスのHP
	array<unique_ptr<IKESprite>, 72> SoulSprite;//プレイヤーのMP
	unique_ptr<IKESprite> SoulGageSprite;//プレイヤーのスタミナの枠
	//変数
	int m_HP = 0;
	float m_Soul = 0.0f;
	float m_BossHP = 0.0f;
	int m_JumpCount = 0;
	float m_AddPower = 0.0f;
	float m_DrawSoul = 0.0f;
	XMFLOAT3 m_JumpUiPos = {0.0f,0.0f,0.0f};
	//UIのサイズ
	XMFLOAT2 m_HPSize = { 0.0f,0.0f };
	XMFLOAT2 m_SoulSize = { 0.0f,0.0f };
	XMFLOAT2 m_AfterSoulSize = { 0.0f,0.0f };
	XMFLOAT2 m_BossHPSize = { 0.0f,0.0f };
	XMFLOAT2 m_AfterBossHPSize = { 0.0f,0.0f };
	//色
	XMFLOAT4 m_HPColor[HP_Max];
	float m_CutWidth = 72.0f;
	enum EnemyType {
		Normal,
		Thorn,
		Bound,
		Bird
	};
private:
};